
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include<time.h>
#include <iostream>
#include <fstream>
#include <unordered_set>
#define FILTERSIZE 10000
#define NUMOFELEMENTS 1000
#define NUMOFHASHES 7
using namespace std;

vector<int> bloomFilter(FILTERSIZE, 0);
vector<int> hashes;

int lookup(vector<int> elements) {
	int cnt = 0;
	for (int i = 0; i < NUMOFELEMENTS; i++) {
		bool flag = true;
		for (int j = 0; j < NUMOFHASHES;j++) {
			if (bloomFilter[(elements[i] ^ hashes[j]) % FILTERSIZE] == 0) {
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
	outfile.open("BloomFilter.dat");
	outfile << cnt << endl;
	outfile.close();
	return cnt;
}

int main() {
	unordered_set<int> myset;
	srand(time(0));
	for (int i = 0; i < NUMOFHASHES; i++) {
		hashes.push_back(rand());
	}
	vector<int> A, B;
	while (A.size() < NUMOFELEMENTS) {
		int temp = rand();
		if (myset.insert(temp).second) {
			A.push_back(temp);
		}
	}
	while (B.size() < NUMOFELEMENTS) {
		int temp = rand();
		if (myset.insert(temp).second) {
			B.push_back(temp);
		}
	}
	//encode A:
	for (int i = 0; i < NUMOFELEMENTS; i++) {
		//A.push_back(rand());
		for (int j = 0; j < NUMOFHASHES; j++) {
			bloomFilter[(A[i] ^ hashes[j]) % FILTERSIZE] = 1;
		}
	}
	

	lookup(A);
	lookup(B);
	return 0;
}
