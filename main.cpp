#pragma once
#include"include/blclient.h"
#include"include/blserver.h"
#include"include/funjs.h"
using namespace ultralight;
#define WINDOW_WIDTH    900
#define WINDOW_HEIGHT   600

int main(int argc, char **argv)
{
    std::cout << "STARt\n";
    auto app = App::Create();

    
    auto window = Window::Create(app->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT, false,
        kWindowFlags_Titled);    
    app->set_window(window);
    VServClient vs;
    vs.SetWin(window);
    funjs::RegistrFunVServClient(&vs);
    vs.SetTitle("BLUETOOTH\n");
    app->Run();
    
    return 0;
}
