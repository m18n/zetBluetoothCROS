#include"include/core.h"
std::fstream core::clog;
std::vector<char> core::vlog;
int core::last_vlog=0;
cx::loginf* cx::linf;
int core::GetRealSize(std::vector<char> v) {
    int i = 0;
    for (i = 0; i < v.size(); i++) {
        if (v[i] == '\0') {
            break;
        }
    }
    return i;

}
void CreateLibrary() {
    core::vlog.resize(1000);
    core::clog.open("logzetbl.txt", std::fstream::out | std::fstream::trunc);
    core::clog.close();
    core::clog.open("logzetbl.txt", std::fstream::out | std::fstream::app);
    core::clog.rdbuf()->pubsetbuf(&core::vlog.front(), core::vlog.size());
    core::clog << "START LIBRARY\n";
 
    cx::linf = new cx::loginf();
}
void DestroyLibrary() {
    core::clog.flush();
    core::clog.close();
    delete cx::linf;
}
void* GetLOG() {
    cx::linf->log = (void*)&core::vlog[core::last_vlog];
    std::cout <<"GETLOG SEND\n" << &core::vlog[core::last_vlog] << "\n";
    int realsize = core::GetRealSize(core::vlog);
    cx::linf->end = realsize - core::last_vlog;
    std::cout << "END: " << cx::linf->end << "\n";
    core::last_vlog = realsize;
    return (void*)cx::linf;
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