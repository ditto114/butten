# butten

This repository contains a small Windows utility that intercepts right mouse button events and injects the `a` key instead.

## Building

Use any Windows C++ compiler (e.g., MSVC's `cl.exe` or MinGW's `g++`) to build the program:

```powershell
cl.exe /EHsc mouse_interceptor.cpp user32.lib
```

or

```powershell
g++ mouse_interceptor.cpp -municode -luser32
```

## Running

Run the resulting executable from a console. Once the hook is installed, right-clicking will no longer trigger the default context menu or other right-click behavior. Instead, an `a` character will be injected. Press `Ctrl+C` in the console window to stop the program.
