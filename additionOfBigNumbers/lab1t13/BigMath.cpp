//
//  BigMath.cpp
//  lab1t13
//
//  Created by Mykola Medynsky on 9/12/18.
//  Copyright © 2018 Mykola Medynskyi. All rights reserved.
//

#include "BigMath.hpp"
using namespace std;
string getShorterString(string str1, string str2) {
    string smaller;
    if(str1.length() > str2.length())
        smaller = str2;
    else
        smaller = str1;
    return smaller;
}
string getLongerString(string str1, string str2) {
    string bigger;
    if(str1.length()>str2.length())
        bigger = str1;
    else
        bigger = str2;
    return bigger;
}
int* addBigNumbers(string str1, string str2, int& size) {
    string shorterString = getShorterString(str1, str2);
    string longerString = getLongerString(str1, str2);
    int sizeOfSmallerString = (int)shorterString.length()-1;
  
    int sizeOfBiggerString = (int)longerString.length()-1;
   
    int* arr1 = new int[sizeOfSmallerString+1];
    int* arr2 = new int[sizeOfBiggerString+1];
    for (int j = sizeOfSmallerString; j >= 0; j--) {
        arr1[j] = shorterString[j] - '0';
    }
    for (int j = sizeOfBiggerString; j>=0; j--) {
        arr2[j] = longerString[j] - '0';
    }

    size_t indexOfSumArray = sizeOfBiggerString+1;
  
    size_t sizeOfSumArray = indexOfSumArray;
    int* sumArray = new int[sizeOfSumArray+1];
    
    for (int i=0; i<=sizeOfSumArray; i++) {
        sumArray[i]=0;
    }
    
    
    while (indexOfSumArray != 0) {
        if(sizeOfSmallerString>-1)
            sumArray[indexOfSumArray] += arr1[sizeOfSmallerString]+arr2[sizeOfBiggerString];
        else
            sumArray[indexOfSumArray] += arr2[sizeOfBiggerString];

        if(sumArray[indexOfSumArray]>=10)
        {
            sumArray[indexOfSumArray-1]=1;
            sumArray[indexOfSumArray]-=10;
        }
        //cout << arr[indexOfSumArray] << endl;
        indexOfSumArray--;
        sizeOfBiggerString--;
        sizeOfSmallerString--;
    }
    size = (int)sizeOfSumArray;
    return sumArray;
}

void printBigNumber(int* sumArray, const int& size) {
    if(sumArray[0]>0) {
        for (int i = 0; i <= size; i++) {
           cout<< sumArray[i];
        }
    }
    else{
        for (int i=1; i <= size; i++) {
           cout<< sumArray[i];
        }
    }
    cout << endl;
   // delete[] sumArray;
}
