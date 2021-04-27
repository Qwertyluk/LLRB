#include "LeftLeaningRedBlackTree.h"
#include <cstddef>



// left rotation
static Node* RotateLeft(Node* node)
{
	Node* temp = node->rightNode;
	node->rightNode = temp->leftNode;
	temp->leftNode = node;
	temp->color = node->color;
	node->color = RED;

	return temp;
}

// right rotation
static Node* RotateRight(Node* node)
{
	Node* temp = node->leftNode;
	node->leftNode = temp->rightNode;
	temp->rightNode = node;
	temp->color = node->color;
	node->color = RED;

	return temp;
}

// color flip
static void ColorFlip(Node* node)
{
	node->color = !node->color;

	if (node->leftNode != NULL) {
		node->leftNode->color = !node->leftNode->color;
	}

	if (node->rightNode != NULL) {
		node->rightNode->color = !node->rightNode->color;
	}
}

// check if a node is red
static inline bool IsRed(Node* node)
{
	return (node != NULL) && node->color;
}

// constructor
LeftLeaningBlackTree::LeftLeaningBlackTree() 
{
	this->root = NULL;
}

// destructor
LeftLeaningBlackTree::~LeftLeaningBlackTree() 
{
	this->Free(this->root);
}

// creation of a new node
Node* LeftLeaningBlackTree::NewNode(KeyValue keyValue)
{
	Node* newNode = new Node;
	newNode->KeyValue.Key = keyValue.Key;
	newNode->KeyValue.Value = keyValue.Value;
	newNode->color = RED;
	newNode->leftNode = NULL;
	newNode->rightNode = NULL;

	return newNode;
}

// insertion of a new node
void LeftLeaningBlackTree::Insert(KeyValue keyvalue)
{
	this->root = this->InsertRec(this->root, keyvalue);
	this->root->color = BLACK;
}

// recursive insertion
Node* LeftLeaningBlackTree::InsertRec(Node* node, KeyValue keyValue)
{
	// insert a leaf
	if (node == NULL)
	{
		node = this->NewNode(keyValue);
		return node;
	}

	// check if value is already in the tree
	if (keyValue.Key == node->KeyValue.Key) 
	{
		node->KeyValue.Value = keyValue.Value;
	}
	// recurse left or right
	else 
	{
		if (keyValue.Key < node->KeyValue.Key)
		{
			node->leftNode = InsertRec(node->leftNode, keyValue);
		}
		else
		{
			node->rightNode = InsertRec(node->rightNode, keyValue);
		}
	}

	// fix right-leaning red node
	if (IsRed(node->rightNode) && (!IsRed(node->leftNode)))
	{
		node = RotateLeft(node);
	}

	// fix two reds in a row
	if (IsRed(node->leftNode) && IsRed(node->leftNode->leftNode))
	{
		node = RotateRight(node);
	}

	if (IsRed(node->leftNode) && IsRed(node->rightNode))
	{
		ColorFlip(node);
	}

	return node;
}

// free node
void LeftLeaningBlackTree::Free(Node* node)
{
	if (node != NULL) {
		if (node->leftNode != NULL)
		{
			Free(node->leftNode);
		}
		
		if (node->rightNode != NULL)
		{
			Free(node->rightNode);
		}

		delete node;
		node = NULL;
	}
}