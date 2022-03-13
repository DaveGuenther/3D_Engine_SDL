# SDL-Template

Use this to create a basic started SDL project in VS Code using MinGW64 (Msys)


## Mingw Configuration:
Follow these instructions to set up VS Code with MinGW64: https://code.visualstudio.com/docs/cpp/config-mingw
Install to: c:\msys64\ 
1. Download MSys64: https://github.com/msys2/msys2-installer/releases/download/2022-01-28/msys2-x86_64-20220128.exe
2. Install to c:\Msys64\
3. At the end of the installer, run MSYS2 64bit
4. <code>pacman -Syu</code> type 'y' or 'yes' at every prompt.  MSYS2 terminal will close at the end
5. Run MSYS2 again
6. <code>pacman -Su</code> type 'y' or 'yes' at every prompt.
7. <code>pacman -S --needed base-devel mingw-w64-x86_64-toolchain</code> type 'y' or 'yes' at every prompt.

## SDL Configuration:
Follow these instructions to download and install the SDL 64 bit lib and Development Libraries: https://giovanni.codes/setup-sdl2-with-visual-studio-code-and-mingw64-on-windows/

1. download: SDL2-2.0.18-win32-x64.zip (64-bit Windows) -- https://www.libsdl.org/release/SDL2-2.0.18-win32-x64.zip
Copy the .DLL file in this to the build/ folder of the repo.  (.gitignore won't include it in the remote repo)

2. download: SDL2-devel-2.0.18-mingw.tar.gz (MinGW 32/64-bit) -- https://www.libsdl.org/release/SDL2-devel-2.0.18-mingw.tar.gz
Open the archive with 7zip and go down one later in the archive until you see a folder called "SDL2-2.0.18"
Extract that folder to c:\SDL\
If you did it right, you should have the following active path: c:\SDL\SDL2-2.0.18\x86_64-w64-mingw32\include



## Repo Structure:
There are two VS Code project directories:
- Engine (VS Code Project): This project folder include all the source, meshes, etc for the engine itself
- Unit Tests (VS Code Project): This project folder is intended for various unit test scripts for the various classes