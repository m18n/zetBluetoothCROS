#pragma once
#ifndef __linux__ //windows
#if defined( DLLAPI )
#define DLLAPI __declspec(dllexport)
#else // !BUILDING_DLL
#define DLLAPI __declspec(dllimport)
#endif // BUILDING_DLL
#else//linux
#define DLLAPI
#endif // __linux__
#include <stdio.h>
#include <iostream>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <vector>
#include "bobj.h"
class BL
{


public:
    BL()
    {
#ifndef __linux__

#else
        dev_id = hci_get_route(NULL);
        sock = hci_open_dev(dev_id);
        if (dev_id < 0 || sock < 0)
        {
            perror("opening socket");
            exit(1);
        }
#endif // __linux__
        
    }
    ~BL(){
        close(sock);
    }
public:
    std::vector<Bobj> GetBobjConnect(int sock, int dev_id);
public:
    int GetSock(){
        return sock;
    }
    int GetDev_id(){
        return dev_id;
    }
private:
    std::vector<Bobj> GetAdressConnect(int sock, int dev_id);
private:
    int dev_id = 0;
    int sock = 0;
};

