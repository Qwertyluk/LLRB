#pragma once

#pragma once

#include <iterator>

#include "Node.h"
#include "TreeTraversal.h"

template<class Key, class T>
class ReverseConstantIterator
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
	ReverseConstantIterator(pointer p) : ptr(p) {}
	const reference operator*() const { return *ptr; }
	pointer operator->() { return ptr; }

	// Prefix increment
	ReverseConstantIterator& operator++()
	{
		MoveForward();
		return *this;
	}
	// Postfix increment
	ReverseConstantIterator operator++(int)
	{
		ConstantIterator<Key, T> temp = *this;
		MoveForward();
		return temp;
	}
	// Prefix decrement
	ReverseConstantIterator& operator--()
	{
		MoveBackwards();
		return *this;
	}
	// Postfix decrement
	ReverseConstantIterator operator--(int)
	{
		ConstantIterator<Key, T> temp = *this;
		MoveBackwards();
		return temp;
	}

	friend bool operator== (const ReverseConstantIterator& a, const ReverseConstantIterator& b) { return a.ptr == b.ptr; };
	friend bool operator!= (const ReverseConstantIterator& a, const ReverseConstantIterator& b) { return a.ptr != b.ptr; };
};