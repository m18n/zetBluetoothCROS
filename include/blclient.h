#pragma once
#include"bobj.h"
#include "bl.h"
#include <bluetooth/rfcomm.h>
class BlClient
{
public:
    BlClient()
    {
    }
    BlClient(Bobj b)
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
        
        // set the connection parameters (who to connect to)
        addr.rc_family = AF_BLUETOOTH;
        addr.rc_channel = (uint8_t)1;
        addr.rc_bdaddr = *b.GetMac();
        int status = connect(clsock, (struct sockaddr *)&addr, sizeof(addr));

        // send a message
        if (status < 0){
            perror("ERROR CONNECT");
            return;
        }
        std::cout << "CONNECT\n";
        
    }

private:
    sockaddr_rc addr= { 0 };
    int clsock;
};