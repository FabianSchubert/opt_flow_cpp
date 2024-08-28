#include <iostream>
#include "ReadH5Events.h"

int main() {

    ReadH5Events events("../repos/event_based_optical_flow/data/checkerboard_sequence.h5");
    
    std::cout << "Width: " << events.width() << std::endl;
    std::cout << "Height: " << events.height() << std::endl;

    std::cout << "t: " << events.t(13000) << std::endl;
    std::cout << "x: " << events.x(13000) << std::endl;
    std::cout << "y: " << events.y(13000) << std::endl;
    std::cout << "p: " << int(events.p(13000)) << std::endl;
    std::cout << "u: " << events.u(13000) << std::endl;
    std::cout << "v: " << events.v(13000) << std::endl;

    //std::cout << read_h5.get_data(1000) << std::endl;

    // HDF5 file and dataset names
    /*
    const std::string FILE_NAME("../repos/event_based_optical_flow/data/checkerboard_sequence.h5");
    const std::string DATASET_NAME("t");

    try {
        // Open the HDF5 file
        H5::H5File file(FILE_NAME, H5F_ACC_RDONLY);

        // Open the dataset
        H5::DataSet dataset = file.openDataSet(DATASET_NAME);

        // Get the dataspace of the dataset
        H5::DataSpace dataspace = dataset.getSpace();

        // Get the number of elements (assumes 1D array)
        hsize_t dims_out[1];
        dataspace.getSimpleExtentDims(dims_out, NULL);
        size_t num_elements = dims_out[0];

        // Allocate memory for the data
        float* data = new float[num_elements];

        // Read the data from the file into the array
        dataset.read(data, H5::PredType::NATIVE_FLOAT);

        // Print out the data
        std::cout << "Data in the HDF5 file:" << std::endl;
        for (size_t i = 0; i < num_elements; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;

        // Clean up memory
        delete[] data;

    } catch (H5::FileIException &error) {
        error.printErrorStack();
        return -1;
    } catch (H5::DataSetIException &error) {
        error.printErrorStack();
        return -1;
    } catch (H5::DataSpaceIException &error) {
        error.printErrorStack();
        return -1;
    }*/

    return 0;
}
