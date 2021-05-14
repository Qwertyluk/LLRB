#pragma once
#pragma once

#include <iterator>

#include "Node.h"
#include "TreeTraversal.h"

template<class Key, class T>
class ReverseIterator
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
		this->ptr = treeTraversal.MoveBackward(this->ptr);
	}
	void MoveBackwards()
	{
		TreeTraversal<Key, T> treeTraversal;
		this->ptr = treeTraversal.MoveForward(this->ptr);
	}

public:
	ReverseIterator(pointer p) : ptr(p) {}
	reference operator*() const { return *ptr; }
	pointer operator->() { return ptr; }

	// Prefix increment
	ReverseIterator& operator++()
	{
		MoveForward();
		return *this;
	}
	// Postfix increment
	ReverseIterator operator++(int)
	{
		Iterator<Key, T> temp = *this;
		MoveForward();
		return temp;
	}
	// Prefix decrement
	ReverseIterator& operator--()
	{
		MoveBackwards();
		return *this;
	}
	// Postfix decrement
	ReverseIterator operator--(int)
	{
		Iterator<Key, T> temp = *this;
		MoveBackwards();
		return temp;
	}

	friend bool operator== (const ReverseIterator& a, const ReverseIterator& b) { return a.ptr == b.ptr; };
	friend bool operator!= (const ReverseIterator& a, const ReverseIterator& b) { return a.ptr != b.ptr; };
};