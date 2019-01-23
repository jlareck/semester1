//
//  main.cpp
//  lab1t13
//
//  Created by Mykola Medynsky on 9/8/18.
//  Copyright © 2018 Mykola Medynskyi. All rights reserved.
//

#include "BigMath.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    string str1 = "11111111111";
    string str2 = "99999999999";

    int size=0;
    printBigNumber(addBigNumbers(str1, str2, size), size);
    return 0;
}
