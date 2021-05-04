#pragma once

#include <utility>

#include "KeyValuePair.h"


#define RED true;
#define BLACK false;

template<class Key, class T>
class LeftLeaningBlackTree 
{
private:
	struct Node
	{
		KeyValue<Key, T> KeyValue;

		bool color;

		Node* leftNode;
		Node* rightNode;
	};
	Node* root;
	std::pair<Node*, bool> InsertRec(Node* node, KeyValue<Key, T> keyValue);
	Node* NewNode(KeyValue<Key, T> keyValue);
	Node* DeleteMin(Node* node);
	void Free(Node* node);
	std::pair<Node*, bool> DeleteRec(Node* node, Key key);
	Node* RotateLeft(Node* node);
	Node* RotateRight(Node* node);
	void ColorFlip(Node* node);
	inline bool IsRed(Node* node);
	Node* MoveRedLeft(Node* node);
	Node* MoveRedRight(Node* node);
	Node* FindMin(Node* node);
	Node* FixUp(Node* node);
	Node* FindRec(Node* node, Key key);

public:
	LeftLeaningBlackTree();
	~LeftLeaningBlackTree();

	bool Insert(KeyValue<Key, T> keyValue);
	KeyValue<Key, T> GetMin();
	KeyValue<Key, T>* Find(Key key);
	void DeleteMin();
	bool Delete(Key key);
	void Clear();
};