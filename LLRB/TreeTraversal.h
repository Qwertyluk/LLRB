#pragma once

#include "Node.h"

template<class Key, class T>
class TreeTraversal 
{
	public:
		Node<Key, T>* MoveForward(Node<Key, T>* node)
		{
			// if has a right child
			if (node->getRightNode() != NULL)
			{
				node = node->getRightNode();
				while (node->getLeftNode() != NULL)
				{
					node = node->getLeftNode();
				}
			}
			// if the node is the left node of its parent
			else if (node->getParentNode() != NULL && node == node->getParentNode()->getLeftNode())
			{
				node = node->getParentNode();
			}
			// the node is the furthest right in its subtree
			else
			{
				while (node->getParentNode() != NULL && node == node->getParentNode()->getRightNode())
				{
					node = node->getParentNode();
				}
				node = node->getParentNode();
			}

			return node;
		}

		Node<Key, T>* MoveBackward(Node<Key, T>* node)
		{
			// if has a left node
			if (node->getLeftNode() != NULL)
			{
				node = node->getLeftNode();
				while (node->getRightNode() != NULL)
				{
					node = node->getRightNode();
				}
			}
			else if (node->getParentNode() != NULL && node == node->getParentNode()->getRightNode())
			{
				node = node->getParentNode();
			}
			else {
				while (node->getParentNode() != NULL && node == node->getParentNode()->getLeftNode())
				{
					node = node->getParentNode();
				}
				node = node->getParentNode();
			}
		}
};