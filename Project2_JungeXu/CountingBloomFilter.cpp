// CountingBloomFilter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#define FILTERSIZE 10000
#define SIZEOFA 1000
#define NUMOFREMOVE 500
#define SIZEOFB 500
#define NUMOFHASHES 7
using namespace std;

vector<int> filter(FILTERSIZE, 0);
vector<int> hashes;
int remove(vector<int> elements) {
    for (int i = 0; i < NUMOFREMOVE; i++) {
        //delete the first 500 elements in set A
        for (int j = 0; j < NUMOFHASHES; j++) {
            filter[(elements[i] ^ hashes[j]) % FILTERSIZE]--;
        }
    }
    return 0;
}

int add(vector<int> elements) {

    for (int i = 0; i < SIZEOFB; i++) {
        //delete the first 500 elements in set A
        for (int j = 0; j < NUMOFHASHES; j++) {
            filter[(elements[i] ^ hashes[j]) % FILTERSIZE]++;
        }
    }
    return 0;
}

int lookup(vector<int> elements) {
    int cnt = 0;
    int n = elements.size();
    for (int i = 0; i < n; i++) {
        bool flag = true;
        for (int j = 0; j < NUMOFHASHES; j++) {
            if (filter[(elements[i] ^ hashes[j]) % FILTERSIZE] < 1) {
                flag = false;
                break;
            }
        }
        if (flag == true) {
            cnt++;
        }
    }
    cout << "es in the filter:" << cnt << endl;
    ofstream outfile;
    outfile.open("CountingBloomFilter.dat");
    outfile << cnt << endl;
    outfile.close();
    return cnt;
}
int main() {
    srand(time(0));
    for (int i = 0; i < NUMOFHASHES; i++) {
        hashes.push_back(rand());
    }
    vector<int> A, B;
    for (int i = 0; i < SIZEOFA; i++) {
        A.push_back(rand()*10000+ rand());
        for (int j = 0; j < NUMOFHASHES; j++) {
            filter[(A[i] ^ hashes[j]) % FILTERSIZE]++;
        }
    }
    for (int i = 0; i < SIZEOFB; i++) {
        B.push_back(rand() * 10000 + rand());
    }

    remove(A);
    add(B);
    lookup(A);
    return 0;
}

