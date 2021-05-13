#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <string>

#include "llbr_map.h"
#include "LeftLeaningRedBlackTree.h"

using namespace std;

int main()
{
	LLRB_Map<string, string> myMap;
	map<string, string> cppMap;

	ifstream dicFile("english.dic");

	string tempStr;
	int i = 0;
	int baseTime = 5000;
	int j = baseTime;
	while (getline(dicFile, tempStr))
	{
		i++;
		if (i % j == 0 )
		{
			j = j + baseTime;
			cout << cppMap.size() << endl;
			cout << myMap.size() << endl;

			chrono::steady_clock::time_point cppMapBegin = chrono::steady_clock::now();
			cppMap.insert(make_pair(tempStr, tempStr)); 
			std::chrono::steady_clock::time_point cppMapEnd = std::chrono::steady_clock::now();
			cout << "cppMap time: " << chrono::duration_cast<chrono::microseconds>(cppMapEnd - cppMapBegin).count() << endl;

			chrono::steady_clock::time_point myMapBegin = chrono::steady_clock::now();
			myMap.insert(make_pair(tempStr, tempStr));
			std::chrono::steady_clock::time_point myMapEnd = std::chrono::steady_clock::now();
			cout << "myMap time: " << chrono::duration_cast<chrono::microseconds>(myMapEnd - myMapBegin).count() << endl;
		}
		else 
		{
			cppMap.insert(make_pair(tempStr, tempStr));
			myMap.insert(make_pair(tempStr, tempStr));
		}
	}

	cout << endl << endl << endl;

	chrono::steady_clock::time_point cppMapBeginAt = chrono::steady_clock::now();
	cppMap.at("juiciest");
	std::chrono::steady_clock::time_point cppMapEndAt = std::chrono::steady_clock::now();
	cout << "cppMap time: " << chrono::duration_cast<chrono::microseconds>(cppMapEndAt - cppMapBeginAt).count() << endl;

	chrono::steady_clock::time_point myMapBeginAt = chrono::steady_clock::now();
	myMap.at("juiciest");
	std::chrono::steady_clock::time_point myMapEndAt = std::chrono::steady_clock::now();
	cout << "cppMap time: " << chrono::duration_cast<chrono::microseconds>(myMapEndAt - myMapBeginAt).count() << endl;

	for (auto& v : myMap)
	{
		cout << v.getKeyValue().Value << endl;
	}
}