#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include <time.h>
#include <iostream>
#include <string> 
#include <fstream>
#define NUMOFSETS 7
#define SETSIZE 1000
#define NUMOFFILTERS 3
#define FILTERSIZE 30000
#define NUMOFHASHES 7
using namespace std;
vector<vector<int>> filters(NUMOFFILTERS,vector<int>(FILTERSIZE, 0));
vector<vector<int>> sets(NUMOFSETS, vector<int>(SETSIZE, 0));
vector<int> hashes;

vector<int> toBinary(int n)
{
    vector<int> code(NUMOFFILTERS, 0);
    int i = NUMOFFILTERS - 1;
    while(n > 0)
    {
        code[i] = n % 2;
        n = n / 2;
        i--;
    }
    return code;
}

int encode() {
    for (int s = 0; s < NUMOFSETS; s++) {
        int setID = s + 1;
        vector<int> BinaryID = toBinary(setID);
       /*for (int i = 0; i < NUMOFFILTERS; i++) {
           std::cout << BinaryID[i];
        }*/
       //std::cout <<endl;
        for (int i = 0; i < NUMOFFILTERS; i++) {
            if (BinaryID[i]==1) {
                for (int e = 0; e < SETSIZE; e++) {
                    for (int h = 0; h < NUMOFHASHES; h++) {
                        filters[i][(sets[s][e] ^ hashes[h]) % FILTERSIZE] = 1;
                    }
                }
            }
        }
        //cout << endl;
    }
    return 0;
}

int lookup() {
    int cnt = 0;
    for (int s = 0; s < NUMOFSETS; s++) {
        int mis = 0;
        for (int e = 0; e < SETSIZE; e++) {
            int belongs = 0;
            int code = 0;
            for (int i = 0; i <NUMOFFILTERS; i++) {
                bool flag = true;
                for (int h = 0; h < NUMOFHASHES; h++) {
                    if (filters[i][(sets[s][e] ^ hashes[h])%FILTERSIZE] == 0) {
                        flag = false;
                        // 不属于filter i
                    }
                }
                if (flag == true) {
                    // 属于filter i;
                    code = code * 2 + 1;
                }
                else {
                    code = code * 2;
                }
            }
            if (code == s + 1) {
                cnt++;
            }
            else {
                //std::cout << code << endl;
                mis++;
            }
        }
       //std::cout << "correct e in set"<<s+1<<": "<<cnt<<" missMatch:"<<mis << endl;
    }
    std::cout << cnt << endl;

    ofstream outfile;
    outfile.open("CodedBloomFilter.dat");
    outfile << cnt << endl;
    outfile.close();
    return 0;
}

int main() {
    srand(time(0));
    
    for (int i = 0; i < NUMOFHASHES; i++) {
        hashes.push_back(rand());
    }
    set<int> elems;
    
    for (int i = 0; i < NUMOFSETS; i++) {
        int j = 0;
        while (j < SETSIZE) {
            int temp = rand()*10000+ rand();
            if (elems.insert(temp).second) {
                sets[i][j++] = temp;
            }
        }
    }
    //cout <<"total num of elems"<< elems.size() << endl;
    encode();
    lookup();
    return 0;
}

