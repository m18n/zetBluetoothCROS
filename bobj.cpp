#include "include/bobj.h"
void Bobj::Inithiliz(bdaddr_t mac, std::string name)
{
    SetMac(mac);
    this->name = name;
}
void Bobj::SetMac(bdaddr_t mac)
{
    this->mac = mac;
    ba2str(&this->mac, &strmac[0]);
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