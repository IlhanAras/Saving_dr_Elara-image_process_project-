#include <iostream>
#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageMatrix matrixImg(img);

    ImageSharpening imgshar;
    matrixImg= imgshar.sharpen(matrixImg,2);

    EdgeDetector edgedt;

    edges= edgedt.detectEdges(matrixImg);

    DecodeMessage dec;
    std::string resultStr= dec.decodeFromImage(matrixImg,edges);

    return resultStr;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {

    ImageSharpening sharpenImgOOP;
    ImageMatrix sharpImg = sharpenImgOOP.sharpen(img, 2);

    EdgeDetector edgeDetectOOP;
    std::vector<std::pair<int, int> > edges = edgeDetectOOP.detectEdges(sharpImg);

    EncodeMessage messageEncoder;
    ImageMatrix encodedImage = messageEncoder.encodeMessageToImage(img, message, edges);

    return encodedImage;

}
