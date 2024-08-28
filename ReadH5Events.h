#ifndef READH5EVENTS_H
#define READH5EVENTS_H

#include <H5Cpp.h>
#include <string>
#include <vector>

class ReadH5Events {
  public:
    ReadH5Events(std::string file_name); 

    ~ReadH5Events();

    int height();
    int width();

    uint32_t t(int i);
    uint16_t x(int i);
    uint16_t y(int i);
    uint8_t p(int i);
    float u(int i);
    float v(int i);
     
  private:
    std::string FILE_NAME;
    // init vector with strings of dataset names (t, x, y, p)
    static const std::vector<std::string> DATASET_NAMES;
    H5::H5File file;
    H5::DataSet* dataset;
    H5::DataSpace* dataspace;
    hsize_t dims_out[1];
    uint32_t* _t;
    uint16_t* _x;
    uint16_t* _y;
    uint8_t* _p;
    float* _u;
    float* _v;
    uint32_t _width_height[2];
};


#endif // !READH5EVENTS_H
