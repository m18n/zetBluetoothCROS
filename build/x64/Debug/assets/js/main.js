function Connect(){
    let mac=document.getElementById("mac").value;
    let port=parseInt(document.getElementById("port").value);
    ConnectCpp(mac,port);
}
function ServStart(){
    ServerStartCpp();
}
function ServStop(){
    ServerStopCpp();
}
function ServSendMessage(){
    let message=document.getElementById("messageserv").value;
    ServSendMessageCpp(message);
}
function ClientSendMessage(){
    let message=document.getElementById("messageclient").value;
    ClientSendMessageCpp(message);
}