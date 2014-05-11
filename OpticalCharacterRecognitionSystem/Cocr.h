//////////////////////////////////////////////////////////////////////////
// CLASS FOR OPTICAL CHARACTER RECOGNITION
// WITH GRAY AND BINARY IMAGE AND CHARACTER TYPE FOR INPUT
// IMAGE SIZE: HEIGHT = 36 , WIDTH = 20, IMAGE CHANNELS = 3
// CHARACTER TYPE: NUMBER, LETTER, CHAR(NUMBER OR LETTER)
// WITH OPENCV LIBRARY
//////////////////////////////////////////////////////////////////////////

#ifndef _COCR_H_
#define _COCR_H_

// MFC Library
#include "stdafx.h"

// OpenCV Library
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

// Basic Library
#include <stdlib.h>

class Cocr {
public:
 // type enum for character type:CHAR(A-Z&0-9), LETTER(A-Z), NUMBER(0-9)
 enum {CHAR = 1, LETTER = 2, NUMBER = 3};
 // constructor
 Cocr();
 Cocr(const Mat& image_gray, const Mat& image_binary, const int char_type = CHAR, const double char_ratio = RATIO_THR);
 // destructor
 ~Cocr();
 // set gray image
 void setImageGray(const Mat& image_gray);
 // set binary image
 void setImageBinary(const Mat& image_binary);
 // set character type
 void setCharacterType(int char_type = CHAR);
 // set character ratio
 void setCharacterRatio(double char_ratio = 1.0);
 // get gray image
 Mat& getImageGray(Mat& image_gray) const;
 // get binary image
 Mat& getImageBinary(Mat& image_binary) const;
 // get character type
 int getCharacterType() const;
 // get character ratio
 double getCharacterRatio() const;
 // get recognition result wrong process will get char value -1
 char getRecognitionResult();
private:
 // image height
 int image_height;
 // image width
 int image_width;
 // gray image
 Mat image_gray;
 // binary image
 Mat image_binary;
 // character type
 int character_type;
 // character ratio
 double character_ratio;
 // character result
 char recognition_result;
 // recognition process
 void recognitionProcess();
 // result type short translate to type char
 void recognitionResultTrans2Char();
 // main recognition function and value
 // const for recognition process
 static const int INF = 32767;                   // max short value
 static const int H = 36;                        // image height
 static const int W = 20;                        // image width
 static const int NUM = H * W;                   // image size(height * width)
 static const int M_NUM = 10;                    // number type num(0-9)
 static const int M_LETTER = 26;                 // letter type num(A-Z)
 static const int M_CHAR = 36;                   // char type num(A-Z&0-9)
 static const int THR_OFFSET_FROM_LEAST = 5100;  // threshold for template match
 // ratio(source character image ratio(height / width) threshold for 1 and I recognition)
 static const int RATIO_THR = 3;
 // template for template matching recognition
 // Model1I.h
 static const short model1I[2][NUM];
 // ModelChar.h
 static const short model8BQ[M_CHAR][NUM];
 static const short model469ADOPQR[M_CHAR][NUM];
 static const short model123457CEFGHJKLMNSTUWXYZ[M_CHAR][NUM];
 // ModelLetter.h
 static const short modelBQR_L[M_LETTER][NUM];
 static const short modelADMNOPQRW_L[M_LETTER][NUM];
 static const short modelACEFGHJKLMNRSTUWXYZ_L[M_LETTER][NUM];
 // ModelNum.h
 static const short model89_L[M_NUM][NUM];
 static const short model04689_L[M_NUM][NUM];
 static const short model123457_L[M_NUM][NUM];
 // find value from array input
 short find(const short* array_input, short* array_output, const short array_length, const short value_min, const short value_max);
 // calculate image connected domain identification
 short ConnectedDomainIdentification(const unsigned char* image_binary, const short mode);
 // judge for 1 and I
 short judge1I(const unsigned char* img_g);
 // judge for number 0-9
 short judgeNum(const unsigned char* img_b, const unsigned char* img_g, const short thr);
 // judge for letter A-Z
 short judgeLetter(const unsigned char* img_b, const unsigned char* img_g, const short thr);
 // judge for char A-Z&0-9
 short judgeChar(const unsigned char* img_b, const unsigned char* img_g, const short thr);
 // JudgeLocalFeatures_base.cpp base function for judge
 short SumImageRegion(const unsigned char* image_input, const short image_input_height, const short image_input_width, const short position_row_top, const short position_row_buttom, const short position_col_left, const short position_col_right);
 short SumImageMinLine(const unsigned char* image_input, const short image_input_height, const short image_input_width, const short mode, const short position_row_top, const short position_row_buttom, const short position_col_left,const short position_col_right);
 // JudgeLocalFeatures_num.cpp function for judge number
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
 // JudgeLocalFeatures_letter.cpp function for judge letter
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
 //JudgeLocalFeatures_char.cpp function for judge char
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
