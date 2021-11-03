
#include <fstream>
#include <iostream>
#include<vector>
#include <cstdlib>
#include <ctime>
#include <set>

#define numOfFlows 1000
#define numOfEntries 1000
#define numOfMultiHashes 3
using namespace std;

vector<int> test;
void multihash(vector<int> flows)
{
    vector<int> hashTable(numOfEntries, -1);
    std::cout << "Multihash Begin!\n";
    vector<int> hash(numOfMultiHashes, 0);
    int cnt = 0;
    srand((int)time(0));
    for (int i = 0; i < numOfMultiHashes; i++){
        hash[i] = rand();
    }
    for (int i = 0; i < numOfFlows; i++){
        int j = 0;
        while (j < numOfMultiHashes && hashTable[(flows[i] ^ hash[j]) % numOfEntries] != -1) {
            j++;
        }
        if (j == numOfMultiHashes) {
            continue;
        }
        else{
            hashTable[(flows[i] ^ hash[j]) % numOfEntries] = flows[i];
            cnt++;
        }
    }
    ofstream outfile;
    outfile.open("MultiHash.dat");
    outfile <<cnt<< endl;
    for (int i = 0; i < numOfEntries; i++) {
        if (hashTable[i] == -1) {
            hashTable[i] = 0;
        }
        outfile << "[" << i << "]:" << hashTable[i] << endl;
    }
    outfile.close();
    cout << "total record is :" << cnt << endl;
    return ;
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
    multihash(flows); 
    return 0;
}


