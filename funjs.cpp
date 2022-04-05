#include"include/funjs.h"
VServClient* funjs::viewsc=NULL;


JSValueRef ConnectJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    JSString js = JSValueCreateJSONString(ctx, arguments[0], NULL, exception);
    String mac = (String)js;
    String8 mac_utf8 = mac.utf8();
    std::string mac_str = details::GetString(mac_utf8.data());

    double port = JSValueToNumber(ctx, arguments[1], exception);
    std::cout << "GET VAR\t MAC: " << mac_str << " PORT: " << port << "\n";
    Bobj b(mac_str,"HELLo");

    funjs::viewsc->blclient.Connect(b,port);
    return JSValueMakeNull(ctx);

}
JSValueRef DisconnectJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    funjs::viewsc->blclient.Disconnect();
    return JSValueMakeNull(ctx);
}
JSValueRef ServerStartJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    funjs::viewsc->blserv.ServerInit();
    funjs::viewsc->blserv.ServerStart();
    return JSValueMakeNull(ctx);
}
JSValueRef ServerStopJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    funjs::viewsc->blserv.ServerStop();
    return JSValueMakeNull(ctx);
}
JSValueRef ServerSendMessageJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    JSString js = JSValueCreateJSONString(ctx, arguments[0], NULL, exception);
    String mac = (String)js;
    String8 mac_utf8 = mac.utf8();
    std::string mess = details::GetString(mac_utf8.data());
    funjs::viewsc->blserv.sendMessage(mess);
    return JSValueMakeNull(ctx);

}
JSValueRef ClientSendMessageJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    JSString js = JSValueCreateJSONString(ctx, arguments[0], NULL, exception);
    String mac = (String)js;
    String8 mac_utf8 = mac.utf8();
    std::string mess = details::GetString(mac_utf8.data());
    funjs::viewsc->blclient.sendMessage(mess);
    return JSValueMakeNull(ctx);

}
void funjs::RegistrFunVServClient(VServClient* vs) {
    viewsc = vs;
    vs->RegistrFunctionJs("ConnectCpp", ConnectJs);
    vs->RegistrFunctionJs("ServerStartCpp", ServerStartJs);
    vs->RegistrFunctionJs("ServerStopCpp", ServerStopJs);
    vs->RegistrFunctionJs("ServSendMessageCpp", ServerSendMessageJs);
    vs->RegistrFunctionJs("ClientSendMessageCpp", ClientSendMessageJs);
    vs->RegistrFunctionJs("DisconnectCpp", DisconnectJs);
}