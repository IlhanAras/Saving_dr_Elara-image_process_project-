#include <iostream>
#include <cmath>

#include "Convolution.h"

// Default constructor 
Convolution::Convolution() {


}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernell, int kh, int kw, int stride_val, bool pad){

    kernelHeight=kh;
    this->customKernel = new double* [kernelHeight];
    kernelWidth=kw;
    stride=stride_val;
    padding=pad;


    for (int i = 0; i < kernelHeight; i++) {
        customKernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; j++) {
            this->customKernel[i][j] = customKernell[i][j];
        }
    }

}

// Destructor
Convolution::~Convolution() {
    if (customKernel != nullptr) {
        for (int i = 0; i < kernelHeight; i++) {
            delete[] customKernel[i];
        }
        delete[] customKernel;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other){

    kernelHeight = other.kernelHeight;
    customKernel = new double* [kernelHeight];
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    padding = other.padding;


    for (int i = 0; i < kernelHeight; i++) {
        customKernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; j++) {
            customKernel[i][j] = other.customKernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this;
    }

    if (customKernel != nullptr) {
        for (int i = 0; i < kernelHeight; i++) {
            delete[] customKernel[i];
        }
        delete[] customKernel;
    }

    kernelHeight = other.kernelHeight;
    this->customKernel = new double* [kernelHeight];
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    padding = other.padding;


    for (int i = 0; i < kernelHeight; i++) {
        customKernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; j++) {
            customKernel[i][j] = other.customKernel[i][j];
        }
    }
    return *this;



}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {

    int inputHeight = input_image.get_height();
    int inputWidth = input_image.get_width();
    int resultHeight, resultWidth;

    resultHeight = std::floor((inputHeight - kernelHeight + 2 * padding) / stride) + 1;
    resultWidth = std::floor((inputWidth - kernelWidth + 2 * padding) / stride) + 1;

    ImageMatrix paddedMatrix(inputHeight + 2*padding, inputWidth + 2*padding);
    for (int i = 0; i < inputHeight; i++) {
        for (int j = 0; j < inputWidth; j++) {
            paddedMatrix.set_data(i + 1*padding, j + 1*padding, input_image.get_data(i, j));
        }
    }


    ImageMatrix result_image(resultHeight, resultWidth);

    for (int i = 0; i < resultHeight; i++) {
        for (int j = 0; j < resultWidth; j++) {
            double sum = 0.0;
            for (int x = 0; x < kernelHeight; x++) {
                for (int y = 0; y < kernelWidth; y++) {

                    int inputRow = i * stride + x;
                    int inputCol = j * stride + y;

                    /*int inputRow = i * stride + x - padding;
                    int inputCol = j * stride + y - padding;*/

                    if (inputRow >= 0 && inputRow < paddedMatrix.get_height() && inputCol >= 0 && inputCol < paddedMatrix.get_width()) {
                        sum += paddedMatrix.get_data(inputRow , inputCol ) * customKernel[x][y];
                    }else {
                        // If the portion of the kernel goes out of image boundaries, move on to the next row
                        break;
                    }
                }
            }
            result_image.set_data(i, j, (sum));
        }
    }

    return result_image;

}
