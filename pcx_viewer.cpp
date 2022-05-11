/*=============================================================================
author        : Walter Schreppers
filename      : main.cpp
created       : 11/5/2022 at 18:50:23
modified      : 11/5/2022
version       :
copyright     : Walter Schreppers
description   : Minimal pcx viewing utility. opens and displays pcx image files
=============================================================================*/

#include "window.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void showUsage(const std::string& exename){
  using namespace std;
  cerr << "Usage " << exename << "[-fs] <pcx file>" << endl << endl;
  cerr << "pcx file is mandatory" << endl;
  cerr << "optional -fs opens in full screen mode" << endl;
}

void showAbout(const std::string& image_file){
  using namespace std;
  cout << "===========================================" << endl;
  cout << "           Tiny PCX viewer" << endl;
  cout << "===========================================" << endl;
  cout << "opening '" << image_file << "'" << endl;
  cout << endl;
  cout << "Press 'f' to toggle fullwindow, 'q' to quit" << endl;
}



int main(int argc, char **argv) {
  using namespace std;
  string image_file = "";
  bool full_screen = false;

  if (argc < 2) {
    showUsage(argv[0]); 
    return 1;
  }

  if(argc == 3){
    image_file = argv[2];
    full_screen = true;
  }
  else{
    image_file = argv[1];
  }

  showAbout(image_file);

  // load sample.pcx into image
  SDL_Surface *image;
  SDL_RWops *rwop;
  rwop=SDL_RWFromFile(image_file.c_str(), "rb");
  image=IMG_LoadPCX_RW(rwop);
  if(!image) {
      printf("IMG_LoadPCX failure: %s\n", IMG_GetError());
      exit(-1);
  }

  // use width/height from pcx
  Window window(image->w, image->h, image_file, full_screen);
  window.setBackground(image);

  while (window.opened()) {
    window.handle_events();
    window.clear();    
    window.draw();

    SDL_Delay(50); // use this to slow down
  }

  return 0;
}
