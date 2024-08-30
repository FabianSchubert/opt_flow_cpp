#include <iostream>
#include <SDL2/SDL.h>
#include "gui.h"



void update_texture(SDL_Texture* tex, uint8_t* data, int n_data){
  int pitch = n_data * 4;
  uint8_t* pixels;

  SDL_LockTexture(tex, NULL, (void**)&pixels, &pitch);
  
  for(int i = 0; i < n_data * 4; i++){
    *(pixels + i) = *(data + i);
  }

  SDL_UnlockTexture(tex);
}

int init_sdl(SDL_Window* &window, SDL_Renderer* &renderer, int wind_width, int wind_height)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
      std::cout << "Error SDL2 Initialization : " << SDL_GetError();
      return 1;
  }

  window = SDL_CreateWindow("First program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wind_width, wind_height, SDL_WINDOW_OPENGL);
  if (window == NULL) {
      std::cout << "Error window creation";
      return 3;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 

  return 0;
}

SDL_Window create_window(int width, int height){
  return  SDL_CreateWindow("First program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wind_width, wind_height, SDL_WINDOW_OPENGL);
}

void draw(SDL_Renderer* renderer, SDL_Texture* texture){
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
 
  SDL_RenderCopy(renderer, texture, NULL, NULL);

  SDL_RenderPresent(renderer);
}

/*void main_loop(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture)
{
  while (true) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
          break;
      }
    }
    
    update_texture(texture);
    draw(renderer, texture);

  }

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

int main(int args, char* argv[]){
  
   

  SDL_Texture* texture = SDL_CreateTexture(
    renderer, 
    SDL_PIXELFORMAT_ARGB8888, 
    SDL_TEXTUREACCESS_STREAMING, 
    WIDTH, HEIGHT);
  
  

  

  return 0;
}*/
