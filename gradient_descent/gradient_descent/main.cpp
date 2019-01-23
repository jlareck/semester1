//
//  main.cpp
//  gradient_descent
//
//  Created by Mykola Medynsky on 10/5/18.
//  Copyright © 2018 Mykola Medynskyi. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;
double derive(double x0)
{
    const double h = 1.0e-6;
    double x1 = x0 - h;
    double x2 = x0 + h;
    double y1 = sin(x1);
    double y2 = sin(x2);
    return (y2 - y1) / (x2 - x1);
}
int main(int argc, const char * argv[]) {
    const double alpha = 0.01;
    int max_iters = 10000;
    double precision = 0.00001;
    double previous_step_size = 1;
    int iter = 0;
    double curr_x = M_PI;
    cout<< "Enter the x:"<< endl;
    cin>> curr_x;
    double prev_x;
   // cout << derive(curr_x)<<endl;
    while((previous_step_size > precision)&&(iter<max_iters))
    {
        prev_x  = curr_x;
        curr_x -= alpha*derive(prev_x);
        //y = y + alpha*derivativeFunction(y);
        previous_step_size = abs(curr_x-prev_x);
        cout << iter << ' ' << curr_x<<endl;
        iter++;
    }
    cout<< "The minimum of the function = " <<curr_x<< endl;
    return 0;
}
