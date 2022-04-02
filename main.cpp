#include"include/blclient.h"


int main(int argc, char **argv)
{

    
    BlClient blcl;
    Bobj b("00:00:5e:00:53:af","PHONE");

    //Bobj b(GE, "TELE");
    blcl.Connect(b,200);
    
    return 0;
}
