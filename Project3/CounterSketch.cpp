#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
#include<time.h>

#define numOfCounterArrays 3
#define numOfCounters 3000
#define OUTPUTLINES 100
#define FILENAME "project3input.txt"
using namespace std;

struct flow {
    string ipad;
    int numOfPkts;
    uint32_t id;
    double estimatedSizes;
    double error;
};

//num of flows:n
int n;
vector<flow> flows;
vector< vector<int> > counters(numOfCounterArrays, vector<int>(numOfCounters, 0));
vector<int> hashes;
uint32_t myhash(uint32_t a)
{
    a = (a + 0x7ed55d16) + (a << 12);
    a = (a ^ 0xc761c23c) ^ (a >> 19);
    a = (a + 0x165667b1) + (a << 5);
    a = (a + 0xd3a2646c) ^ (a << 9);
    a = (a + 0xfd7046c5) + (a << 3);
    a = (a ^ 0xb55a4f09) ^ (a >> 16);
    return a;
}

bool GreaterSort(flow a, flow b) { return (a.estimatedSizes > b.estimatedSizes); }

void query() {
    double totalError = 0;
    for (int i = 0; i < n; i++) {
        vector<int> ests;
        for (int j = 0; j < numOfCounterArrays; j++) {
            ests.push_back(abs( counters[j][(myhash((flows[i].id ^ hashes[j])) >> 1) % numOfCounters] ));
        }
        sort(ests.begin(), ests.end());
        if (numOfCounterArrays % 2 == 1) {
            flows[i].estimatedSizes = ests[numOfCounterArrays / 2];
        }
        else {
            flows[i].estimatedSizes = ((double)(ests[(numOfCounterArrays - 1) / 2] + (double)ests[numOfCounterArrays / 2])) / 2;
        }
        flows[i].error = abs(flows[i].estimatedSizes - flows[i].numOfPkts);
        totalError += flows[i].error;
    }
    sort(flows.begin(), flows.end(), GreaterSort);
    ofstream outfile;
    outfile.open("countsketch.dat");
    outfile << (double)totalError / n << endl;
    for (int i = 0; (i < OUTPUTLINES) && (i < n); i++) {
        outfile << flows[i].ipad << "\t" << flows[i].estimatedSizes << "\t" << flows[i].numOfPkts << endl;
    }
    outfile.close();
    cout << "error is" << totalError / n << endl;
}


int main()
{
    std::hash<string> str_hash;
    ifstream fp;
    string infileName = FILENAME;
    fp.open(infileName);
    if (!fp) {
        std::cout << "this file doesn't exist! Please check the file and try again later!\n" << endl;
        system("pause");
        return 1;
    }
    fp >> n;
    flows.resize(n);
    cout << "n:" << n << endl;
    //vector<vector<int>> bit32(n, vector<int>(32, 0));

    for (int i = 0; i < n; i++) {
        fp >> flows[i].ipad >> flows[i].numOfPkts;
        flows[i].id = str_hash(flows[i].ipad);
    }
    srand(time(0));
    for (int i = 0; i < numOfCounterArrays; i++) {
        uint32_t randnum = (rand()<<15 | rand());
        hashes.push_back(randnum);
        cout << hex << hashes[i] << endl;

    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < numOfCounterArrays; j++) {
            int sign = 0;
            //cout  << hex << (flows[i].id ^ hashes[j]) << endl;
            if ((1 & myhash(flows[i].id ^ hashes[j])) == 0){
                sign = -1;
            }
            else {
                sign = 1;
            }
            counters[j][ (myhash((flows[i].id ^ hashes[j])) >>1 ) % numOfCounters] += sign*flows[i].numOfPkts;
        }
    }
    query();
    return 0;
}

//void split(const string& s, vector<string>& tokens, char delim) {
//    tokens.clear();
//    auto string_find_first_not = [s, delim](size_t pos = 0) -> size_t {
//        for (size_t i = pos; i < s.size(); i++) {
//            if (s[i] != delim) return i;
//        }
//        return string::npos;
//    };
//    size_t lastPos = string_find_first_not(0);
//    size_t pos = s.find(delim, lastPos);
//    while (lastPos != string::npos) {
//        tokens.emplace_back(s.substr(lastPos, pos - lastPos));
//        lastPos = string_find_first_not(pos);
//        pos = s.find(delim, lastPos);
//    }
//}
//int decToBinary(size_t n)
//{
//    // array to store binary number
//    int binaryNum[32];
//    string binaryN = "";
//    // counter for binary array
//    int i = 0;
//    while (n > 0) {
//
//        // storing remainder in binary array
//        binaryNum[i] = n % 2;
//        binaryN = to_string(binaryNum[i]) + binaryN;
//        n = n / 2;
//        i++;
//    }
//    cout << binaryN.size() << endl;
//    return 0;
//}