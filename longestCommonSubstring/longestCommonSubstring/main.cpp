//
//  main.cpp
//  longestCommonSubstring
//
//  Created by Mykola Medynsky on 10/19/18.
//  Copyright © 2018 Mykola Medynskyi. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
void printLCSubStr(string str1, string str2, const int m,const int n)
{
     int matrix[m+1][n+1];
     int len = 0;
     int row, col;
     for (int i = 0; i <= m; i++) {
          for (int j = 0; j <= n; j++) {
               if (i == 0 || j == 0)
                    matrix[i][j] = 0;
               
               else if (str1[i - 1] == str2[j - 1]) {
                    matrix[i][j] = matrix[i - 1][j - 1] + 1;
                    if (len < matrix[i][j]) {
                         len = matrix[i][j];
                         row = i;
                         col = j;
                    }
               }
               else
                    matrix[i][j] = 0;
          }
     }
     
     if (len == 0) {
          cout << "there is no common substring";
     }
     else{
          char* resultStr = new char[len];
          while (matrix[row][col] != 0) {
               resultStr[--len] = str2[col - 1];
               row--;
               col--;
          }
          cout << resultStr;
     }
}
int main()
{
     string str1 = "1234lkjhgfdsagdg";
     string str2 = "dfgdfgdfgd1234";
     
     int m = str1.length()+1;
     int n = str2.length()+1;
     printLCSubStr(str1, str2, m, n);
     cout<< endl;
     return 0;
}
