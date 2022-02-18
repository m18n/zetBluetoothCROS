#include"include/blserver.h"
void* CreateBLServer() {
	return  (void*) new BlServer();
}
void StartServer(void* blserver,uint8_t channel) {
	BlServer* bl = (BlServer*)blserver;
	bl->ServerInit(channel);
	bl->ServerStart();
}