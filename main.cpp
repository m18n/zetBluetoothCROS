#include"include/blclient.h"


int main(int argc, char **argv)
{

    BL bl;
    char name[248] = {0};

    std::vector<Bobj> bobj = bl.GetBobjConnect(bl.GetSock(), bl.GetDev_id());
    for (int i = 0; i < bobj.size(); i++)
    {
        std::cout << "ADDRESS: " << bobj[i].GetStrMac() << " Name: " << bobj[i].GetName() << "\n";
    }
    if(bobj.size()==0)
        return 0;
    BlClient blcl;
    blcl.Connect(bobj[0]);
    return 0;
}
