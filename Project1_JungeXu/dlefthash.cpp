
#include <fstream>
#include <iostream>
#include<vector>
#include <cstdlib>
#include <ctime>
#include <set>

#define numOfFlows 1000
#define numOfEntries 1000
#define numOfSegments 4
using namespace std;

void dlefthash(vector<int> flows) {
    vector<int> hashTable(numOfEntries, -1);
    cout << "D-LEFTHASH BEGINS!:" << endl;
    int numOfHashes = numOfSegments;
    vector<int> range(numOfSegments, 0);
    int lengthOfSegment = numOfEntries / numOfSegments;
    for (int i = 1; i < numOfSegments; i++) {
        range[i] = range[i - 1] + lengthOfSegment;
    }
    vector<int> hash(numOfHashes, 0);
    int cnt = 0;
    srand((int)time(0));
    for (int i = 0; i < numOfHashes; i++) {
        hash[i] = rand();
    }
    for (int i = 0; i < numOfFlows; i++) {
        for (int j = 0; j < numOfSegments; j++) {
            int index = (flows[i] ^ hash[j]) % lengthOfSegment + range[j];
            if (hashTable[index] == -1) {
                hashTable[index] = flows[i];
                cnt++;
                break;
            }
        }
    }
    ofstream outfile;
    outfile.open("DLeftHash.dat");
    outfile << cnt <<endl;
    for (int i = 0; i < numOfEntries; i++) {
        if (hashTable[i] == -1) {
            hashTable[i] = 0;
        }
        outfile << "[" << i << "]:" << hashTable[i] << endl;
    }
    outfile.close();
    cout << "successful insert:" << cnt<<endl;
    return;
}

int main(){
    set<int> IDs;
    vector<int> flows;
    srand((int)time(0));
    while (IDs.size() < numOfFlows) {
        int temp = rand();
        if (IDs.insert(temp).second) {
            flows.push_back(temp);
        }
    }
    dlefthash(flows);
    return 0;
}


