function Connect(){
    let h=document.getElementById("clienth");
    h.style.color='red';
    let mac=document.getElementById("mac").value;
    let port=parseInt(document.getElementById("port").value);
    ConnectCpp(mac,port);
}
function Disconnect(){
    let h=document.getElementById("clienth");
    h.style.color='black';
    DisconnectCpp();
}
function ServStart(){
    let h=document.getElementById('servh');
    h.style.color='red';
    ServerStartCpp();
}
function ServStop(){
    let h=document.getElementById('servh');
    h.style.color='black';
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