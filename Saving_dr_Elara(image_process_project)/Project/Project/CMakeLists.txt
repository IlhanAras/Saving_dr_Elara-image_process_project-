cmake_minimum_required(VERSION 3.26)
project(PA1_template)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(PA1_template
        src/Convolution.cpp
        src/Convolution.h
        src/DecodeMessage.cpp
        src/DecodeMessage.h
        src/EdgeDetector.cpp
        src/EdgeDetector.h
        src/EncodeMessage.cpp
        src/EncodeMessage.h
        src/ImageLoader.cpp
        src/ImageLoader.h
        src/ImageMatrix.cpp
        src/ImageMatrix.h
        src/ImageProcessor.cpp
        src/ImageProcessor.h
        src/ImageSharpening.cpp
        src/ImageSharpening.h
        src/main.cpp)
