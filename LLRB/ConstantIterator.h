#pragma once

#include <iterator>

#include "Node.h"

template<class Key, class T>
class ConstantIterator
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
	ConstantIterator(pointer p) : ptr(p) {}
	const reference operator*() const { return *ptr; }
	pointer operator->() { return ptr; }

	// Prefix increment
	ConstantIterator& operator++()
	{
		MoveForward();
		return *this;
	}
	// Postfix increment
	ConstantIterator operator++(int)
	{
		ConstantIterator<Key, T> temp = *this;
		MoveForward();
		return temp;
	}
	// Prefix decrement
	ConstantIterator& operator--()
	{
		MoveBackwards();
		return *this;
	}
	// Postfix decrement
	ConstantIterator operator--(int)
	{
		ConstantIterator<Key, T> temp = *this;
		MoveBackwards();
		return temp;
	}

	friend bool operator== (const ConstantIterator& a, const ConstantIterator& b) { return a.ptr == b.ptr; };
	friend bool operator!= (const ConstantIterator& a, const ConstantIterator& b) { return a.ptr != b.ptr; };
};