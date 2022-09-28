# SDL based 3D Engine

This is a personal learning project that uses the core math and code presented by <b>javidx9</b> through his youtube tutorial series: https://youtu.be/ih20l3pJoeU.  I've added additional code to build an engine using an OOP approach and add in other things like input mangement classes and possibly simple physics.  The goal is to get to the point where the engine can load and render a small 3D map with the following functionality:
- Backface Culling
- Simple Lighting
- Camera Support
- Input Manager for FPS style control
- Solid Color Triangle Rasterization
- Surface Collision (not being able to walk through walls)
- Texturemapping

Everything uses software rendering (no open GL support) in an effort to build something similar to what might have been possible in the mid 90's but on stronger hardware.

This project is based on mingw (g++) and SDL (Simplified DirectMedia Layer) and includes VSCode project files


<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-07-29%20Texturemapped.png">
  <br><i>Engine Screenshot - Texturemapped Cube Rendered! 7/29/2022</i>
</p>
<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-07-13.png">
  <br><i>IRL Screenshot - Debug Cube to help with texturemapping 7/13/2022 </i>
</p>
<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-07-05%20Blender%20Cube.png">
  <br><i>Blender Screenshot - Texturemapped Test Cube 7/5/2022 </i>
</p>
<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/Pirate%20Cave%20-%20walkthrough.gif">
  <br><i>Engine Screenshot - Pirate Cave Walkthrough (Omnidirectional lighting) 5/27/2022</i>
</p>

<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/cave%20omni%202.PNG">
  <br><i>Engine Screenshot - Omnidirectional Lighting (position of camera shoots out light in all directions) 5/27/2022</i>
</p>

<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/cave%20conincal%202.PNG">
  <br><i>Engine Screenshot - Conical Lighting (light shoots out in the direction the camera is facing) 5/27/2022</i>
</p>

<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-04-03_Rasterized_dimmed.png">
  <br><i>Engine Screenshot - Triangle Rasterization 4/3/2022</i>
</p>

<br>
<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-04-03_back_face_culling.png">
  <br><i>Engine Screenshot - Backface Culling 4/3/2022</i>
</p>

<br> 

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-03-23.png">
  <br><i>Engine Screenshot - Wireframe Primitives 3/23/2022</i>
</p>



## Windows Installation
### Msys/Mingw Configuration:
Follow these instructions to set up VS Code with MinGW64: https://code.visualstudio.com/docs/cpp/config-mingw  or perform the following steps to match versions used by this project:
Install to: c:\msys64\ 
1. Download MSys64: https://github.com/msys2/msys2-installer/releases/download/2022-01-28/msys2-x86_64-20220128.exe
2. Install to c:\Msys64\
3. At the end of the installer, run MSYS2 64bit
4. <code>pacman -Syu</code> type 'y' or 'yes' at every prompt.  MSYS2 terminal will close at the end
5. Run MSYS2 again
6. <code>pacman -Su</code> type 'y' or 'yes' at every prompt.
7. <code>pacman -S --needed base-devel mingw-w64-x86_64-toolchain</code> type 'y' or 'yes' at every prompt.
8. <code>pacman --needed -Sy bash pacman pacman-mirrors msys2-runtime</code> type 'y' or 'yes' at every prompt.
9. <code>pacman -S mingw-w64-x86_64-clang</code> type 'y' or 'yes' at every prompt.
This should install both g++ and clang++.  
10. <code>pacman -S vim</code> type 'y' or 'yes' at every prompt.
11. Add Clang++ and g++ to your Msys path.  Run Msys to get to prompt in home folder.  type <code>vim .bash_profile</code> (install vim with <code>pacman -S vim</code> if needed).  Go to end of file and add a path definition to point your Msys terminal to clang++ and g++ directories.  In my case I used <code>PATH="/mingw64/bin:${PATH}"</code>.  Save changes to the file and restart Msys
12. Install git if needed in Msys <code>pacman -S git</code> type 'y' or 'yes' at every prompt.
13. From Msys home (~) folder, clode this repo <code>git clone git@github.com:DaveGuenther/3D_Engine_SDL.git</code>

### SDL Configuration:
Follow these instructions to download and install the SDL 64 bit lib and Development Libraries: https://giovanni.codes/setup-sdl2-with-visual-studio-code-and-mingw64-on-windows/  or perform the following steps to match versions used by this project:

Visit https://www.libsdl.org/release/ for most recent SDL releases (referencing items 1 and 2 below)
1. download: SDL2-2.0.18-win32-x64.zip (64-bit Windows) -- https://www.libsdl.org/release/SDL2-2.0.18-win32-x64.zip
Copy the .DLL file in this to the build/ folder of the repo after you've cloned it.  (.gitignore won't include it in the remote repo)

2. download: SDL2-devel-2.0.18-mingw.tar.gz (MinGW 32/64-bit) -- https://www.libsdl.org/release/SDL2-devel-2.0.18-mingw.tar.gz
Open the archive with 7zip and go down one level in the archive until you see a folder called "SDL2-2.0.18"
Extract that folder to c:\SDL\
If you did it right, you should have the following active path: c:\SDL\SDL2-2.0.18\x86_64-w64-mingw32\include

Visit https://www.libsdl.org/projects/SDL_image/release for most recent SDL_image releases (recerending items 3 and 4 below)
3. download: SDL2_image-2.0.5-win32-x64.zip (64-bit Windows) -- https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5-win32-x64.zip
Copy the .DLL file in this archive to the build/ folder off the repo after you've cloned it.

4. download: SDL2_image-devel-2.0.5-mingw.tar.gz (MinGW 32/64-bit) -- https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz
Open the archive with 7zip and go down two levels in the archive until you see the folder "SDL2_image-2.0.5/x86_64-w64-mingw32/"
Extract that folder to c:\SDL\SDL2-2.0.18\
If you did it right, you should have the file SDL_image.h located in the following active path: C:\SDL\SDL2-2.0.18\x86_64-w64-mingw32\include\SDL\

## Running the Engine
1. Once in VS Code, open the 'Engine_(VS_Code_Project)' folder
2. In a terminal, run <code>make all</code> to build the target without debug information built in.  Run <code>make debug</code> to build the target with debug information built in
3. To switch back and forth between g++ and clang++ compilers, use the <code>$(CC)</code> variable in the makefile

## Documentation
UML diagrams were built on a freeware tool called Dia using out-of-the-box shapes.  It can be found here: http://dia-installer.de/download/index.html.en.  As adjustments are made to the UML diagram, it will also be exported as a multi-page PDF in the Design Diagrams folder
