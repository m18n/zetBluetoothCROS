#pragma once
#include"bobj.h"
#include"core.h"

class BlClient
{
public:
    BlClient()
    {
#ifndef __linux__ //windows
        WSADATA wsData;
        WORD ver = MAKEWORD(2, 2);

        int wsOk = WSAStartup(ver, &wsData);
        if (wsOk != 0)
        {
            std::cout << "Can't initialize winsok" << std::endl;
            return;
        }
#endif
    }
    BlClient(Bobj b):BlClient()
    {
        Connect(b,1);
    }
    ~BlClient()
    {
        close(clsock);
    }

public:
    void Connect(Bobj b,int port)
    {
        std::cout<<"MAC: " << b.GetStrMac() << "\n";
        clsock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
#ifndef __linux__ //windows
        addr.addressFamily = AF_BTH;
        addr.serviceClassId = RFCOMM_PROTOCOL_UUID;
        addr.port = port;
        addr.btAddr = *b.GetMac();
        
#else//linux
        addr.rc_family = AF_BLUETOOTH;
        addr.rc_channel = (uint8_t)1;
        addr.rc_bdaddr = *b.GetMac();
#endif // __linux__
        // set the connection parameters (who to connect to)
        
        std::cout << "START CONNECT\n";
        int status = connect(clsock, (struct sockaddr *)&addr, sizeof(addr));

        // send a message
        if (status < 0){
            std::cout << "ERROR CONNECT\n";
            perror("ERROR CONNECT");
            return;
        }
        std::cout << "CONNECT SUCCSESFUL\n";
        
    }
    void GetPacket() {
        
        while (true)
        {

            char hay[1024];
            int res = recV(clsock, hay, 1024);
            if (res < 0)
            {
                std::cout << "DISSCONNECT\n";
                close(clsock);
                break;
            }
            std::cout << "READ PACKET: " << hay << "\n";

        }
    }
    void sendMessage(std::string mess);
private:
    sockaddre addr= { 0 };
    int clsock;
};