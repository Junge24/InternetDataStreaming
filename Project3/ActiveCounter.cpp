// ActiveCounter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <cmath>
#define N 1000000
#define BITS_NUM 16 // number of bits used for the number part of the counter
#define BITS_EXP 16 // number of bits used for the number part of the counter
using namespace std;

int main()
{
    unsigned int cn = 0;
    unsigned int ce = 0;

    srand(time(0));
    int numberMax = pow(2,BITS_NUM)-1;
    int expoMax = pow(2, BITS_EXP) - 1;
    for (int i = 0; i < N; i++) {

        if (cn >= numberMax) {
            cn = cn >> 1;
            ce++;
            if (ce > expoMax) {
                cout << "ce overflow" << endl;
            }
            //cout << "right shift" << endl;
        }
        double randnum = rand();
        //cout << randnum << endl;
        if (randnum <= RAND_MAX * pow(pow(2, ce),-1)) {
            cn++;
        }
    }
   
    //cout << "cn:" << cn << "ce:" << ce << endl;
    long long int res = cn * pow(2, ce);
    cout << "res:" << res << endl;

    ofstream outfile;
    outfile.open("activecounter.dat");
    outfile << res << endl;
    outfile.close();
    return cn * pow(2, ce);
}

