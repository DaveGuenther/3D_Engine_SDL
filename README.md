# SDL-Template

Use this to create a basic started SDL project in VS Code using MinGW64 (Msys)


## Mingw Configuration:
Follow these instructions to set up VS Code with MinGW64: https://code.visualstudio.com/docs/cpp/config-mingw
Install to: c:\msys64\ 

## SDL Configuration:
Follow these instructions to download and install the SDL 64 bit lib and Development Libraries: https://giovanni.codes/setup-sdl2-with-visual-studio-code-and-mingw64-on-windows/

Specifically, download:
- SDL2-2.0.18-win32-x64.zip (64-bit Windows)
Copy the .DLL file in this to the build/ folder of the repo.  (.gitignore won't include it in the remote repo)

- SDL2-devel-2.0.18-mingw.tar.gz (MinGW 32/64-bit)
Extract to c:\SDL\

