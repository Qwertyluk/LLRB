#include <cstddef>

#include "LeftLeaningRedBlackTree.h"


// left rotation
template<class Key, class T>
typename LeftLeaningBlackTree<Key, T>::Node* LeftLeaningBlackTree<Key, T>::RotateLeft(Node* node)
{
	Node* temp = node->rightNode;
	node->rightNode = temp->leftNode;
	temp->leftNode = node;
	temp->color = node->color;
	node->color = RED;

	return temp;
}

// right rotation
template<class Key, class T>
typename LeftLeaningBlackTree<Key, T>::Node* LeftLeaningBlackTree<Key, T>::RotateRight(Node* node)
{
	Node* temp = node->leftNode;
	node->leftNode = temp->rightNode;
	temp->rightNode = node;
	temp->color = node->color;
	node->color = RED;

	return temp;
}

// color flip
template<class Key, class T>
void LeftLeaningBlackTree<Key, T>::ColorFlip(Node* node)
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
template<class Key, class T>
inline bool LeftLeaningBlackTree<Key, T>::IsRed(Node* node)
{
	return (node != NULL) && node->color;
}

template<class Key, class T>
typename LeftLeaningBlackTree<Key, T>::Node* LeftLeaningBlackTree<Key, T>::MoveRedLeft(Node* node)
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

template<class Key, class T>
typename LeftLeaningBlackTree<Key, T>::Node* LeftLeaningBlackTree<Key, T>::MoveRedRight(Node* node)
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
template<class Key, class T>
typename LeftLeaningBlackTree<Key, T>::Node* LeftLeaningBlackTree<Key, T>::FindMin(Node* node)
{
	while (node->leftNode != NULL) 
	{
		node = node->leftNode;
	}

	return node;
}

// repair rule violations
template<class Key, class T>
typename LeftLeaningBlackTree<Key, T>::Node* LeftLeaningBlackTree<Key,T>::FixUp(Node* node)
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
template<class Key, class T>
LeftLeaningBlackTree<Key, T>::LeftLeaningBlackTree<Key, T>() 
{
	this->root = NULL;
}

// destructor
template<class Key, class T>
LeftLeaningBlackTree<Key, T>::~LeftLeaningBlackTree<Key, T>() 
{
	this->Free(this->root);
}

// creation of a new node
template<class Key, class T>
typename LeftLeaningBlackTree<Key, T>::Node* LeftLeaningBlackTree<Key, T>::NewNode(KeyValue<Key, T> keyValue)
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
template<class Key, class T>
bool LeftLeaningBlackTree<Key, T>::Insert(KeyValue<Key, T> keyvalue)
{
	std::pair<Node*, bool> pair = this->InsertRec(this->root, keyvalue);
	this->root = pair.first;
	this->root->color = BLACK;

	return pair.second;
}

// recursive insertion
template<class Key, class T>
std::pair<typename LeftLeaningBlackTree<Key, T>::Node*, bool> LeftLeaningBlackTree<Key, T>::InsertRec(Node* node, KeyValue<Key, T> keyValue)
{
	// insert a leaf
	if (node == NULL)
	{
		node = this->NewNode(keyValue);
		return std::make_pair(node, true);
	}

	bool succeed = true;
	// check if value is already in the tree
	if (keyValue.Key == node->KeyValue.Key)
	{
		succeed = false;
	}
	// recurse left or right
	else
	{
		if (keyValue.Key < node->KeyValue.Key)
		{
			std::pair<Node*, bool> pair = InsertRec(node->leftNode, keyValue);
			node->leftNode = pair.first;
			succeed = pair.second;
		}
		else
		{
			std::pair<Node*, bool> pair = InsertRec(node->rightNode, keyValue);
			node->rightNode = pair.first;
			succeed = pair.second;
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

	return std::make_pair(node, succeed);
}

// free a node
template<class Key, class T>
void LeftLeaningBlackTree<Key, T>::Free(Node* node)
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
template<class Key, class T>
KeyValue<Key, T> LeftLeaningBlackTree<Key, T>::GetMin()
{
	Node* node = this->root;
	while (node->leftNode != NULL)
	{
		node = node->leftNode;
	}

	return node->KeyValue;
}

// find a tree minimum
template<class Key, class T>
KeyValue<Key, T>* LeftLeaningBlackTree<Key, T>::Find(Key key)
{
	Node* node = FindRec(this->root, key);
	if (node == NULL)
	{
		return NULL;
	}
	else
	{
		KeyValue<Key, T>* kv = new KeyValue<Key, T>();
		kv = &node->KeyValue;
		return kv;
	}
}

// find a tree minimum
template<class Key, class T>
typename LeftLeaningBlackTree<Key, T>::Node* LeftLeaningBlackTree<Key, T>::FindRec(Node* node, Key key)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (node->KeyValue.Key == key)
	{
		return node;
	}
	else if(node->KeyValue.Key < key)
	{
		return FindRec(node->rightNode, key);
	}
	else
	{
		return FindRec(node->leftNode, key);
	}
}

// delete a minimum
template<class Key, class T>
void LeftLeaningBlackTree<Key, T>::DeleteMin()
{
	this->root = DeleteMin(this->root);
	this->root->color = BLACK;
}

template<class Key, class T>
typename LeftLeaningBlackTree<Key, T>::Node* LeftLeaningBlackTree<Key, T>::DeleteMin(Node* node)
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
template<class Key, class T>
std::pair<typename LeftLeaningBlackTree<Key, T>::Node*, bool> LeftLeaningBlackTree<Key, T>::DeleteRec(Node* node, Key key)
{
	std::pair<Node*, bool> retPair;
	retPair.first = node;
	retPair.second = false;

	if (node->KeyValue.Key > key)
	{
		if (node->leftNode != NULL)
		{
			if (!IsRed(node->leftNode) && !IsRed(node->leftNode->leftNode))
			{
				node = MoveRedLeft(node);
			}
			
			std::pair<Node*, bool> pair = DeleteRec(node->leftNode, key);
			node->leftNode = pair.first;
			retPair.second = pair.second;
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
			return std::make_pair(nullptr, true);
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
				std::pair<Node*, bool> pair = DeleteRec(node->rightNode, key);
				node->rightNode = pair.first;
				retPair.second = pair.second;
			}
		}
	}

	Node* retNode = FixUp(node);
	retPair.first = retNode;
	return retPair;
}

// delete the node with the specified key
template<class Key, class T>
bool LeftLeaningBlackTree<Key, T>::Delete(Key key)
{
	if (this->root != NULL)
	{
		std::pair<Node*, bool> pair = DeleteRec(this->root, key);
		this->root = pair.first;

		if (this->root != NULL)
		{
			this->root->color = BLACK;
		}

		return pair.second;
	}

	return false;
}

template<class Key, class T>
void LeftLeaningBlackTree<Key, T>::Clear()
{
	this->Free(this->root);
	this->root = NULL;
}