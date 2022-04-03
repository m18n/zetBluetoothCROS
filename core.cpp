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
int recV(int sock, char* buf, int size) {

    int ret = recv(sock, buf, size, MSG_PEEK);

    int indexs = 0;
    for (int i = 0; i < ret; i++) {
        if (buf[i] == ':') {
            indexs = i;
            break;
        }
    }
    char strsize[10];
    ret = recv(sock, strsize, indexs + 1, NULL);
    strsize[indexs] = '\0';
    int realsize = atoi(strsize);
    ret = recv(sock, buf, realsize, NULL);
    return ret;
}
int senD(int sock, const char* buf, int size) {
    static std::vector<char> vec(500);
    std::string sizestr = std::to_string(size);
    int indexs = sizestr.length();
    memcpy(&vec[0], &sizestr[0], indexs);
    vec[indexs] = ':';
    memcpy(&vec[indexs + 1], &buf[0], size);
    int allsize = indexs + size + 2;
    vec[allsize - 1] = '\0';
    return send(sock, &vec[0], allsize-1, NULL);
}
#endif // __linux__