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


#include"stdio.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
namespace core {
	int GetRealSize(std::vector<char> v);
}

#ifndef __linux__ //windows
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <ws2bth.h>
#include<BluetoothAPIs.h>
#include<bthsdpdef.h>
#include<Ws2bth.h>
#include<tchar.h>
#pragma comment(lib, "ws2_32.lib")
DEFINE_GUID(g_guidServiceClass, 0xb62c4e8d, 0x62cc, 0x404b, 0xbb, 0xbf, 0xbf, 0x3e, 0x3b, 0xbb, 0x13, 0x74);

#else//linux
#include <sys/socket.h>
#include <sys/types.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif // __linux__
//typedef
#ifndef __linux__ //windows

typedef struct _SOCKADDR_BTH sockaddre;
#define AF_BLUETOOTH AF_BTH
#define BTPROTO_RFCOMM BTHPROTO_RFCOMM
typedef BTH_ADDR bdaddr_t;
#else//linux
typedef int SOCKET;
typedef sockaddr_rc sockaddre;
#endif // __linux__


#ifndef __linux__ //windows
void close(SOCKET s);
int ba2str(BTH_ADDR* btaddr, const char* straddr);
int str2ba(char* str_bt_addr, BTH_ADDR* bt_addr);//for converting string to bluetooth address;
#endif // __linux__
int recV(int sock, char* buf, int size);
int senD(int sock, const char* buf, int size);