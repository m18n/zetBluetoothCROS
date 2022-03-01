#include"include/blserver.h"
void* CreateBLServer() {
    core::clog << "TeST\n";
	return  (void*) new BlServer();
}
void StartServer(void* blserver,uint8_t channel) {
	BlServer* bl = (BlServer*)blserver;
	bl->ServerInit(channel);
	bl->ServerStart();
}
void BlServer::ServerInit(uint8_t channel)
{
    std::cout <<"VLOG: " << &core::vlog[0] << "\n";
    core::clog << "SERVER INIT\n";
    std::cout << "VLOG: " << &core::vlog[0] << "\n";
    servsock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
   
    // bind socket to port 1 of the first available
    // local bluetooth adapter
#ifndef __linux__ //windows
    addr.addressFamily = AF_BTH;
    addr.serviceClassId = RFCOMM_PROTOCOL_UUID;
    addr.port = BT_PORT_ANY;
#else//linux
    bdaddr_t bdaddr_any = { 0, 0, 0, 0, 0, 0 };
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_bdaddr = bdaddr_any;
    addr.rc_channel = channel;
#endif // __linux__


}
void BlServer::GetPacket() {

    SOCKET client = accept(servsock, (struct sockaddr*)&addr, &opt);
    core::clog << "CONNECT CLIENT\n";
    std::cout << "CONNECT CLIENT\n";
    send(client, "TEST", 4, NULL);
    while (true)
    {

        char hay[1024];
        int res = recv(client, hay, 1024, NULL);
        if (res < 0)
        {
            core::clog << "DISSCONNECT\n";
            std::cout << "DISSCONNECT\n";
            close(client);
            client = accept(servsock, (struct sockaddr*)&addr, &opt);
            core::clog << "CONNECT CLIENT\n";
            std::cout << "CONNECT CLIENT\n";
            send(client, "TEST", 4, NULL);
            continue;
        }
        int test = (int)hay[0];
        std::cout << "HAy: " << test << "\n";

    }
}
void BlServer::ServerStart()
{
    core::clog << "SERVER START\n";
    std::cout << "SERVER STARTT\n";
    bind(servsock, (struct sockaddr*)&addr, sizeof(addr));

    // put socket into listening mode
    listen(servsock, 1);

    // accept one connection


   
    std::thread th(&BlServer::GetPacket,this);
    th.detach();
    
}