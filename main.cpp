#include <iostream>
#include <SDL2/SDL.h>
#include "read_h5_events.h"
#include "stream_events.h"
#include "gui.h"
#include "data_utils.h"
#include "opt_flow.h"

int main(int argc, char **argv)
{

  if (argc != 3)
  {
    std::cout << "Usage: " << argv[0] << " <file_name> <DT in ms>" << std::endl;
    return 1;
  }
  else
  {
    std::cout << "Reading file: " << argv[1] << std::endl;
  }

  std::string file_name = argv[1];
  const float DT = std::stof(argv[2]);

  ReadH5Events events(file_name);
  StreamEvents stream_events(file_name, DT);

  const int WIDTH = events.width();
  const int HEIGHT = events.height();

  const int N_PIX = WIDTH * HEIGHT;

  const int WIND_WIDTH = 2 * WIDTH;
  const int WIND_HEIGHT = 2 * HEIGHT;

  uint32_t *t;
  uint16_t *x;
  uint16_t *y;
  uint8_t *p;
  float *u;
  float *v;
  int num_events_in_bin;
  int bin_id;
  int evt_start_id_current_bin;

  float *u_est = new float[events.num_events];
  float *v_est = new float[events.num_events];

  OptFlow opt_flow(WIDTH, HEIGHT);

  uint8_t tex_data[N_PIX * 4];

  // use template function set_array to set tex_data to 0
  set_array<uint8_t>(tex_data, N_PIX * 4, (uint8_t)(0));

  int init = init_sdl();

  SDL_Window *window;
  SDL_Renderer *renderer;

  window = SDL_CreateWindow("First program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIND_WIDTH, WIND_HEIGHT, SDL_WINDOW_OPENGL);
  if (window == NULL)
  {
    std::cout << "Error window creation";
    return 3;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture *texture = SDL_CreateTexture(
      renderer,
      SDL_PIXELFORMAT_ABGR32,
      SDL_TEXTUREACCESS_STREAMING,
      WIDTH, HEIGHT);

  SDL_Event e;

  bool running = true;

  while (running)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      // User requests quit
      if (e.type == SDL_QUIT)
      {
        running = false;
      }
    }

    stream_events.get(t, x, y, p, u, v, num_events_in_bin, bin_id, evt_start_id_current_bin);
    if (t == nullptr)
    {
      std::cout << "event stream finished" << std::endl;
      running = false;
    }
    else
    {
      opt_flow.update_flow(t, x, y, p, u_est + evt_start_id_current_bin, v_est + evt_start_id_current_bin, num_events_in_bin);
    }

    set_array<uint8_t>(tex_data, N_PIX * 4, (uint8_t)(0));
    update_event_pixels(x, y, p, tex_data, num_events_in_bin, N_PIX, WIDTH, HEIGHT);

    update_texture(texture, tex_data, N_PIX);

    draw(renderer, texture);
  }

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
}
