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
            cerr << "Can't initialize winsok" << endl;
            return;
        }
#endif
    }
    BlClient(Bobj b):BlClient()
    {
        Connect(b);
    }
    ~BlClient()
    {
        close(clsock);
    }

public:
    void Connect(Bobj b)
    {
        clsock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
#ifndef __linux__ //windows
        addr.addressFamily = AF_BTH;
        addr.serviceClassId = RFCOMM_PROTOCOL_UUID;
        addr.port = 1;
        addr.btAddr = *b.GetMac();
#else//linux
        addr.rc_family = AF_BLUETOOTH;
        addr.rc_channel = (uint8_t)1;
        addr.rc_bdaddr = *b.GetMac();
#endif // __linux__
        // set the connection parameters (who to connect to)
       
        int status = connect(clsock, (struct sockaddr *)&addr, sizeof(addr));

        // send a message
        if (status < 0){
            perror("ERROR CONNECT");
            return;
        }
        std::cout << "CONNECT\n";
        
    }

private:
    sockaddre addr= { 0 };
    int clsock;
};