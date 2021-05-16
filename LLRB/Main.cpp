#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <string>
#include <algorithm>

#include "llbr_map.h"
#include "LeftLeaningRedBlackTree.h"
#include "Node.h"
#include "Iterator.h"

using namespace std;

int main()
{
	LLRB_Map<int, int> testMap;
	testMap.insert(make_pair(25, 25));
	testMap.insert(make_pair(50, 50));
	testMap.insert(make_pair(15, 15));
	testMap.insert(make_pair(22, 22));

	LLRB_Map<int, string> implMap;
	map<int, string> cppMap;

	ifstream dicFile("english.dic");

	string tempStr;
	ofstream fileImplMapInsert;
	ofstream fileCppMapInsert;
	ofstream fileImplMapAt;
	ofstream fileCppMapAt;
	ofstream fileImplMapErase;
	ofstream fileCppMapErase;
	fileImplMapInsert.open("implMapInsert.csv");
	fileCppMapInsert.open("cppMapInsert.csv");
	fileImplMapAt.open("implMapAt.csv");
	fileCppMapAt.open("cppMapAt.csv");
	fileImplMapErase.open("implMapErase.csv");
	fileCppMapErase.open("cppMapErase.csv");

	int nLines = 0;
	while (getline(dicFile, tempStr))
	{
		nLines++;
	}
	dicFile.clear();
	dicFile.seekg(0);

	int* integers = new int[nLines];
	for (int i = 0; i < nLines; i++)
	{
		integers[i] = i + 1;
	}
	random_shuffle(&integers[0], &integers[nLines]);

	for(int i = 1 ; i <= nLines; i++)
	{
		getline(dicFile, tempStr);
		chrono::steady_clock::time_point cppMapInsertBegin = chrono::steady_clock::now();
		cppMap.insert(make_pair(integers[i - 1], tempStr));
		std::chrono::steady_clock::time_point cppMapInsertEnd = std::chrono::steady_clock::now();
		fileCppMapInsert << chrono::duration_cast<chrono::nanoseconds>(cppMapInsertEnd - cppMapInsertBegin).count() << endl;

		chrono::steady_clock::time_point implMapInsertBegin = chrono::steady_clock::now();
		implMap.insert(make_pair(integers[i - 1], tempStr));
		std::chrono::steady_clock::time_point implMapInsertEnd = std::chrono::steady_clock::now();
		fileImplMapInsert << chrono::duration_cast<chrono::nanoseconds>(implMapInsertEnd - implMapInsertBegin).count() << endl;
		
		int rnd = rand() % i + 1;

		chrono::steady_clock::time_point cppMapAtBegin = chrono::steady_clock::now();
		cppMap.at(integers[rnd - 1]);
		std::chrono::steady_clock::time_point cppMapAtEnd = std::chrono::steady_clock::now();
		fileCppMapAt << chrono::duration_cast<chrono::nanoseconds>(cppMapAtEnd - cppMapAtBegin).count() << endl;

		chrono::steady_clock::time_point implMapAtBegin = chrono::steady_clock::now();
		implMap.at(integers[rnd - 1]);
		std::chrono::steady_clock::time_point implMapAtEnd = std::chrono::steady_clock::now();
		fileImplMapAt << chrono::duration_cast<chrono::nanoseconds>(implMapAtEnd - implMapAtBegin).count() << endl;
	}

	int* indexes = new int[cppMap.size()];
	for (int i = 0; i < cppMap.size(); i++) {
		indexes[i] = i + 1;
	}
	random_shuffle(&indexes[0], &indexes[cppMap.size()]);

	for (int i = cppMap.size() - 1; i >= 0; i--)
	{
		chrono::steady_clock::time_point cppMapEraseBegin = chrono::steady_clock::now();
		size_t n1 = cppMap.erase(indexes[i]);
		std::chrono::steady_clock::time_point cppMapEraseEnd = std::chrono::steady_clock::now();
		fileCppMapErase << chrono::duration_cast<chrono::nanoseconds>(cppMapEraseEnd - cppMapEraseBegin).count() << endl;

		chrono::steady_clock::time_point implMapEraseBegin = chrono::steady_clock::now();
		size_t n2 = implMap.erase(indexes[i]);
		std::chrono::steady_clock::time_point implMapEraseEnd = std::chrono::steady_clock::now();
		fileImplMapErase << chrono::duration_cast<chrono::nanoseconds>(implMapEraseEnd - implMapEraseBegin).count() << endl;
	}

	delete[] indexes;
	delete[] integers;

	cout << cppMap.size() << endl;
	cout << implMap.size() << endl;
}