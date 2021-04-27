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
	void Free(Node* node);

public:
	LeftLeaningBlackTree();
	~LeftLeaningBlackTree();

	void Insert(KeyValue keyValue);
};