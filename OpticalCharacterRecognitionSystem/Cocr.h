//////////////////////////////////////////////////////////////////////////
// CLASS FOR OPTICAL CHARACTER RECOGNITION
// WITH GRAY AND BINARY IMAGE AND CHARACTER TYPE FOR INPUT
// IMAGE SIZE: HEIGHT = 36 , WIDTH = 20, IMAGE CHANNELS = 3
// CHARACTER TYPE: NUMBER, LETTER, CHAR(NUMBER OR LETTER)
// WITH OPENCV LIBRARY
//////////////////////////////////////////////////////////////////////////

#ifndef _COCR_H_
#define _COCR_H_

// OpenCV Library
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

// Basic Library
#include <stdlib.h>

// ORC macro

class Cocr {
public:
    // type enum
    enum {CHAR = 1, LETTER = 2, NUMBER = 3};
    // const
    static const int INF = 32767;
    static const int H = 36;
    static const int W = 20;
    static const int NUM = H * W;
    static const int M_NUM = 10;
    static const int M_LETTER = 26;
    static const int M_CHAR = 36;
    static const int RATIO_THR = 3;
    static const int THR_OFFSET_FROM_LEAST = 5100;
    Cocr();
    Cocr(const Mat& image_gray, const Mat& image_binary, const int char_type = CHAR, const double char_ratio = RATIO_THR);
    ~Cocr();
    void setImageGray(const Mat& image_gray);
    void setImageBinary(const Mat& image_binary);
    void setCharacterType(int char_type = CHAR);
    void setCharacterRatio(double char_ratio = 1.0);
    Mat& getImageGray(Mat& image_gray) const;
    Mat& getImageBinary(Mat& image_binary) const;
    int getCharacterType() const;
    double getCharacterRatio() const;
    char getRecognitionResult();
private:
    int image_height;
    int image_width;
    Mat image_gray;
    Mat image_binary;
    int character_type;
    double character_ratio;
    char recognition_result;
    void recognitionProcess();
    void recognitionResultTrans2Char();
    // find.cpp
    short find(const short* array_input, short* array_output, const short array_length, const short value_min, const short value_max);
    // connect_domain_identification.cpp
    short ConnectedDomainIdentification(const unsigned char* image_binary, const short mode);
    // Judge1I.cpp
    short judge1I(const unsigned char* img_g);
    // judgeNum.cpp
    short judgeNum(const unsigned char* img_b, const unsigned char* img_g, const short thr);
    // judgeLetter.cpp
    short judgeLetter(const unsigned char* img_b, const unsigned char* img_g, const short thr);
    // JudgeChar.cpp
    short judgeChar(const unsigned char* img_b, const unsigned char* img_g, const short thr);
    // JudgeLocalFeatures_base.cpp
    short SumImageRegion(const unsigned char* image_input, const short image_input_height, const short image_input_width, const short position_row_top, const short position_row_buttom, const short position_col_left, const short position_col_right);
    short SumImageMinLine(const unsigned char* image_input, const short image_input_height, const short image_input_width, const short mode, const short position_row_top, const short position_row_buttom, const short position_col_left,const short position_col_right);
    // JudgeLocalFeatures_num.cpp
    short judge17(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge23(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge35(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge06(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge08(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge09(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge68(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge69(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge89(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge068(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judge069(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judge089(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judge689(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    // JudgeLocalFeatures_letter.cpp
    short judgeBQ(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeCG(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeCS(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeGS(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeCGS(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judgeCL(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeCU(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeLU(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeCLU(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judgeDO(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeDQ(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeOQ(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeDOQ(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judgeEF(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeEFS(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judgeEL(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeHK(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeKX(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeHU(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeHM(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeHN(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeMN(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeHMN(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judgeMR(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeMW(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeHMW(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judgeNW(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeNR(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeRW(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgePR(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeTJ(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeTY(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeJZ(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judgeTJZ(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    //JudgeLocalFeatures_char.cpp
    short judge2Z(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge4A(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge3S(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge5S(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge35S(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judge7J(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge7T(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge7Z(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge7Y(const unsigned char *img_bw, const short height, const short width, const short thr);
    short judge7JT(const unsigned char *img_bw, const short height, const short width, const short thr_1, const short thr_2);
    short judge8B(const unsigned char *img_bw, const short height, const short width, const short thr);
};

#endif // _COCR_H_
