/***************************************************************************
 * 
 * Copyright (c) 2014 izptec.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/



/**
 * @file lis.cpp
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/03/10 09:43:57
 * @version 1.0 
 * @brief 
 *  
 **/

//数组中最长递增子序列
#include <iostream>
#include <string.h>
using namespace std;

#define INT_MAX 0xefffffff

template<class T>
inline T MaxInTwoElement(const T&a, const T &b)
{
    return a>b?a:b;
}

int Slove1(const int *, int);//使用DP寻找，O(N^2)， DP[i] =Max{DP[j]+1,DP[i]}(DP[i]>DP[j])
int Slove2(const int *, int);//使用另外的数组保存长度为n的LIS最大元素的最小值
int Slove3(const int *, int);
int Dp[20];

void Initialize()
{
    memset(Dp,0,sizeof(Dp));
    Dp[0] = 1;
}

int main()
{
    int (*p[3])(const int*, int) = {&Slove1,&Slove2,&Slove3};
    int Data[] = {1,-1,2,-3,4,-5,6,-7};
    for (int i = 0;i<3;++i)
    {
        cout<<p[i](Data,sizeof(Data)/sizeof(int))<<endl;
    }
    return 0;
}

int Slove1(const int *Data, int length)
{
    Initialize();
    int Max = 1;
    for (int i = 1; i<length; ++i)
    {
        for (int j = 0; j<i; ++j)
        {
            if (Data[i] > Data[j])
            {
                Dp[i] = MaxInTwoElement(Dp[j] + 1,Dp[i]);
            }
        }
        Max = Max>Dp[i]?Max:Dp[i];
    }
    return Max;
}
int Slove2(const int *Data, int length)
{
    int *MaxEle = new int[length +1];
    MaxEle[0] = -INT_MAX;
    MaxEle[1] = Data[0];
    //initialize
    for (int i =0; i<length; ++i)
        Dp[i] = 1;
    int maxLength = 1;
    for (int i=1; i<length; ++i)//traversing the array
    {
        int j;
        for (j=maxLength; j>-1; --j)//find the Max element int the LIS
        {
            if (Data[i] > MaxEle[j])//j is the length of sequence, too
            {//means it can be added to the sequence
                Dp[i] = j+1;
                break;
            }
        }
        //now j = 0 or the index which firstly satisfied Data[i] > MaxEle[j] 
        if (Dp[i] > maxLength)
        {//update the length and the element in MaxEle according to the length
            maxLength = Dp[i];
            MaxEle[Dp[i]] = Data[i];
        }
        else if(Data[i] > MaxEle[j]  && Data[i] < MaxEle[j+1])
        {//当前的值并不比最大长度大，则更新
            MaxEle[j+1] = Data[i];
        }
    }
    return maxLength;
}
int Slove3(const int *Data, int length)
{
    int *MaxEle = new int[length +1];
    MaxEle[0] = -INT_MAX;
    MaxEle[1] = Data[0];
    //initialize
    for (int i =0; i<length; ++i)
        Dp[i] = 1;
    int maxLength = 1;
    for (int i=1; i<length; ++i)//traversing the array
    {
        int j;
        //        int bg = 0;
        //        int end = maxLength;
        //here, cuz the MaxEle is ordered( can be proved), 
        //we can use binary search
        //        while (true)
        //        {
        //            j = (bg +end)/2;
        //            if (Data[i] > MaxEle[j])
        //            {
        //                Dp[i] = j+1;
        //                break;
        //            }
        //            else 
        //            {
        //                end = j;
        //            }
        //        }
        for (j=maxLength; j>0; --j)//find the Max element int the LIS
        {
            if (Data[i] > MaxEle[j])//j is the length of sequence, too
            {//means it can be added to the sequence
                Dp[i] = j+1;
                break;
            }
        }
        //now j = 0 or the index which firstly satisfied Data[i] > MaxEle[j] 
        if (Dp[i] > maxLength)
        {//update the length and the element in MaxEle according to the length
            maxLength = Dp[i];
            MaxEle[Dp[i]] = Data[i];
        }
        else if(Data[i] > MaxEle[j]  && Data[i] < MaxEle[j+1])
        {//当前的值并不比最大长度大，则更新
            MaxEle[j+1] = Data[i];
        }
    }
    return maxLength;
}



















/* vim: set ts=256 sw=4 sts=4 tw=80 expandtab noet: */
