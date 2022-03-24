# SDL based 3D Engine

This project is based on mingw (g++) and SDL (Simplified DirectMedia Layer) and includes VSCode project files


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

## Repo Structure:
There are two VS Code project directories:
- Engine (VS Code Project): This project folder include all the source, meshes, etc for the engine itself
- Unit Tests (VS Code Project): This project folder is intended for various unit test scripts for the various classes
