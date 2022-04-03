#include"include/core.h"
int core::GetRealSize(std::vector<char> v) {
    int i = 0;
    for (i = 0; i < v.size(); i++) {
        if (v[i] == '\0') {
            break;
        }
    }
    return i;

}

#ifndef __linux__ //windows
void close(SOCKET s) {
	closesocket(s);
}

int str2ba(char* str_bt_addr, BTH_ADDR* bt_addr)//for converting string to bluetooth address
{
    unsigned int addr[6];
    if (sscanf_s(str_bt_addr, "%02x:%02x:%02x:%02x:%02x:%02x",
        &addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]) != 6)
    {
        return 1;
    }
    *bt_addr = 0;
    BTH_ADDR tmpaddr;
    int i;
    for (i = 0; i < 6; ++i)
    {
        tmpaddr = (BTH_ADDR)(addr[i] & 0xff);
        *bt_addr = ((*bt_addr) << 8) + tmpaddr;
    }
    return 0;
}

#endif // __linux__