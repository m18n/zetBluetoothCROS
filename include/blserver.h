#pragma once
#include "bobj.h"
#include"core.h"
DLLAPI class BlServer
{
public:
    BlServer()
    {
#ifndef __linux__ //windows
        WSADATA wsData;
        WORD ver = MAKEWORD(2, 2);

        int wsOk = WSAStartup(ver, &wsData);
        if (wsOk != 0)
        {
            std::cout << "ERROR\n" << "\n";
            return;
        }
#endif
    }

    ~BlServer()
    {
        close(servsock);
    }

public:
    void ServerInit(uint8_t channel)
    {
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
    
   
    void ServerStart()
    {
        std::cout << "SERVER STARTT\n";
        bind(servsock, (struct sockaddr *)&addr, sizeof(addr));

        // put socket into listening mode
        listen(servsock, 1);

        // accept one connection

       
        SOCKET client=accept(servsock, (struct sockaddr *)&addr, &opt);
         std::cout << "CONNECT CLIENT\n";
         send(client,"TEST",4,NULL);
        while (true)
        {

            char hay[1024];
            int res = recv(client, hay, 1024, NULL);
             if (res < 0)
            {
                std::cout << "DISSCONNECT\n";
                close(client);
                client = accept(servsock, (struct sockaddr *)&addr, &opt);
                std::cout << "CONNECT CLIENT\n";
                send(client,"TEST",4,NULL);
                continue;
            }
            int test = (int)hay[0];
            std::cout << "HAy: " << test << "\n";
           
        }
    }

private:
    sockaddre addr = {0};
    socklen_t opt = sizeof(addr);
    SOCKET servsock;
};
extern "C" {
    DLLAPI void* CreateBLServer();
    DLLAPI void StartServer(void* blserver,uint8_t channel);
}