#pragma once

#include <utility>
#include <memory>

#include "KeyValuePair.h"
#include "Node.h"
#include "Colors.h"

template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<Node<Key, T>>>
class LeftLeaningBlackTree 
{
private:
	Node<Key, T> iteratorRoot;
	Node<Key, T>* root;
	Alloc allocator;
	Compare compare;

	std::pair<Node<Key, T>*, bool> InsertRec(Node<Key, T>* node, Node<Key, T>* parentNode, KeyValue<Key, T> keyValue)
	{
		// insert a leaf
		if (node == NULL)
		{
			node = this->NewNode(parentNode, keyValue);
			return std::make_pair(node, true);
		}

		bool succeed = true;
		// check if value is already in the tree
		if (keyValue.Key == node->getKeyValue().Key)
		{
			succeed = false;
		}
		// recurse left or right
		else
		{
			//if (keyValue.Key < node->getKeyValue().Key)
			if (this->compare(keyValue.Key, node->getKeyValue().Key))
			{
				std::pair<Node<Key, T>*, bool> pair = InsertRec(node->getLeftNode(), node, keyValue);
				node->setLeftNode(pair.first);
				succeed = pair.second;
			}
			else
			{
				std::pair<Node<Key, T>*, bool> pair = InsertRec(node->getRightNode(), node, keyValue);
				node->setRightNode(pair.first);
				succeed = pair.second;
			}
		}

		// fix right-leaning red node
		if (IsRed(node->getRightNode()) && (!IsRed(node->getLeftNode())))
		{
			node = RotateLeft(node);
		}

		// fix two reds in a row
		if (IsRed(node->getLeftNode()) && IsRed(node->getLeftNode()->getLeftNode()))
		{
			node = RotateRight(node);
		}

		if (IsRed(node->getLeftNode()) && IsRed(node->getRightNode()))
		{
			ColorFlip(node);
		}

		return std::make_pair(node, succeed);
	}
	Node<Key, T>* NewNode(Node<Key, T>* parentNode, KeyValue<Key, T> keyValue)
	{
		Node<Key, T>* newNode = this->allocator.allocate(1);
		this->allocator.construct(newNode);
		newNode->getKeyValue().Key = keyValue.Key;
		newNode->getKeyValue().Value = keyValue.Value;
		newNode->setColor(RED);
		newNode->setLeftNode(NULL);
		newNode->setRightNode(NULL);
		newNode->setParentNode(parentNode);

		return newNode;
	}
	Node<Key, T>* DeleteMin(Node<Key, T>* node)
	{
		if (node->getLeftNode() == NULL)
		{
			Free(node);
			return NULL;
		}

		if (!IsRed(node->getLeftNode()) && !IsRed(node->getLeftNode()->getLeftNode()))
		{
			node = MoveRedLeft(node);
		}

		node->setLeftNode(DeleteMin(node->getLeftNode()));

		return FixUp(node);
	}
	void Free(Node<Key, T>* node)
	{
		if (node != NULL) {
			if (node->getLeftNode() != NULL)
			{
				Free(node->getLeftNode());
			}

			if (node->getRightNode() != NULL)
			{
				Free(node->getRightNode());
			}

			if (node->getParentNode() == &this->iteratorRoot)
			{
				this->iteratorRoot.setLeftNode(NULL);
			}

			//delete node;
			this->allocator.destroy(node);
			this->allocator.deallocate(node, 1);
			node = NULL;
		}
	}
	std::pair<Node<Key, T>*, bool> DeleteRec(Node<Key, T>* node, Key key)
	{
		std::pair<Node<Key, T>*, bool> retPair;
		retPair.first = node;
		retPair.second = false;

		if (node->getKeyValue().Key > key)
		{
			if (node->getLeftNode() != NULL)
			{
				if (!IsRed(node->getLeftNode()) && !IsRed(node->getLeftNode()->getLeftNode()))
				{
					node = MoveRedLeft(node);
				}

				std::pair<Node<Key, T>*, bool> pair = DeleteRec(node->getLeftNode(), key);
				node->setLeftNode(pair.first);
				retPair.second = pair.second;
			}
		}
		else
		{
			if (IsRed(node->getLeftNode()))
			{
				node = RotateRight(node);
			}

			if (node->getKeyValue().Key == key && node->getRightNode() == NULL)
			{
				Free(node);
				return std::make_pair(nullptr, true);
			}

			if (node->getRightNode() != NULL)
			{
				if (!IsRed(node->getRightNode()) && !IsRed(node->getRightNode()->getLeftNode()))
				{
					node = MoveRedRight(node);
				}

				if (node->getKeyValue().Key == key)
				{
					node->setKeyValue(FindMin(node->getRightNode())->getKeyValue());
					node->setRightNode(DeleteMin(node->getRightNode()));
				}
				else
				{
					std::pair<Node<Key, T>*, bool> pair = DeleteRec(node->getRightNode(), key);
					node->setRightNode(pair.first);
					retPair.second = pair.second;
				}
			}
		}

		Node<Key, T>* retNode = FixUp(node);
		retPair.first = retNode;
		return retPair;
	}
	Node<Key, T>* RotateLeft(Node<Key, T>* node)
	{
		Node<Key, T>* temp = node->getRightNode();
		//added:
		temp->setParentNode(node->getParentNode());
		if (temp->getLeftNode() != NULL)
		{
			temp->getLeftNode()->setParentNode(node);
		}
		//
		node->setRightNode(temp->getLeftNode());
		temp->setLeftNode(node);
		temp->setColor(node->getColor());
		node->setColor(RED);

		return temp;
	}
	Node<Key, T>* RotateRight(Node<Key, T>* node)
	{
		Node<Key, T>* temp = node->getLeftNode();
		// added:
		temp->setParentNode(node->getParentNode());
		if (temp->getRightNode() != NULL)
		{
			temp->getRightNode()->setParentNode(node);
		}

		//
		node->setLeftNode(temp->getRightNode());
		temp->setRightNode(node);
		temp->setColor(node->getColor());
		node->setColor(RED);

		return temp;
	}
	void ColorFlip(Node<Key, T>* node)
	{
		node->setColor(!node->getColor());

		if (node->getLeftNode() != NULL) {
			node->getLeftNode()->setColor(!node->getLeftNode()->getColor());
		}

		if (node->getRightNode() != NULL) {
			node->getRightNode()->setColor(!node->getRightNode()->getColor());
		}
	}
	inline bool IsRed(Node<Key, T>* node)
	{
		return (node != NULL) && node->getColor();
	}
	Node<Key, T>* MoveRedLeft(Node<Key, T>* node)
	{
		ColorFlip(node);

		if (node->getRightNode() != NULL && IsRed(node->getRightNode()->getLeftNode()))
		{
			node->setRightNode(RotateRight(node->getRightNode()));
			node = RotateLeft(node);
			ColorFlip(node);
		}

		return node;
	}
	Node<Key, T>* MoveRedRight(Node<Key, T>* node)
	{
		ColorFlip(node);

		if (node->getLeftNode() != NULL && IsRed(node->getLeftNode()->getLeftNode()))
		{
			node = RotateRight(node);
			ColorFlip(node);
		}

		return node;
	}
	Node<Key, T>* FindMin(Node<Key, T>* node)
	{
		while (node->getLeftNode() != NULL)
		{
			node = node->getLeftNode();
		}

		return node;
	}
	Node<Key, T>* FixUp(Node<Key, T>* node)
	{
		if (IsRed(node->getRightNode()))
		{
			node = RotateLeft(node);
		}

		if (IsRed(node->getLeftNode()) && IsRed(node->getLeftNode()->getLeftNode()))
		{
			node = RotateRight(node);
		}

		if (IsRed(node->getLeftNode()) && IsRed(node->getRightNode()))
		{
			ColorFlip(node);
		}

		return node;
	}
	Node<Key, T>* FindRec(Node<Key, T>* node, Key key)
	{
		if (node == NULL)
		{
			return NULL;
		}

		if (node->getKeyValue().Key == key)
		{
			return node;
		}
		//else if(node->getKeyValue().Key < key)
		else if (this->compare(node->getKeyValue().Key, key))
		{
			return FindRec(node->getRightNode(), key);
		}
		else
		{
			return FindRec(node->getLeftNode(), key);
		}
	}

public:
	LeftLeaningBlackTree()
	{
		this->iteratorRoot.setLeftNode(this->root);
		this->root = NULL;
	}
	~LeftLeaningBlackTree()
	{
		this->Free(this->root);
	}

