#pragma once

#include "KeyValuePair.h"
#include "Colors.h"

template<class Key, class T>
class Node
{
private:
	KeyValue<Key, T> keyValue;
	bool color;
	Node* leftNode;
	Node* rightNode;
	Node* parentNode;

public:
	Node()
	{
		this->color = RED;
		this->leftNode = NULL;
		this->rightNode = NULL;
		this->parentNode = NULL;
	}
	~Node()
	{

	}
	bool getColor()
	{
		return this->color;
	}
	void setColor(bool col)
	{
		this->color = col;
	}
	Node* getLeftNode()
	{
		return this->leftNode;
	}
	void setLeftNode(Node* node)
	{
		this->leftNode = node;
		if (node != NULL)
		{
			node->setParentNode(this);
		}
	}
	Node* getRightNode()
	{
		return this->rightNode;
	}
	void setRightNode(Node* node)
	{
		this->rightNode = node;
		if (node != NULL)
		{
			node->setParentNode(this);
		}
	}
	KeyValue<Key, T>& getKeyValue()
	{
		return this->keyValue;
	}
	void setKeyValue(KeyValue<Key, T> kv)
	{
		this->keyValue = kv;
	}
	Node* getParentNode()
	{
		return this->parentNode;
	}
	void setParentNode(Node* node)
	{
		this->parentNode = node;
	}
};