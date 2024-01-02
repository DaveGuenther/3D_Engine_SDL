#ifndef CONSOLE_VARIABLES_H
#define CONSOLE_VARIABLES_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

enum render_screen_type {WINDOW_FULLSCREEN, WINDOW_FULLSCREEN_DESKTOP, WINDOW_RESIZABLE};
enum rasterizer_type {TEXTURE, SOLID, WIREFRAME};
enum ambient_light_type {DEPTH_POLY, DEPTH_PIXEL};

class ConsoleRenderData{
    public:
        
        bool triggerRendererRestart;
        render_screen_type renderScreenType;
        Uint32 renderCanvas_W;
        Uint32 renderCanvas_H;
        Uint32 renderScreenResolution_W;
        Uint32 renderScreenResolution_H;  

};

class ConsoleRasterizerData{
    public:
        rasterizer_type polyType;
        bool drawPolyEdges;
        bool colorFrustumClippedTris;
        ambient_light_type ambientLightingType;
};

class Log{
    public:
        bool inputLogs;
};

class ConsoleCommandLog{
    public:
        std::string currentCommand; // current console command to be parsed
        std::vector<std::string> commandHistory;  // complete list of console commands
        uint8_t historyPtr; // index in history when using up and down arrow keys in console to navigate the history
};

class ConsoleData{
    public:
        ConsoleRenderData renderer;
        ConsoleRasterizerData rasterizer;
        Log logMessages;
        ConsoleCommandLog consoleCommandLog;
        ConsoleData();




};

#endif