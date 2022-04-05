#include"include/blserver.h"

void StartServer(void* blserver,uint8_t channel) {
	BlServer* bl = (BlServer*)blserver;
	bl->ServerInit();
	bl->ServerStart();
}
void BlServer::ServerInit()
{
    std::cout << "Server Init\n";
    servsock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (servsock == INVALID_SOCKET)
    {
        printf("Failed to get bluetooth socket! %s\n");
        exit(1);
    }
    // bind socket to port 1 of the first available
    // local bluetooth adapter
#ifndef __linux__ //windows
    addr.addressFamily = AF_BTH;
  
    addr.btAddr = 0;
    addr.serviceClassId = GUID_NULL;
    addr.port = BT_PORT_ANY;
#else//linux
    bdaddr_t bdaddr_any = { 0, 0, 0, 0, 0, 0 };
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_bdaddr = bdaddr_any;
    addr.rc_channel = channel;
#endif // __linux__


}
void BlServer::sendMessage(std::string mess) {
    senD(client, mess.c_str(), mess.length() + 1);
}
void BlServer::GetPacket() {
    std::cout << "START GET PAKCET\n";
    if (client = accept(servsock, (struct sockaddr*)&addr, &opt)) {

        std::cout << "CONNECT CLIENT\n";
    }
    while (true)
    {
        if (!serverpr) {
            std::cout << "STOP GET PACKET\n";
            break;
        }
        sendMessage("YOU CONNECT SERVER");
        char hay[1024];
       
        int res = recV(client, hay, 1024);
        if (!serverpr) {
            std::cout << "STOP GET PACKET\n";
            break;
        }
        if (res <= 0)
        {
            
            std::cout << "DISSCONNECT\n";
            close(client);
            if (client = accept(servsock, (struct sockaddr*)&addr, &opt)) {
                std::cout << "CONNECT CLIENT\n";
                sendMessage("YOU CONNECT SERVER");
            }
            continue;
        }else
            std::cout << "RECV: " << hay << "\n";

    }
}
void BlServer::ServerStart()
{
   
    std::cout << "SERVER STARTT\n";
    if (0 != bind(servsock, (struct sockaddr*)&addr, sizeof(addr)))
    {
        printf("%s\n", GetLastError());
    }
    else
    {
        printf("\nBinding Successful....\n");
        int length = sizeof(SOCKADDR_BTH);
        getsockname(servsock, (sockaddr*)&addr, &length);
        wprintf(L"Local Bluetooth device is %04x%08x \nServer channel = %d\n",
            GET_NAP(addr.btAddr), GET_SAP(addr.btAddr), addr.port);
    }
   
    if (0 != listen(servsock, 1))
    {
        std::cout << "ERROR LISTEN\n";
    }

    WSAQUERYSET service;
    memset(&service, 0, sizeof(service));
    service.dwSize = sizeof(service);
    service.lpszServiceInstanceName = _T("Accelerometer Data...");
    service.lpszComment = _T("Pushing data to PC");

    GUID serviceID = OBEXFileTransferServiceClass_UUID;

    service.lpServiceClassId = &serviceID;
    service.dwNumberOfCsAddrs = 1;
    service.dwNameSpace = NS_BTH;

    CSADDR_INFO csAddr;
    memset(&csAddr, 0, sizeof(csAddr));
    csAddr.LocalAddr.iSockaddrLength = sizeof(SOCKADDR_BTH);
    csAddr.LocalAddr.lpSockaddr = (sockaddr*)&addr;
    csAddr.iSocketType = SOCK_STREAM;
    csAddr.iProtocol = BTHPROTO_RFCOMM;
    service.lpcsaBuffer = &csAddr;

    if (0 != WSASetService(&service, RNRSERVICE_REGISTER, 0))
    {
        printf("Service registration failed....");
        
    }
    else
    {
        printf("\nService registration Successful....\n");
    }
    printf("\nBefore accept.........\n");

    serverpr = true;
   
    std::thread th(&BlServer::GetPacket,this);
    th.detach();
    
}
void BlServer::ServerStop() {
    if (serverpr) {
        
        closesocket(client);
        closesocket(servsock);
        serverpr = false;
    }
   
}