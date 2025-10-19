#include <windows.h>
#include <iostream>

namespace {
HHOOK g_mouseHook = nullptr;

void sendCharacter(wchar_t ch) {
    INPUT input{};
    input.type = INPUT_KEYBOARD;
    input.ki.dwFlags = KEYEVENTF_UNICODE;
    input.ki.wScan = ch;
    SendInput(1, &input, sizeof(INPUT));

    INPUT inputUp = input;
    inputUp.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
    SendInput(1, &inputUp, sizeof(INPUT));
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        switch (wParam) {
            case WM_RBUTTONDOWN:
                sendCharacter(L'a');
                return 1; // block the original right click down event
            case WM_RBUTTONUP:
            case WM_RBUTTONDBLCLK:
                return 1; // block other right click events
            default:
                break;
        }
    }

    return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
}

void messageLoop() {
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
}

int main() {
    g_mouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, nullptr, 0);

    if (!g_mouseHook) {
        std::cerr << "Failed to install mouse hook. Error: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Mouse hook installed. Press Ctrl+C in this console to exit." << std::endl;
    messageLoop();

    if (g_mouseHook) {
        UnhookWindowsHookEx(g_mouseHook);
    }

    return 0;
}
