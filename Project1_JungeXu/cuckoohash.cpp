#include <iostream>
#include<vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <fstream>
#define numOfFlows 1000
#define numOfEntries 1000
#define numOfCuckooHashes 3
#define STEP 2
using namespace std;

bool move(vector<int>& table, vector<int>& hash, int index, int numOfHashes, int step) {
    if (step == 0) {
        return false;
    }
    int oldID = table[index];
    for (int i = 0; i < numOfHashes; i++) {
        int newKey = (oldID ^ hash[i]) % numOfEntries;
        if (newKey != index && table[newKey] == -1) {
            table[newKey] = oldID;
            table[index] = -1;
            return true;
        }
    }
    for (int i = 0; i < numOfHashes; i++) {
        int newKey = (oldID ^ hash[i]) % numOfEntries;
        if (newKey != index && move(table, hash, newKey, numOfHashes, step - 1)) {
            table[newKey] = oldID;
            return true;
        }
    }
    return false;
}
void cuckoohash(vector<int> flows) {
    vector<int> hashTable(numOfEntries, -1);
    std::cout << "Cuckoohash Begin!\n";
    vector<int> hash(numOfCuckooHashes, 0);
    int cnt = 0;
    srand((int)time(0));
    for (int i = 0; i < numOfCuckooHashes; i++) {
        hash[i] = rand();
    }
    for (int i = 0; i < numOfFlows; i++) {
        int j = 0;
        bool findEmptyRecord = false;
        while (j < numOfCuckooHashes && hashTable[(flows[i] ^ hash[j]) % numOfEntries] != -1) {
            j++;
        }

        if (j < numOfCuckooHashes) {
            hashTable[(flows[i] ^ hash[j]) % numOfEntries] = flows[i];
            cnt++;
        }
        else {
            //not find a empty space to record the flowID: Try to move others  
            for (int k = 0; k < numOfCuckooHashes; k++) {
                int temp = (flows[i] ^ hash[k]) % numOfEntries;
                if (move(hashTable, hash, temp, numOfCuckooHashes, STEP)) {
                    hashTable[temp] = flows[i];
                    cnt++;
                    break;
                }
            }
        }
    }
    ofstream outfile;
    outfile.open("CuckooHash.dat");
    outfile << cnt << endl;

    for (int i = 0; i < numOfEntries; i++) {
        if (hashTable[i] == -1) {
            hashTable[i] = 0;
        }
        outfile << "[" << i << "]:" << hashTable[i] << endl;
    }
    cout << "total record is :" << cnt << endl;
    outfile.close();

    return;
}

int main() {
    set<int> IDs;
    vector<int> flows;
    srand((int)time(0));
    while (IDs.size() < numOfFlows) {
        int temp = rand();
        if (IDs.insert(temp).second) {
            flows.push_back(temp);
        }
    }
    cuckoohash(flows);
    return 0;
}