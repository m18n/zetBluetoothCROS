function Connect(){
    let mac=document.getElementById("mac").value;
    let port=parseInt(document.getElementById("port").value);
    ConnectCpp(mac,port);
}
function ServStart(){
    let port=parseInt(document.getElementById("portserv").value);
    ServerStartCpp(port);
}