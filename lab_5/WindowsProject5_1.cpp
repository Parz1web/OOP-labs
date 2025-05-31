#include <windows.h>
#include <map>
#include <memory>

#define ID_FILE_EXIT 9001

class MessageHandler {
public:
    virtual ~MessageHandler() = default;
    virtual LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};


class PaintHandler : public MessageHandler {
public:
    LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        EndPaint(hwnd, &ps);
        return 0;
    }
};


class DestroyHandler : public MessageHandler {
public:
    LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override {
        PostQuitMessage(0);
        return 0;
    }
};


class CommandHandler : public MessageHandler {
public:
    CommandHandler(HWND hwnd) : hwnd_(hwnd) {}

    LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override {
        switch (LOWORD(wParam)) {
        case ID_FILE_EXIT:
            DestroyHandler destroyHandler;
            return destroyHandler.HandleMessage(hwnd, uMsg, wParam, lParam);
            
        }
        return 0;
    }

private:
    HWND hwnd_;
};

// Основной обработчик сообщений
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static std::map<UINT, std::unique_ptr<MessageHandler>> handlers;

    if (handlers.empty()) {
        handlers[WM_PAINT] = std::make_unique<PaintHandler>();
        handlers[WM_DESTROY] = std::make_unique<DestroyHandler>();
        handlers[WM_COMMAND] = std::make_unique<CommandHandler>(hwnd);
    }

    auto it = handlers.find(uMsg);
    if (it != handlers.end()) {
        return it->second->HandleMessage(hwnd, uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
    return 0;
}