	bool Insert(KeyValue<Key, T> keyValue)
	{
		std::pair<Node<Key, T>*, bool> pair = this->InsertRec(this->root, NULL, keyValue);
		this->root = pair.first;
		this->root->setColor(BLACK);
		this->iteratorRoot.setLeftNode(this->root);

		return pair.second;
	}
	Node<Key, T>* GetMin()
	{
		if (this->root == NULL)
		{
			return NULL;
		}

		Node<Key, T>* node = this->root;
		while (node->getLeftNode() != NULL)
		{
			node = node->getLeftNode();
		}

		return node;
	}
	KeyValue<Key, T>* Find(Key key)
	{
		Node<Key, T>* node = FindRec(this->root, key);
		if (node == NULL)
		{
			return NULL;
		}
		else
		{
			KeyValue<Key, T>* kv = new KeyValue<Key, T>();
			kv = &node->getKeyValue();
			return kv;
		}
	}
	void DeleteMin()
	{
		if (this->root != NULL)
		{
			this->root = DeleteMin(this->root);
			this->root->color = BLACK;
		}
	}
	bool Delete(Key key)
	{
		if (this->root != NULL)
		{
			std::pair<Node<Key, T>*, bool> pair = DeleteRec(this->root, key);
			this->root = pair.first;

			if (this->root != NULL)
			{
				this->root->setColor(BLACK);
			}

			return pair.second;
		}

		return false;
	}
	void Clear()
	{
		this->Free(this->root);
		this->root = NULL;
	}
	Node<Key, T>* GetIteratorRoot()
	{
		return &this->iteratorRoot;
	}
};