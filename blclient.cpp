#include"include/blclient.h"
void Connect(void* blclient,char* mac,int port) {
	
	Bobj b;
	b.SetStrMac(mac);
	BlClient* bl = (BlClient*)blclient;
	bl->Connect(b,port);
}
void BlClient::sendMessage(std::string mess) {
	senD(clsock, mess.c_str(), mess.length());
}