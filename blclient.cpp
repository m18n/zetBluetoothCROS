#include"include/blclient.h"
void Connect(void* blclient,char* mac,int port) {
	
	Bobj b;
	b.SetStrMac(mac);
	BlClient* bl = (BlClient*)blclient;
	bl->Connect(b,port);
}
void BlClient::sendMessage(std::string mess) {
	std::cout << "CLIENT SEND MESSAGE: " << mess << "\n";
	senD0(clsock, mess.c_str(), mess.length()+1);
}
void BlClient::Disconnect() {
	if (conn) {
		std::cout << "DISCONNECT\n";
		closesocket(clsock);
		conn = false;
	}
}