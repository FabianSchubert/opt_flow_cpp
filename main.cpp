#include <iostream>
#include <SDL2/SDL.h>
#include "read_h5_events.h"
#include "stream_events.h"
#include "gui.h"

const int WIDTH = 320;
const int HEIGHT = 240;
const int N_PIX = WIDTH * HEIGHT;

const int WIND_WIDTH = 2 * WIDTH;
const int WIND_HEIGHT = 2 * HEIGHT;

// add command line arguments
int main(int argc, char** argv) {
    
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    } else {
        std::cout << "Reading file: " << argv[1] << std::endl;
    }
    
    std::string file_name = argv[1];

    ReadH5Events events(file_name);
    StreamEvents stream_events(file_name, 1000.0);

    uint32_t* t;
    uint16_t* x;
    uint16_t* y;
    uint8_t* p;
    float* u;
    float* v;
    int num_events_in_bin;

    while(true) {
      stream_events.get(t, x, y, p, u, v, num_events_in_bin);
      std::cout << "Number of events in bin: " << num_events_in_bin << std::endl;
      // check if t points to nullptr
      if(t == nullptr) {
        break;
      }
    }
    
    SDL_Window* window;
    SDL_Renderer* renderer;

    init_sdl(window, renderer, WIND_WIDTH, WIND_HEIGHT);

    SDL_Texture* texture = SDL_CreateTexture(
    renderer, 
    SDL_PIXELFORMAT_ARGB8888, 
    SDL_TEXTUREACCESS_STREAMING, 
    WIDTH, HEIGHT);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    
    return 0;
}
