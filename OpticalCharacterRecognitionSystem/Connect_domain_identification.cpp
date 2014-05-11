/*************************************************************************
  Copyright (C),1988-1999, Cita109 Tech. Co., Ltd.  
  FileName:Connect_domain_identification.cpp
  Author: ChenXiLin       Version: 1.1         Date: 20131001
  Description:     ��ͨ��ʶ���Ӻ���  
*************************************************************************/
/**************************** INCLUDE FILES *****************************/
#include "Cocr.h"
/**************************** INCLUDE FILES *****************************/
/*************************************************************************
 Function:       ConnectedDomainIdentification  
 Description:    1.���� floodfill �ı�Ǻ���_�Թ�һ�����ַ���ǣ�
                 ���������ַ��ߴ�;
 Calls:          none
 CalledBy:       RotateChar;JudgeChar.c;JudgeLetter.c;JudgeNum.c
 TableAccessed:  none
 TableUpdated:   none
 Input:          image_binary:    const unsigned char*   ����Ķ�ֵͼ��
                 image_height:    const short            image height
                 image_width:     const short            image width
                 mode:            const short    �������
 Output:         none
 Return:         short         �ַ���ͨ�����
 Others:         
*************************************************************************/
short Cocr::ConnectedDomainIdentification(const unsigned char* image_binary,
                                    const short mode)
{
    int num = 0;
    Mat mat_binary = Mat(H + 2, W + 2, CV_8UC1, Scalar::all(255));
    for (int i = 0; i < H; i++) {
        unsigned char* p_mat = mat_binary.ptr<uchar>(i + 1);
        const unsigned char* p_image = image_binary + i * W;
            memcpy(p_mat + 1, p_image, W);
    }
    char new_value = 0;
    for (int i = 0; i < mat_binary.rows; i++) {
        unsigned char* p_mat = mat_binary.ptr<uchar>(i);
        for (int j = 0; j < mat_binary.cols; j++) {
            if (*(p_mat + j) == 255) {
                new_value++;
                int area = floodFill(mat_binary, Point(j, i), Scalar(new_value));
                if (area >= 12) {
                    num++;
                }
            }
        }
    }
    return num;
}
