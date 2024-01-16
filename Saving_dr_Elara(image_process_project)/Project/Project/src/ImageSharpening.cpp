#include <iostream>
#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    kernel_Height = 3;
    kernel_Width = 3;
    blurring_kernel = new double* [kernel_Height];

    for (int i = 0; i < kernel_Height; i++) {
        blurring_kernel[i] = new double[kernel_Width];
        for (int j = 0; j < kernel_Width; j++) {
            blurring_kernel[i][j] = 1.0 * 1/9;
        }
    }
}

ImageSharpening::~ImageSharpening(){
    if (blurring_kernel != nullptr) {
        for (int i = 0; i < kernel_Height; i++) {
            delete[] blurring_kernel[i];
        }
        delete[] blurring_kernel;
    }
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k=2.0) {
    kernel_Height = 3;
    kernel_Width = 3;
    blurring_kernel = new double* [kernel_Height];

    for (int i = 0; i < kernel_Height; i++) {
        blurring_kernel[i] = new double[kernel_Width];
        for (int j = 0; j < kernel_Width; j++) {
            blurring_kernel[i][j] = 1.0 * 1/9;
        }
    }
    Convolution convolution(blurring_kernel,kernel_Height,kernel_Width,1, true);
    ImageMatrix blurred_image = convolution.convolve(input_image);


    int height = input_image.get_height();
    int width = input_image.get_width();

    ImageMatrix sharpened_image(height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            double input_Img_pxl = input_image.get_data(i, j);
            double blurred_Img_pixel = blurred_image.get_data(i, j);
            double sharpened_pixel = input_Img_pxl + k * (input_Img_pxl - blurred_Img_pixel);
            sharpened_pixel = std::min(255.0, std::max(0.0, sharpened_pixel));
            sharpened_image.set_data(i, j, (sharpened_pixel));
        }
    }



    return sharpened_image;
}
