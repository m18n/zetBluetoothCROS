#pragma once
#include <iostream>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
class Bobj
{
public:
    Bobj();
    Bobj(bdaddr_t mac, std::string name);

public:
    void Inithiliz(bdaddr_t mac, std::string name);
    void SetMac(bdaddr_t mac);
    void SetName(std::string name);
    std::string GetName();
    bdaddr_t *GetMac();
    std::string GetStrMac();

private:
    bdaddr_t mac;
    std::string strmac;
    std::string name;
};