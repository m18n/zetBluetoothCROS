#include "include/bobj.h"
void Bobj::Inithiliz(bdaddr_t mac, std::string name)
{
    SetMac(mac);
    this->name = name;
}
void Bobj::Inithiliz(std::string mac, std::string name)
{
    SetStrMac(mac);
    this->name = name;
}
void Bobj::SetMac(bdaddr_t mac)
{
    this->mac = mac;
}
void Bobj::SetStrMac(std::string mac) {
    str2ba(&mac[0], &this->mac);
    this->strmac=mac;
}
void Bobj::SetName(std::string name)
{
    this->name = name;
}
std::string Bobj::GetName()
{
    return name;
}
bdaddr_t *Bobj::GetMac()
{
    return &mac;
}
std::string Bobj::GetStrMac()
{
    return strmac;
}
Bobj::Bobj()
{
    strmac = "00:00:00:00:00:00";
    name = "[ucnow]\n";
}
Bobj::Bobj(bdaddr_t mac, std::string name)
{
    Inithiliz(mac, name);
}
Bobj::Bobj(std::string mac, std::string name) {
    Inithiliz(mac, name);
}