#pragma once
#include "bobj.h"
#include"core.h"
 class BlServer
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
    void ServerInit(uint8_t channel);
    
   
    void ServerStart();

private:
    sockaddre addr = {0};
    socklen_t opt = sizeof(addr);
    SOCKET servsock;
};
extern "C" {
    DLLAPI void* CreateBLServer();
    DLLAPI void StartServer(void* blserver,uint8_t channel);
}