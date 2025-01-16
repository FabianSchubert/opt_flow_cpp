#ifndef STREAM_EVENTS_H
#define STREAM_EVENTS_H

#include "read_h5_events.h"
#include <string>

class StreamEvents {
  public:
    StreamEvents(const std::string &file_name, float _dt);
    ~StreamEvents();

    // get the next bin of events
    void get(uint32_t* &_t, uint16_t* &_x, uint16_t* &_y, uint8_t* &_p,
        float* &_u, float* &_v, int &num_events_in_bin, int &bin_id, int &start_id);

    int num_events;
    float dt;
    float t_max;
    int n_bins;

  private:
    ReadH5Events events;
    int current_bin;
    int current_event;
    int* bin_id_end;
};

#endif
