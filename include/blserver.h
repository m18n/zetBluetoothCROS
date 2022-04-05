#pragma once
#include "bobj.h"
#include"core.h"
#include<thread>
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
private:
    void GetPacket();
public:
    void ServerInit();
    
   
    void ServerStart();
    void ServerStop();
    void sendMessage(std::string mess);
private:
    sockaddre addr = {0};
    socklen_t opt = sizeof(addr);
    SOCKET servsock;
    SOCKET client;
    bool serverpr = false;
};