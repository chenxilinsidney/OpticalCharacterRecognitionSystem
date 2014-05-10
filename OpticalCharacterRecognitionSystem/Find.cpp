/*************************************************************************
  Copyright (C),1988-1999, Cita109 Tech. Co., Ltd.  
  FileName:floodfill.c 
  Author: ChenXiLin       Version: 1.1         Date: 20131001
  Description:     ��������   
  Version:        1.1  ��������
  FunctionList:
    1.short find(const short* array_input,
                    const short array_length,
                    const short value_min,
                    const short value_max,
                    short* array_output);
  History:          add new function, edit the comments
     <author>         <time>   <version >  <desc>  
     Chen Xin Yuan    13/02/01    1.0     build this moudle 
     Chen Xi Lin      13/10/01    1.1     modify the comments
     Wan Yan Ying     14/01/15    1.1     add new function 4
     Chen Xi Lin      14/02/21    1.1     speed function 2 and function 4
*************************************************************************/
/**************************** INCLUDE FILES *****************************/
#include "stdafx.h"
#include "Cocr.h"
/**************************** INCLUDE FILES *****************************/
/*************************************************************************
 Function:       find  
 Description:    �������飨short�ͣ��з��ϸ�����Χ
                 ��value_min<=x<=value_max���ڵ�Ԫ������ 
 Calls:          none
 CalledBy:       judgeLetter_L;judgeNum_L;judgeChar;
                 judgeLetter_S;judgeNum_S;FloodFillLabel;
 TableAccessed:  none
 TableUpdated:   none
 Input:          array_input:     const short*   ����������
                 array_length:    const short    ���������������Ԫ�ظ���
                 value_min:       const short    ��������
                 value_max:       const short    ��������
 Output:         array_output:    short*         ��ŷ���������Ԫ�ص�����
 Return:                    short         ���ҵ���Ԫ�ظ���
 Others:         
*************************************************************************/
short Cocr::find(const short* array_input,
           short* array_output,
           const short array_length,
           const short value_min,
           const short value_max)
{
    short i, k = 0;
    if (array_output == NULL && value_min == value_max) {
        for (i = 0; i < array_length; i++) {
            if (*(array_input + i) == value_min) {
                return 1;
            }
        }
        return 0;
    }
    for( i = 0; i < array_length; i++ )
        array_output[ i ] = -1;
    for( i = 0; i < array_length; i++ )
        if( ( array_input[ i ] >= value_min )  &&  ( array_input[ i ] <= value_max ) )
        {
            array_output[ k ] = i;
            k++;
        }
    // ��������
    return k;
}
