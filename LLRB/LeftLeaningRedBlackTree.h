#pragma once

#include "KeyValuePair.h"

#define RED true;
#define BLACK false;

struct Node 
{
	KeyValue KeyValue;

	bool color;

	Node* leftNode;
	Node* rightNode;
};

class LeftLeaningBlackTree 
{
private:
	Node* root;
	Node* InsertRec(Node* node, KeyValue keyValue);
	Node* NewNode(KeyValue keyValue);
	Node* DeleteMin(Node* node);
	void Free(Node* node);
	Node* DeleteRec(Node* node, unsigned int key);

public:
	LeftLeaningBlackTree();
	~LeftLeaningBlackTree();

	void Insert(KeyValue keyValue);
	KeyValue GetMin();
	void DeleteMin();
	void Delete(unsigned int key);
};