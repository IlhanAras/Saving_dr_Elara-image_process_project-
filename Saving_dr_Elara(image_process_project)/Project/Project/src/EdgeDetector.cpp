// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

#include <iostream>
// Default constructor
EdgeDetector::EdgeDetector() {

    Gy = new double* [3];
    for (int i = 0; i < 3; i++) {
        Gy[i] = new double[3];
    }

    Gy[0][0] = -1.0;
    Gy[0][1] = -2.0;
    Gy[0][2] = -1.0;
    Gy[1][0] = 0.0;
    Gy[1][1] = 0.0;
    Gy[1][2] = 0.0;
    Gy[2][0] = 1.0;
    Gy[2][1] = 2.0;
    Gy[2][2] = 1.0;

    Gx = new double* [3];
    for (int i = 0; i < 3; i++) {
        Gx[i] = new double[3];
    }

    Gx[0][0] = -1.0;
    Gx[0][1] = 0.0;
    Gx[0][2] = 1.0;
    Gx[1][0] = -2.0;
    Gx[1][1] = 0.0;
    Gx[1][2] = 2.0;
    Gx[2][0] = -1.0;
    Gx[2][1] = 0.0;
    Gx[2][2] = 1.0;
}

// Destructor
EdgeDetector::~EdgeDetector() {
    for(int i=0;i<3;i++){
        delete[] Gx[i];
        delete[] Gy[i];
    }
    delete[] Gx;
    delete[] Gy;
}


// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {






    Convolution convX(Gx,3,3,1,true);
    ImageMatrix Ix= convX.convolve(input_image);


    Convolution convY(Gy,3,3,1,true);
    ImageMatrix Iy= convY.convolve(input_image);




    ImageMatrix magnitude(input_image.get_height(),input_image.get_width());

    for(int i=0; i<input_image.get_height(); i++){
        for(int j=0; j<input_image.get_width(); j++){
            double result= sqrt(pow(Ix.get_data(i,j),2) + pow(Iy.get_data(i,j),2));
            magnitude.set_data(i,j,result);
        }
    }
    double sum=0.0;
    for(int i=0; i<magnitude.get_height(); i++){
        for(int j=0; j<magnitude.get_width(); j++){
            sum+=magnitude.get_data(i,j);
        }
    }






    double threshold = sum / (magnitude.get_width() * magnitude.get_height());

    std::vector<std::pair<int, int>> EdgePixels;


    for(int row=0; row<input_image.get_height(); row++){
        for(int col=0; col<input_image.get_width(); col++){
            if(magnitude.get_data(row,col)>threshold){
                EdgePixels.push_back(std::make_pair(row, col));
            }
        }
    }

    return EdgePixels;

}

