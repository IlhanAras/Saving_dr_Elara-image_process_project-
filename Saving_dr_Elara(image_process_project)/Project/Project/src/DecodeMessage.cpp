// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>

// Default constructor
DecodeMessage::DecodeMessage() {

}

// Destructor
DecodeMessage::~DecodeMessage() {

}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int> >& edgePixels) {

    std::string decodedMessage;
    std::string stringBinary;

    for (const auto& pxl : edgePixels) {
        int pxlValue = static_cast<int>(image.get_data(pxl.first, pxl.second));

        // Extract the least significant bit (LSB) from the pixel's value
        int LSB = pxlValue & 1;

        // Append the LSB to the binary string
        stringBinary += std::to_string(LSB);
    }

    while (stringBinary.length() % 7 != 0) {
        stringBinary = "0" + stringBinary;
    }

    for (size_t i = 0; i < stringBinary.length(); i += 7) {
        std::string sevenBits = stringBinary.substr(i, 7);
        int decimalValue = 0;
        for (char bit : sevenBits) {
            decimalValue = decimalValue * 2 + (bit - '0');
        }

        // ASCII değerini düzeltilmiş sınırlar içinde tut
        if (decimalValue <= 32) {
            decimalValue += 33;
        } else if (decimalValue >= 127) {
            decimalValue = 126;
        }

        char asciiChar = static_cast<char>(decimalValue);
        decodedMessage += asciiChar;
    }

    return decodedMessage;

}

