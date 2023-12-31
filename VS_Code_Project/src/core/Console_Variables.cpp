#include "Console_Variables.h"
#include <SDL2/SDL.h>

ConsoleData::ConsoleData(){
    // Initial Renderer Settings
    this->renderer.triggerRendererRestart=true;
    this->renderer.renderScreenType = WINDOW_FULLSCREEN_DESKTOP;
    this->renderer.renderCanvas_W = 400;
    this->renderer.renderCanvas_H = 225;
    this->renderer.renderScreenResolution_W=400;
    this->renderer.renderScreenResolution_H=225;  

    // Initial Rasterizer Settings
    this->rasterizer.polyType = TEXTURE;
    this->rasterizer.drawPolyEdges = false;
    this->rasterizer.colorFrustumClippedTris = false;    
    this->rasterizer.ambientLightingType = DEPTH_POLY;

    // Initial Log settings
    this->logMessages.inputLogs = false;
}