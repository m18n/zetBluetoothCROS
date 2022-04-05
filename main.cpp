#include"include/blclient.h"
#include"include/blserver.h"
#include <AppCore/App.h>
#include <AppCore/Window.h>
#include <AppCore/Overlay.h>
#include <AppCore/JSHelpers.h>
#include <JavaScriptCore/JSRetainPtr.h>
using namespace ultralight;
#define WINDOW_WIDTH    900
#define WINDOW_HEIGHT   600
JSValueRef ConnectJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception);
JSValueRef ServerStartJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception);
JSValueRef ServerStopJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception);
JSValueRef ServerSendMessageJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception);
JSValueRef ClientSendMessageJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception);
class MyApp : public WindowListener,
    public ViewListener, public LoadListener {
    RefPtr<App> app_;
    RefPtr<Window> window_;
    RefPtr<Overlay> ov;
    
    JSContextRef ctx;
public:
    BlClient blcl;
    BlServer blserv;
    MyApp() {
      
        app_ = App::Create();
        window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
            false, kWindowFlags_Titled | kWindowFlags_Resizable);
        window_->SetTitle("Telegram");
        app_->set_window(*window_.get());
        ov = Overlay::Create(*window_.get(), 1, 1, 0, 0);     
        OnResize(window_->width(), window_->height());
        ov->view()->LoadURL("file:///index.html");
        window_->set_listener(this);
        ov->view()->set_view_listener(this);
        ov->view()->set_load_listener(this);
    }
    void OnDOMReady(View* caller,
        uint64_t frame_id,
        bool is_main_frame,
        const String& url) override
    {

        // Acquire the JS execution context for the current page.
        //
        // This call will lock the execution context for the current
        // thread as long as the Ref<> is alive.
        //
        Ref<JSContext> context = caller->LockJSContext();

        // Get the underlying JSContextRef for use with the
        // JavaScriptCore C API.
        ctx = context.get();
        RegistrFunctionJs("ConnectCpp", ConnectJs);
        RegistrFunctionJs("ServerStartCpp", ServerStartJs);
        RegistrFunctionJs("ServerStopCpp", ServerStopJs);
        RegistrFunctionJs("ServSendMessageCpp", ServerSendMessageJs);
        RegistrFunctionJs("ClientSendMessageCpp", ClientSendMessageJs);
        // Create a JavaScript String containing the name of our callback.
    }
    void RegistrFunctionJs(std::string namefunction, JSObjectCallAsFunctionCallback fun)
    {
        JSStringRef name = JSStringCreateWithUTF8CString(namefunction.c_str());

        // Create a garbage-collected JavaScript function that is bound to our
        // native C callback 'OnButtonClick()'.'

        JSObjectRef func = JSObjectMakeFunctionWithCallback(ctx, name,
            fun);

        // Get the global JavaScript object (aka 'window')
        JSObjectRef globalObj = JSContextGetGlobalObject(ctx);

        // Store our function in the page's global JavaScript object so that it
        // accessible from the page as 'OnButtonClick()'.
        JSObjectSetProperty(ctx, globalObj, name, func, 0, 0);

        // Release the JavaScript String we created earlier.
        JSStringRelease(name);
    }
    void CallFunctionJs(std::string namefunction, std::string val)
    {
        JSRetainPtr<JSStringRef> str = adopt(
            JSStringCreateWithUTF8CString(namefunction.c_str()));

        // Evaluate the string "ShowMessage"
        JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

        // Check if 'func' is actually an Object and not null
        if (JSValueIsObject(ctx, func))
        {

            // Cast 'func' to an Object, will return null if typecast failed.
            JSObjectRef funcObj = JSValueToObject(ctx, func, 0);

            // Check if 'funcObj' is a Function and not null
            if (funcObj && JSObjectIsFunction(ctx, funcObj))
            {

                // Create a JS string from null-terminated UTF8 C-string, store it
                // in a smart pointer to release it when it goes out of scope.
                JSRetainPtr<JSStringRef> msg =
                    adopt(JSStringCreateWithUTF8CString(val.c_str()));

                // Create our list of arguments (we only have one)
                const JSValueRef args[] = { JSValueMakeString(ctx, msg.get()) };

                // Count the number of arguments in the array.
                size_t num_args = sizeof(args) / sizeof(JSValueRef*);

                // Create a place to store an exception, if any
                JSValueRef exception = 0;

                // Call the ShowMessage() function with our list of arguments.
                JSValueRef result = JSObjectCallAsFunction(ctx, funcObj, 0,
                    num_args, args,
                    &exception);

                if (exception)
                {
                    // Handle any exceptions thrown from function here.
                }

                if (result)
                {
                    // Handle result (if any) here.
                }
            }
        }
    }
    void CallFunctionJs(std::string namefunction, double val)
    {
        JSRetainPtr<JSStringRef> str = adopt(
            JSStringCreateWithUTF8CString(namefunction.c_str()));

        // Evaluate the string "ShowMessage"
        JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

        // Check if 'func' is actually an Object and not null
        if (JSValueIsObject(ctx, func))
        {

            // Cast 'func' to an Object, will return null if typecast failed.
            JSObjectRef funcObj = JSValueToObject(ctx, func, 0);

            // Check if 'funcObj' is a Function and not null
            if (funcObj && JSObjectIsFunction(ctx, funcObj))
            {

                // Create a JS string from null-terminated UTF8 C-string, store it
                // in a smart pointer to release it when it goes out of scope.


                // Create our list of arguments (we only have one)
                const JSValueRef args[] = { JSValueMakeNumber(ctx,val) };

                // Count the number of arguments in the array.
                size_t num_args = sizeof(args) / sizeof(JSValueRef*);

                // Create a place to store an exception, if any
                JSValueRef exception = 0;

                // Call the ShowMessage() function with our list of arguments.
                JSValueRef result = JSObjectCallAsFunction(ctx, funcObj, 0,
                    num_args, args,
                    &exception);

                if (exception)
                {
                    // Handle any exceptions thrown from function here.
                }

                if (result)
                {
                    // Handle result (if any) here.
                }
            }
        }
    }
    void Connect(std::string mac,int port) {
        Bobj b(mac, "PHONE");
        //Bobj b(GE, "TELE");
        blcl.Connect(b,port);
        blcl.GetPacket();
    }
    void StartServer() {
        blserv.ServerInit();
        blserv.ServerStart();
    }
    void StopServer() {
        blserv.ServerStop();
    }
    
    virtual ~MyApp() {}
    virtual void OnClose() override {}
    virtual void OnResize(uint32_t width, uint32_t height) override {
        ov->Resize(width, height);
    }

    virtual void OnChangeCursor(ultralight::View* caller,
        Cursor cursor) {
        window_->SetCursor(cursor);
    }
    std::string GetString(String8 str) {
        char* w=str.data();
        w[str.length() - 1] = '\0';
        std::string string(&w[1]);
        
        
        return std::move(string);
    }
    void Run() {
        app_->Run();
        
    }
};
MyApp app;
JSValueRef ConnectJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    JSString js=JSValueCreateJSONString(ctx, arguments[0], NULL, exception);
    String mac=(String)js;
    String8 mac_utf8 = mac.utf8();
    std::string mac_str = app.GetString(mac_utf8.data());
    
    double port=JSValueToNumber(ctx, arguments[1], exception);
    std::cout << "GET VAR\t MAC: " << mac_str << " PORT: " << port << "\n";
    app.Connect(mac_str, port);
    return JSValueMakeNull(ctx);
    
}
JSValueRef ServerStartJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    app.StartServer();
    return JSValueMakeNull(ctx);
}
JSValueRef ServerStopJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    app.StopServer();
    return JSValueMakeNull(ctx);
}
JSValueRef ServerSendMessageJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    JSString js = JSValueCreateJSONString(ctx, arguments[0], NULL, exception);
    String mac = (String)js;
    String8 mac_utf8 = mac.utf8();
    std::string mess = app.GetString(mac_utf8.data());
    app.blserv.sendMessage(mess);
    return JSValueMakeNull(ctx);

}
JSValueRef ClientSendMessageJs(JSContextRef ctx, JSObjectRef function,
    JSObjectRef thisObject, size_t argumentCount,
    const JSValueRef arguments[], JSValueRef* exception) {
    JSString js = JSValueCreateJSONString(ctx, arguments[0], NULL, exception);
    String mac = (String)js;
    String8 mac_utf8 = mac.utf8();
    std::string mess = app.GetString(mac_utf8.data());
    app.blcl.sendMessage(mess);
    return JSValueMakeNull(ctx);

}
int main(int argc, char **argv)
{
    std::cout << "STARt\n";
    
    app.Run();
    
    return 0;
}
