//
//  main.cpp
//  possibleTriangle2.0
//
//  Created by Mykola Medynsky on 10/25/18.
//  Copyright © 2018 Mykola Medynskyi. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
void isPossibleTriangle(int arr[],int n)
{
    int r, l;
    sort(arr, arr+n);
    for (int i = 0; i < n-2; i++){
        for (int j = i+1; j< n-1; j++ )
        {
            l = j+1;
            r = n-1;
            while(r - l != -1)
            {
                int mid = l + (r-l)/2;
                if((arr[i]*arr[i])+(arr[j]*arr[j])>(arr[mid]*arr[mid]))
                    l = mid+1;
                else
                    r = mid-1;
            }
            for (int k = j+1; k<l; k++){
                    cout << arr[i]<< ' ' <<arr[j]<< ' '<<arr[k]<<endl;
            }
        }

    }
}
int main()
{
    int arr[] = {3,4, 6, 7,8,10,20,24,25,30,31,33};
    int N = sizeof(arr) / sizeof(int);
    
    isPossibleTriangle(arr, N);
    
    return 0;
}
