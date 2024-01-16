#include "EncodeMessage.h"
#include <cmath>
#include <bitset>
#include <iostream>


// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

std::string EncodeMessage::rightCircularShift(const std::string &input) {
    if (input.empty()) {
        return input;
    }
    size_t shiftAmount = std::floor(input.length() / 2); // ⌊len(message)/2⌋
    std::string leftSide=input.substr(input.length() - shiftAmount);
    std::string rightSide=input.substr(0, input.length() - shiftAmount);

    std::string result = leftSide + rightSide;

    return result;
}

bool EncodeMessage::isPrime(int number) {
    if (number <= 1) {
        return false;
    }

    if (number == 2) {
        return true;
    }

    if (number % 2 == 0) {
        return false;
    }

    int sqrtNumber = sqrt(number);
    for (int i = 3; i <= sqrtNumber; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}
int EncodeMessage::fibonacci(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }

    int prev = 0;
    int current = 1;
    int result;

    for (int i = 2; i <= n; i++) {
        result = prev + current;
        prev = current;
        current = result;
    }

    return result;
}

std::string EncodeMessage::charTranformation(const std::string &message) {
    std::string resultMessage;
    for(int i=0; i<message.length(); i++){
        char newChar=message[i];

        if(isPrime(i)){

            int asciiValue = static_cast<int>(newChar);
            asciiValue= asciiValue + fibonacci(i);

            if(asciiValue<=32){
                asciiValue+=33;
            }
            else if(asciiValue>=127){
                asciiValue=126;
            }
            newChar= static_cast<char>(asciiValue);
        }
        resultMessage += std::string(1,newChar);

    }
    return resultMessage;
}
// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int> >& positions) {
    ImageMatrix encodedImage = img;
    std::string transformedMesg=charTranformation(message);

    transformedMesg= rightCircularShift(transformedMesg);

    std::string binaryMessage;

    for (char c : transformedMesg) {
        int asciiValue = static_cast<int>(c);

        // clip bounds
        if (asciiValue <= 32) {
            asciiValue += 33;
        } else if (asciiValue >= 127) {
            asciiValue = 126;
        }

        std::string binaryChar = std::bitset<7>(asciiValue).to_string();
        binaryMessage += binaryChar;
    }

    const int minLength = std::min(positions.size(), binaryMessage.length());
    for (int i = 0; i < minLength; i++) {
        int row = positions[i].first;
        int col = positions[i].second;
        int pixelValue = img.get_data(row, col);

        int newPixelValue = (pixelValue & 0xFFFFFFE) | ((binaryMessage[i] & 1) << 0);
        encodedImage.set_data(row, col, newPixelValue);
    }

    return encodedImage;
}
