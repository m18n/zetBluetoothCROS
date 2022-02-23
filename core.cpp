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
int ba2str(BTH_ADDR* btaddr, const char* straddr)
{
    int i;
    unsigned int aaddr[6];
    BTH_ADDR tmpaddr = 0;

    if (sscanf(straddr, "%02x:%02x:%02x:%02x:%02x:%02x",
        &aaddr[0], &aaddr[1], &aaddr[2],
        &aaddr[3], &aaddr[4], &aaddr[5]) != 6)
        return 1;
    *btaddr = 0;
    for (i = 0; i < 6; i++) {
        tmpaddr = (BTH_ADDR)(aaddr[i] & 0xff);
        *btaddr = ((*btaddr) << 8) + tmpaddr;
    }
    return 0;
}

#endif // __linux__