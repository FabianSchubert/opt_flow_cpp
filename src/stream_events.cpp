#include "stream_events.h"
#include <iostream>

StreamEvents::StreamEvents(std::string file_name, float _dt): events(file_name)
{
  num_events = events.num_events;

  dt = _dt;
  t_max = 0.0;
  n_bins = 0;

  current_bin = 0;
  current_event = 0;

  // Calculate t_max, and n_bins
  std::cout << "Calculating t_max" << std::endl;
  for (int i = 0; i < num_events; i++) {
    if (events.t(i) > t_max) {
      t_max = events.t(i);
    }
  }
  std::cout << "t_max: " << t_max << std::endl;

  n_bins = int(t_max / dt) + 1;
  
  // bin edges refers to indices of events, not their times.
  // but events should be placed in the bins based on equally spaced times.
  bin_id_end = new int[n_bins];
  for (int i = 0; i < n_bins; i++) {
    bin_id_end[i] = 0;
  }

  for(int i=0; i<num_events;i++){
    int bin_id = int(events.t(i)/dt);
    bin_id_end[bin_id] = i + 1;
  }
  // if bin_id_end[i] = 0, replace it with bin_id_end[i-1]
  for(int i=1; i<n_bins;i++){
    if(bin_id_end[i] == 0){
      bin_id_end[i] = bin_id_end[i-1];
    }
  }
};

StreamEvents::~StreamEvents()
{
  delete bin_id_end;
};


void StreamEvents::get(uint32_t* &_t, uint16_t* &_x, uint16_t* &_y, uint8_t* &_p,
        float* &_u, float* &_v, int &num_events_in_bin){
  if(current_bin >= n_bins){
    num_events_in_bin = 0;
    _t = nullptr;
    _x = nullptr;
    _y = nullptr;
    _p = nullptr;
    _u = nullptr;
    _v = nullptr;
  } else {
    int start_id = current_event;
    int end_id = bin_id_end[current_bin];

    num_events_in_bin = end_id - start_id;

    _t = events._t + start_id;
    _x = events._x + start_id;
    _y = events._y + start_id;
    _p = events._p + start_id;
    _u = events._u + start_id;
    _v = events._v + start_id;

    current_event = end_id;
    current_bin++;
  }
};

