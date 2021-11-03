// Project3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;
#define FILENAME "project3input.txt"
#define numOfCounterArrays 3
#define numOfCounters 3000
#define OUTPUTLINES 100
struct flow {
    string ipad;
    int numOfPkts;
    long long int id;
    int estimatedSizes;
    int error;
};
//num of flows:n
int n;
vector<flow> flows;
vector< vector<int> > counters(numOfCounterArrays, vector<int>(numOfCounters, 0));
vector<int> hashes;


bool GreaterSort(flow a, flow b) { return (a.estimatedSizes > b.estimatedSizes); }
void query() {
    int totalError = 0;
    for (int i = 0; i < n; i++) {
        int temp = (hashes[0] ^ flows[i].id) % numOfCounters;
        int min = counters[0][temp];
        for (int j = 1; j < numOfCounterArrays; j++) {
            if (counters[j][(hashes[j] ^ flows[i].id) % numOfCounters] < min) {
                int targetIndex = (hashes[j] ^ flows[i].id) % numOfCounters;
                min = counters[j][targetIndex];
            }
        }
        flows[i].estimatedSizes = min;
        flows[i].error = flows[i].estimatedSizes - flows[i].numOfPkts;
        totalError += flows[i].error;
    }

    sort(flows.begin(), flows.end(), GreaterSort);
    ofstream outfile;
    outfile.open("countmin.dat");
    outfile << (double)totalError / n << endl;
    cout << (double)totalError / n << endl;
    for (int i = 0; i < OUTPUTLINES && i < n; i++) {
        //cout << flows[i].id << endl;
        outfile << flows[i].ipad << "\t" << flows[i].estimatedSizes << "\t" << flows[i].numOfPkts << endl;
    }
    outfile.close();
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
    //flows
    //vector<pair<long long int,int>> flows(n);
    string temp;
    for (int i = 0; i < n; i++) {
        fp >> flows[i].ipad >> flows[i].numOfPkts;
        //cout << str_hash(temp) << endl;
        flows[i].id = str_hash(flows[i].ipad);
        //cout << flows[i].first <<"  "<< flows[i].second << endl;
    }
    srand(time(0));
    for (int i = 0; i < numOfCounterArrays; i++) {
        hashes.push_back(rand());
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < numOfCounterArrays; j++) {
            counters[j][(hashes[j] ^ flows[i].id) % numOfCounters] += flows[i].numOfPkts;
        }
    }
    query();
}


