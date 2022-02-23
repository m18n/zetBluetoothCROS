#include"include/blclient.h"
void* CreateBLClient() {
	core::clog << "CREATE OBJECT BLCLIENT\n";
	return  (void*) new BlClient();
}
void Connect(void* blclient,char* mac,int port) {
	
	Bobj b;
	b.SetStrMac(mac);
	BlClient* bl = (BlClient*)blclient;
	bl->Connect(b,port);
}