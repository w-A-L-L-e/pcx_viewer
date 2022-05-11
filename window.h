/*=============================================================================
author        : Walter Schreppers
filename      : screen.h
created       : 30/4/2022 at 22:50:23
modified      : 
version       : 
copyright     : Walter Schreppers
bugreport(log): 
=============================================================================*/

#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <string>

class Window {

  public:
    //constructor & destructor
    //==========================
    Window(Uint32 width=640, Uint32 height=480, const std::string& title="SDL2", bool full_screen = false);
    ~Window();

    //public members
    //==============
    void handle_events();
    void clear();
    void setFullscreen(bool fs);
    void setBackground(SDL_Surface* image);
    void draw(bool present=true);
    SDL_Renderer* getRenderer(){ return renderer; }
    SDL_Window* getWindow(){ return window; }

    void printFPS();
    void showRenderInfo();
    void showDimensions();

    bool opened(){ return running; }
    bool closed(){ return !running; }

    //public locals
    //=============
    SDL_Event event;
    Uint32 width, height, center_x, center_y;

  private:
    //private members
    //===============
    void init();

    //private locals
    //==============
    bool fullscreen;
    bool running;
    std::string window_title;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

}; //end of class Window

#endif

