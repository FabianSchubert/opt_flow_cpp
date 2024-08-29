#include "read_h5_events.h"
#include <H5Cpp.h>
#include <string>
#include <vector>
#include <iostream>

ReadH5Events::ReadH5Events(std::string file_name):
  FILE_NAME(file_name), 
  file(file_name, H5F_ACC_RDONLY)
{
  int _num_events = 0;
  bool _num_events_set = false;

  for (auto dataset_name : DATASET_NAMES) {
    dataset = new H5::DataSet(file.openDataSet(dataset_name));
    dataspace = new H5::DataSpace(dataset->getSpace());
    dataspace->getSimpleExtentDims(dims_out, NULL);
    size_t num_elements = dims_out[0];
    if (dataset_name == "t") {
      _t = new uint32_t[num_elements];
      dataset->read(_t, H5::PredType::NATIVE_UINT32);
    } else if (dataset_name == "x") {
      _x = new uint16_t[num_elements];
      dataset->read(_x, H5::PredType::NATIVE_UINT16);
    } else if (dataset_name == "y") {
      _y = new uint16_t[num_elements];
      dataset->read(_y, H5::PredType::NATIVE_UINT16);
    } else if (dataset_name == "p") {
      _p = new uint8_t[num_elements];
      dataset->read(_p, H5::PredType::NATIVE_UINT8);
    } else if (dataset_name == "u") {
      _u = new float[num_elements];
      dataset->read(_u, H5::PredType::NATIVE_FLOAT);
    } else if (dataset_name == "v") {
      _v = new float[num_elements];
      dataset->read(_v, H5::PredType::NATIVE_FLOAT);
    } else if (dataset_name == "width_height") {
      if(num_elements != 2) {
        std::cout << "Width and height dataset must have 2 elements" << std::endl;
      }
      dataset->read(_width_height, H5::PredType::NATIVE_UINT32);
    } else {
      std::cout << "Unknown dataset name: " << dataset_name << std::endl;
    }

    if (!_num_events_set && dataset_name != "width_height") {
      _num_events = num_elements;
      _num_events_set = true;
    } else if (_num_events != num_elements && dataset_name != "width_height") {
      std::cout << "Number of elements in dataset " << dataset_name << " does not match number of elements in other datasets" << std::endl;
    }

    num_events = _num_events;

    // Clean up memory
    delete dataset;
    delete dataspace;
  }
};

ReadH5Events::~ReadH5Events() {
  delete _t;
  delete _x;
  delete _y;
  delete _p;
  delete _u;
  delete _v;
};

int ReadH5Events::height() {
  return _width_height[1];
};

int ReadH5Events::width() {
  return _width_height[0];
};

uint32_t ReadH5Events::t(int i) {
  return _t[i];
};

uint16_t ReadH5Events::x(int i) {
  return _x[i];
};

uint16_t ReadH5Events::y(int i) {
  return _y[i];
};

uint8_t ReadH5Events::p(int i) {
  return _p[i];
};

float ReadH5Events::u(int i) {
  return _u[i];
};

float ReadH5Events::v(int i) {
  return _v[i];
};

const std::vector<std::string> ReadH5Events::DATASET_NAMES = {"t", "x", "y", "p", "u", "v", "width_height"};

