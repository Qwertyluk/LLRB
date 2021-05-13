#pragma once

#include <iterator>

#include "Node.h"
#include "TreeTraversal.h"

template<class Key, class T>
class Iterator
{
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = Node<Key, T>;
	using pointer = Node<Key, T>*;
	using reference = Node<Key, T>&;

	private:
		pointer ptr;
		void MoveForward()
		{
			TreeTraversal<Key, T> treeTraversal;
			this->ptr = treeTraversal.MoveForward(this->ptr);
		}
		void MoveBackwards()
		{
			TreeTraversal<Key, T> treeTraversal;
			this->ptr = treeTraversal.MoveBackward(this->ptr);
		}

	public:
		Iterator(pointer p) : ptr(p){}
		reference operator*() const { return *ptr; }
		pointer operator->() { return ptr; }

		// Prefix increment
		Iterator& operator++()
		{
			MoveForward();
			return *this;
		}
		// Postfix increment
		Iterator operator++(int)
		{
			Iterator<Key, T> temp = *this;
			MoveForward();
			return temp;
		}
		// Prefix decrement
		Iterator& operator--()
		{
			MoveBackwards();
			return *this;
		}
		// Postfix decrement
		Iterator operator--(int)
		{
			Iterator<Key, T> temp = *this;
			MoveBackwards();
			return temp;
		}

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };
};