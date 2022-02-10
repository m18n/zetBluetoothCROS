#pragma once
#include "bobj.h"
#include "bl.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <bluetooth/rfcomm.h>
class BlServer
{
public:
    BlServer()
    {
    }

    ~BlServer()
    {
        close(servsock);
    }

public:
    void ServerInit(uint8_t channel)
    {
        servsock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        bdaddr_t bdaddr_any = {0, 0, 0, 0, 0, 0};
        // bind socket to port 1 of the first available
        // local bluetooth adapter
        addr.rc_family = AF_BLUETOOTH;
        addr.rc_bdaddr = bdaddr_any;
        addr.rc_channel = channel;
    }
    
   
    void ServerStart()
    {
        bind(servsock, (struct sockaddr *)&addr, sizeof(addr));

        // put socket into listening mode
        listen(servsock, 1);

        // accept one connection

       
        int client=accept(servsock, (struct sockaddr *)&addr, &opt);
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
    sockaddr_rc addr = {0};
    socklen_t opt = sizeof(addr);
    int servsock;
};