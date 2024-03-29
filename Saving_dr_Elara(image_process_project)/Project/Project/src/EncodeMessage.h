#ifndef ENCODE_MESSAGE_H
#define ENCODE_MESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

class EncodeMessage {
public:
    EncodeMessage();
    ~EncodeMessage();

    ImageMatrix encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int> >& positions);


private:
    std::string rightCircularShift(const std::string& input);
    bool isPrime(int number);
    int fibonacci(int n);
    std::string charTranformation(const std::string &message);
};

#endif // ENCODE_MESSAGE_H
