
// FOR MFC
#include "stdafx.h"

// COCR CLASS
#include "Cocr.h"

// constructor
Cocr::Cocr():image_height(H), image_width(W), character_type(CHAR), character_ratio(RATIO_THR)
{
    image_gray = Mat(image_height, image_width,CV_8UC1,Scalar::all(0));
    image_binary = Mat(image_height, image_width,CV_8UC1,Scalar::all(0));
    recognition_result = -1;
}
Cocr::Cocr(const Mat& image_gray, const Mat& image_binary, const int char_type /* = CHAR */, const double char_ratio /* = RATIO_THR */)
{
    image_gray.copyTo(this->image_gray);
    image_binary.copyTo(this->image_binary);
    this->character_type = char_type;
    this->character_ratio = char_ratio;
}
// destructor
Cocr::~Cocr() {}
// set value
void Cocr::setImageGray(const Mat& image_gray)
{
    if (image_gray.channels() != 1) {
        cvtColor(image_gray, image_gray, CV_BGR2GRAY);
    }
    if (image_gray.rows != image_height || image_gray.cols != image_width) {
        resize(image_gray, image_gray, Size(image_width, image_height));
    }
    image_gray.copyTo(this->image_gray);
}
void Cocr::setImageBinary(const Mat& image_binary)
{
    if (image_binary.channels() != 1) {
        cvtColor(image_binary, image_binary, CV_BGR2GRAY);
    }
    if (image_binary.rows != image_height || image_binary.cols != image_width) {
        resize(image_binary, image_binary, Size(image_width, image_height));
        threshold(image_binary, image_binary, 128, 255, THRESH_BINARY);
    }
    image_binary.copyTo(this->image_binary);
}
void Cocr::setCharacterType(int char_type /* = CHAR */)
{
    this->character_type = char_type;
}
void Cocr::setCharacterRatio(double char_ratio /* = 1.0 */)
{
    this->character_ratio = char_ratio;
}
// get value
Mat& Cocr::getImageGray(Mat& image_gray) const
{
    this->image_binary.copyTo(image_gray);
    return image_gray;
}
Mat& Cocr::getImageBinary(Mat& image_binary) const
{
    this->image_binary.copyTo(image_binary);
    return image_binary;
}
int Cocr::getCharacterType() const
{
    return this->character_type;
}
double Cocr::getCharacterRatio() const
{
    return this->character_ratio;
}
void Cocr::recognitionResultTrans2Char()
{
    switch (character_type)
    {
    case CHAR:
        if (recognition_result >= 0 && recognition_result < 10) {
            recognition_result = '0' + recognition_result;
        } else {
            recognition_result = 'A' + recognition_result - 10;
        }
        break;
    case LETTER:
        recognition_result = 'A' + recognition_result - 10;
        break;
    case NUMBER:
        recognition_result = '0' + recognition_result;
        break;
    default:
        break;
    }
}
char Cocr::getRecognitionResult()
{
    recognitionProcess();
    recognitionResultTrans2Char();
    return recognition_result;
}

void Cocr::recognitionProcess()
{
    // Mat to point
    unsigned char* img_b = new unsigned char[image_height * image_width];
    unsigned char* img_g = new unsigned char[image_height * image_width];
    for (int i = 0; i < image_height; i++) {
        uchar* p_mat_b = image_binary.ptr<uchar>(i);
        uchar* p_mat_g = image_gray.ptr<uchar>(i);
        for (int j = 0; j < image_width; j++) {
            *(img_b + i * image_width + j) = *(p_mat_b + j);
            *(img_g + i * image_width + j) = *(p_mat_g + j);
        }
    }
    if (character_ratio > RATIO_THR) {
        switch (character_type) {
        case CHAR:
            recognition_result = judge1I(img_g);
            break;
        case NUMBER:
            recognition_result = 1;
            break;
        case LETTER:
            recognition_result = 18;
            break;
        default:
            recognition_result = -1;
            break;
        }
    } else {
        switch (character_type) {
        case CHAR:
            recognition_result = judgeChar(img_b, img_g, THR_OFFSET_FROM_LEAST);
            break;
        case NUMBER:
            recognition_result = judgeNum(img_b, img_g, THR_OFFSET_FROM_LEAST);
            break;
        case LETTER:
            recognition_result = judgeLetter(img_b, img_g, THR_OFFSET_FROM_LEAST);
            break;
        default:
            recognition_result = -1;
            break;
        }
    }
    // free memory
    delete img_b;
    img_b = NULL;
    delete img_g;
    img_g = NULL;
#ifdef _DEBUG
    TRACE("result = %d\n", recognition_result);
#endif
}