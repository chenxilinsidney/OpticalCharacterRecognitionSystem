/*************************************************************************
  Copyright (C),1988-1999, Cita109 Tech. Co., Ltd.  
  FileName:Find.cpp
  Author: ChenXiLin       Version: 1.1         Date: 20131001
  Description:     查找数组   
*************************************************************************/
/**************************** INCLUDE FILES *****************************/
#include "Cocr.h"
/**************************** INCLUDE FILES *****************************/
/*************************************************************************
 Function:       find  
 Description:    查找数组（short型）中符合给定范围
                 （value_min<=x<=value_max）内的元素索引 
 Calls:          none
 CalledBy:       judgeLetter_L;judgeNum_L;judgeChar;
                 judgeLetter_S;judgeNum_S;FloodFillLabel;
 TableAccessed:  none
 TableUpdated:   none
 Input:          array_input:     const short*   待查找数组
                 array_length:    const short    待查找数组数组的元素个数
                 value_min:       const short    查找下限
                 value_max:       const short    查找上限
 Output:         array_output:    short*         存放符合条件的元素的索引
 Return:                    short         查找到的元素个数
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
    // 函数返回
    return k;
}
