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

static Node* MoveRedLeft(Node* node) 
{
	ColorFlip(node);

	if (node->rightNode != NULL && IsRed(node->rightNode->leftNode))
	{
		node->rightNode = RotateRight(node->rightNode);
		node = RotateLeft(node);
		ColorFlip(node);
	}

	return node;
}

static Node* MoveRedRight(Node* node)
{
	ColorFlip(node);
	
	if (node->leftNode != NULL && IsRed(node->leftNode->leftNode))
	{
		node = RotateRight(node);
		ColorFlip(node);
	}

	return node;
}

// find minimum from specified node
static Node* FindMin(Node* node)
{
	while (node->leftNode != NULL) 
	{
		node = node->leftNode;
	}

	return node;
}

// repair rule violations
static Node* FixUp(Node* node)
{
	if (IsRed(node->rightNode))
	{
		node = RotateLeft(node);
	}

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

// find a tree minimum
KeyValue LeftLeaningBlackTree::GetMin()
{
	Node* node = this->root;
	while (node->leftNode != NULL)
	{
		node = node->leftNode;
	}

	return node->KeyValue;
}

// delete a minimum
void LeftLeaningBlackTree::DeleteMin()
{
	this->root = DeleteMin(this->root);
	this->root->color = BLACK;
}

Node* LeftLeaningBlackTree::DeleteMin(Node* node)
{
	if (node->leftNode == NULL)
	{
		Free(node);
		return NULL;
	}

	if (!IsRed(node->leftNode) && !IsRed(node->leftNode->leftNode))
	{
		node = MoveRedLeft(node);
	}

	node->leftNode = DeleteMin(node->leftNode);

	return FixUp(node);
}

// recursive deletion
Node* LeftLeaningBlackTree::DeleteRec(Node* node, unsigned int key)
{
	if (node->KeyValue.Key > key)
	{
		if (node->leftNode != NULL)
		{
			if (!IsRed(node->leftNode) && !IsRed(node->leftNode->leftNode))
			{
				node = MoveRedLeft(node);
			}
			
			node->leftNode = DeleteRec(node->leftNode, key);
		}
	}
	else 
	{
		if (IsRed(node->leftNode))
		{
			node = RotateRight(node);
		}

		if (node->KeyValue.Key == key && node->rightNode == NULL)
		{
			Free(node);
			return NULL;
		}

		if (node->rightNode != NULL)
		{
			if (!IsRed(node->rightNode) && !IsRed(node->rightNode->leftNode))
			{
				node = MoveRedRight(node);
			}

			if (node->KeyValue.Key == key)
			{
				node->KeyValue = FindMin(node->rightNode)->KeyValue;
				node->rightNode = DeleteMin(node->rightNode);
			}
			else
			{
				node->rightNode = DeleteRec(node->rightNode, key);
			}
		}
	}

	return FixUp(node);
}

// delete the node with the specified key
void LeftLeaningBlackTree::Delete(unsigned int key)
{
	if (this->root != NULL)
	{
		this->root = DeleteRec(this->root, key);

		if (this->root != NULL)
		{
			this->root->color = BLACK;
		}
	}
}