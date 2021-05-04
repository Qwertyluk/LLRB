#include <iostream>
#include <map>

#include "llbr_map.h"
#include "llbr_map.cpp"

#include "LeftLeaningRedBlackTree.h"
//#include "LeftLeaningRedBlackTree.cpp"

using namespace std;

int main()
{
	LLRB_Map<std::string, int> LLRB_map;
	
	cout << "size 0: " << LLRB_map.size() << endl;
	cout << "empty true: " << LLRB_map.empty() << endl;

	// true
	bool b1 = LLRB_map.insert(make_pair("ala", 5));
	// true
	bool b2 = LLRB_map.insert(make_pair("ala2", 6));
	// false
	bool b3 = LLRB_map.insert(make_pair("ala2", 3));
	// false
	bool b4 = LLRB_map.insert(make_pair("ala", 10));
	// true
	bool b5 = LLRB_map.insert(make_pair("ala3", 3));
	// false
	bool b6 = LLRB_map.insert(make_pair("ala3", 0));

	// 5
	int& value1 = LLRB_map.at("ala");
	// 6
	int& value2 = LLRB_map.at("ala2");
	// 3
	int& value3 = LLRB_map.at("ala3");
	// 3
	const int& value4 = LLRB_map.at("ala3");

	// true
	bool b7 = LLRB_map.erase("ala");
	// false
	bool b8 = LLRB_map.erase("ala");
	// true
	bool b9 = LLRB_map.erase("ala3");

	// 1
	size_t size1 = LLRB_map.count("ala2");
	
	LLRB_map.insert(make_pair("ala3", 3));
	LLRB_map.clear();
		
	// 0
	size_t size2 = LLRB_map.count("ala2");
}