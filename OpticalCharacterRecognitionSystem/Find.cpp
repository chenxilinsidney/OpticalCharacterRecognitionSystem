/*************************************************************************
  Copyright (C),1988-1999, Cita109 Tech. Co., Ltd.  
  FileName:floodfill.c 
  Author: ChenXiLin       Version: 1.1         Date: 20131001
  Description:     查找数组   
  Version:        1.1  查找数组
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
