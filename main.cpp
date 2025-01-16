#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <chrono>
#include "read_h5_events.h"
#include "stream_events.h"
#include "gui.h"
#include "data_utils.h"
#include "opt_flow.h"
#include "json.hpp"

int main(int argc, char **argv)
{

  if (argc != 4)
  {
    std::cout << "Usage: " << argv[0] << " <file_name> <opt_flow_config_file_name> <DT in ms>" << std::endl;
    return 1;
  }
  else
  {
    std::cout << "Reading file: " << argv[1] << std::endl;
  }

  std::string file_name = argv[1];
  std::string opt_flow_config_file_name = argv[2];
  const float DT = std::stof(argv[3]) * 1000.0f;

  ReadH5Events events(file_name);
  StreamEvents stream_events(file_name, DT);

  const int WIDTH = events.width();
  const int HEIGHT = events.height();

  std::cout << "Width: " << WIDTH << " Height: " << HEIGHT << std::endl;

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

  auto u_est = new float[events.num_events];
  auto v_est = new float[events.num_events];

  // load json config for optical flow
  std::ifstream conf_file(opt_flow_config_file_name);
  nlohmann::json json_conf = nlohmann::json::parse(conf_file);
  conf_file.close();

  const auto KERN_HALF = static_cast<int>(json_conf["kern_half"]);
  const auto KERN_HALF_HS = static_cast<int>(json_conf["kern_half_hs"]);
  const auto TAU = static_cast<float>(json_conf["tau"]);
  const auto G_REG = static_cast<float>(json_conf["g_reg"]);
  const auto SCALE = static_cast<float>(json_conf["scale_viz"]);
  const auto ALPHA_HS = static_cast<float>(json_conf["alpha_hs"]);

  OptFlow opt_flow(WIDTH, HEIGHT, TAU, G_REG, ALPHA_HS, KERN_HALF, KERN_HALF_HS);

  uint8_t tex_data[N_PIX * 4];

  // use template function set_array to set tex_data to 0
  set_array<uint8_t>(tex_data, N_PIX * 4, (uint8_t)(0));

  int init = init_sdl();

  SDL_Window *window;
  SDL_Renderer *renderer;

  window = SDL_CreateWindow("Optical Flow Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIND_WIDTH, WIND_HEIGHT, SDL_WINDOW_OPENGL);
  if (window == nullptr)
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

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

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

    update_flow_pixels(x, y, u_est + evt_start_id_current_bin, v_est + evt_start_id_current_bin, tex_data,
                       num_events_in_bin, N_PIX, WIDTH, HEIGHT, SCALE);

    // update_flow_pixels(x, y, u, v, tex_data,
    //                     num_events_in_bin, N_PIX, WIDTH, HEIGHT, 1.0f);

    // update_event_pixels(x, y, p, tex_data, num_events_in_bin, N_PIX, WIDTH, HEIGHT);

    update_texture(texture, tex_data, N_PIX);

    draw(renderer, texture);
  }

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  std::cout << "Elapsed time in microseconds: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
  std::cout << "Processed " << events.num_events / (
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1e6) << " events per second"
      <<
      std::endl;
  std::cout << "Required by Dataset: " << events.num_events / (stream_events.t_max / 1e6) << " events per second" << std::endl;
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
}
