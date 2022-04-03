#include"include/blclient.h"
#include <AppCore/App.h>
#include <AppCore/Window.h>
#include <AppCore/Overlay.h>

using namespace ultralight;
#define WINDOW_WIDTH    900
#define WINDOW_HEIGHT   600
class MyApp : public WindowListener,
    public ViewListener {
    RefPtr<App> app_;
    RefPtr<Window> window_;
    RefPtr<Overlay> ov;
    BlClient blcl;
public:
    MyApp() {
        ///
        /// Create our main App instance.
        ///
        app_ = App::Create();

        ///
        /// Create a resizable window by passing by OR'ing our window flags with
        /// kWindowFlags_Resizable.
        ///
        window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
            false, kWindowFlags_Titled | kWindowFlags_Resizable);

        ///
        /// Set the title of our window.
        ///
        window_->SetTitle("Telegram");

        ///
        /// Tell our app to use 'window' as our main window.
        ///
        /// This call is required before creating any overlays or calling App::Run
        ///
        app_->set_window(*window_.get());

        ///
        /// Create the overlays for our left and right panes-- we don't care about
        /// their initial size and position because they'll be set when we call
        /// OnResize() below.
        ///
        ov = Overlay::Create(*window_.get(), 1, 1, 0, 0);

        ///
        /// Force a call to OnResize to perform initial layout and sizing of our
        /// left and right overlays.
        ///
        OnResize(window_->width(), window_->height());

        ///
        /// Load some HTML into our left and right overlays.
        ///
        ov->view()->LoadURL("file:///index.html");

        ///
        /// Register our MyApp instance as a WindowListener so we can handle the
        /// Window's OnResize event below.
        ///
        window_->set_listener(this);

        ///
        /// Register our MyApp instance as a ViewListener so we can handle the
        /// Views' OnChangeCursor event below.
        ///
        ov->view()->set_view_listener(this);
       

    }
    
    void Connect(std::string mac,int port) {
        Bobj b(mac, "PHONE");
        //Bobj b(GE, "TELE");
        blcl.Connect(b,port);
    }
    virtual ~MyApp() {}

    ///
    /// Inherited from WindowListener, not used.
    ///
    virtual void OnClose() override {}

    ///
    /// Inherited from WindowListener, called when the Window is resized.
    ///
    virtual void OnResize(uint32_t width, uint32_t height) override {
        ov->Resize(width, height);
    }

    ///
    /// Inherited from ViewListener, called when the Cursor changes.
    ///
    virtual void OnChangeCursor(ultralight::View* caller,
        Cursor cursor) {
        window_->SetCursor(cursor);
    }

    void Run() {
        app_->Run();
        Connect("00:00:5e:00:53:af", 1);
    }
};

int main(int argc, char **argv)
{
    std::cout << "STARt\n";
    MyApp app;
    app.Run();
    
    return 0;
}
