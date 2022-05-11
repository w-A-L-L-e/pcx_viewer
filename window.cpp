/*=============================================================================
author        : Walter Schreppers
filename      : window.cpp
created       : 30/4/2022 at 22:50:23
modified      :
version       :
copyright     : Walter Schreppers
bugreport(log):
=============================================================================*/

#include "window.h"
#include <iostream>
#include <string>

/*-----------------------------------------------------------------------------
name        : init
description : initialize SDL screen
parameters  :
return      : void
exceptions  :
algorithm   : trivial
-----------------------------------------------------------------------------*/
void Window::init() {
  SDL_Init(SDL_INIT_EVERYTHING);

  window =
      SDL_CreateWindow(this->window_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);

  // the VSYNC makes it cap at 60fps (or whatever the screen refresh is) and
  // have smooth animation
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // showRenderInfo(renderer);

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, width, height);

  running = true;
  setFullscreen(this->fullscreen);
}

Window::Window(Uint32 width, Uint32 height, const std::string& title, bool full_screen) {
  this->width = width;
  this->height = height;
  this->center_x = width / 2;
  this->center_y = height / 2;
  this->window_title = title;
  this->fullscreen = full_screen;

  window = NULL;
  renderer = NULL;
  texture = NULL;

  init();
}

/*-----------------------------------------------------------------------------
name        : ~Window
description : destructor
parameters  :
return      :
exceptions  :
algorithm   : trivial
-----------------------------------------------------------------------------*/
Window::~Window() {
  running = false;
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Quit();
}

void Window::setFullscreen(bool fs){
  if (fs) {
    SDL_SetWindowFullscreen(window,
                            // SDL_WINDOW_FULLSCREEN);
                            SDL_WINDOW_FULLSCREEN_DESKTOP);
  } else {
    SDL_SetWindowFullscreen(window, 0);
  }
}

void Window::handle_events() {

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN: // SDL_KEYUP also exists
      if (event.key.keysym.scancode == SDL_SCANCODE_F) {
        fullscreen = !fullscreen;
        setFullscreen(fullscreen); 
      }
      if (event.key.keysym.scancode == SDL_SCANCODE_Q) {
        running = SDL_FALSE;
      }
      break;
    default:
      break;
    }
  }
}

void Window::clear() {
  // clear screen
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
}

void Window::draw(bool present) {
  // copy texture created from pcx onto window
  // passing null, null will make it stretch nicely on fullwindow
  // if((SDL_RenderCopy(renderer, tex, NULL, &destr)) < 0){
  if((SDL_RenderCopy(renderer, texture, NULL, NULL)) < 0){
    std::cout << SDL_GetError() << std::endl;
    exit(-1);
  }

  if (present) {
    // show renderer on screen
    SDL_RenderPresent(renderer);
  }
}

void Window::setBackground(SDL_Surface* image){
  //create destination rectangle (optional)
  //SDL_Rect destr;
  //destr.x = 0;
  //destr.y = 0;
  //destr.w = image->w;
  //destr.h = image->h;
  texture = SDL_CreateTextureFromSurface(renderer, image);

  // cleanup and check if texture was created
  SDL_FreeSurface(image);
  if(texture == NULL){
    std::cout << SDL_GetError() << std::endl;
    exit(-1);
  }
}

void Window::printFPS() {
  static Uint32 countedFrames = 0;
  static Uint32 startTick = SDL_GetTicks();
  Uint32 ticks = SDL_GetTicks();
  countedFrames++;
  if (countedFrames % 30 == 0) {
    float avgFPS = (int)countedFrames / ((ticks - startTick) / 1000.f);
    printf("fps %f\n", avgFPS);
  }
  if (countedFrames % 150 == 0) {
    startTick = ticks;
    countedFrames = 0;
  }
}

void Window::showRenderInfo() {
  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  std::cout << "Renderer name: " << info.name << std::endl;
  std::cout << "Texture formats: " << std::endl;
  for (Uint32 i = 0; i < info.num_texture_formats; i++) {
    std::cout << SDL_GetPixelFormatName(info.texture_formats[i]) << std::endl;
  }
}



void Window::showDimensions(){
  int window_w = 0;
  int window_h = 0;
  SDL_GL_GetDrawableSize(window, &window_w, &window_h);
  std::cout << "window size=" << window_w << " x " << window_h << std::endl;
  //on my retina mac fullwindow= window size=1280 x 800
}


 /* other sdl image loading and saving we might use in future vesion:
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadICO_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadCUR_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadBMP_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadGIF_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadJPG_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadLBM_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadPCX_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadPNG_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadPNM_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadSVG_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadTGA_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadTIF_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadXCF_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadXPM_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadXV_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_LoadWEBP_RW(SDL_RWops *src);
    extern DECLSPEC SDL_Surface * SDLCALL IMG_ReadXPMFromArray(char **xpm);

    // Individual saving functions 
    extern DECLSPEC int SDLCALL IMG_SavePNG(SDL_Surface *surface, const char *file);
    extern DECLSPEC int SDLCALL IMG_SavePNG_RW(SDL_Surface *surface, SDL_RWops *dst, int freedst);
    extern DECLSPEC int SDLCALL IMG_SaveJPG(SDL_Surface *surface, const char *file, int quality);
    extern DECLSPEC int SDLCALL IMG_SaveJPG_RW(SDL_Surface *surface, SDL_RWops *dst, int freedst, int quality);
  */


