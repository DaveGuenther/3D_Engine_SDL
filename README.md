# SDL based 3D Engine

This project is based on mingw (g++) and SDL (Simplified DirectMedia Layer) and includes VSCode project files

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-03-23.png">
  <br><i>Engine Screenshot from 3/23/2022</i>
</p>

## Installation
### Mingw Configuration:
Follow these instructions to set up VS Code with MinGW64: https://code.visualstudio.com/docs/cpp/config-mingw  or perform the following steps to match versions used by this project:
Install to: c:\msys64\ 
1. Download MSys64: https://github.com/msys2/msys2-installer/releases/download/2022-01-28/msys2-x86_64-20220128.exe
2. Install to c:\Msys64\
3. At the end of the installer, run MSYS2 64bit
4. <code>pacman -Syu</code> type 'y' or 'yes' at every prompt.  MSYS2 terminal will close at the end
5. Run MSYS2 again
6. <code>pacman -Su</code> type 'y' or 'yes' at every prompt.
7. <code>pacman -S --needed base-devel mingw-w64-x86_64-toolchain</code> type 'y' or 'yes' at every prompt.

### SDL Configuration:
Follow these instructions to download and install the SDL 64 bit lib and Development Libraries: https://giovanni.codes/setup-sdl2-with-visual-studio-code-and-mingw64-on-windows/  or perform the following steps to match versions used by this project:

1. download: SDL2-2.0.18-win32-x64.zip (64-bit Windows) -- https://www.libsdl.org/release/SDL2-2.0.18-win32-x64.zip
Copy the .DLL file in this to the build/ folder of the repo after you've cloned it.  (.gitignore won't include it in the remote repo)

2. download: SDL2-devel-2.0.18-mingw.tar.gz (MinGW 32/64-bit) -- https://www.libsdl.org/release/SDL2-devel-2.0.18-mingw.tar.gz
Open the archive with 7zip and go down one later in the archive until you see a folder called "SDL2-2.0.18"
Extract that folder to c:\SDL\
If you did it right, you should have the following active path: c:\SDL\SDL2-2.0.18\x86_64-w64-mingw32\include


## Running the Engine
1. Once in VS Code, open the 'Engine_(VS_Code_Project)' folder
2. Verify that the paths in the .json files in your .vscode folder are valid particulartly for mingw and SDL
3. Open src/game.cpp and run the file (Ctrl+F5)
