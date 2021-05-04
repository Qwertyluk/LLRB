#pragma once

#include <utility>

#include "LeftLeaningRedBlackTree.h"
#include "LeftLeaningRedBlackTree.cpp"

template<class Key, class T>
class LLRB_Map
{
	private:
		LeftLeaningBlackTree<Key, T> LLRB;
		size_t length;

	public:
		LLRB_Map();
		~LLRB_Map();

		bool empty() const;
		size_t size() const;
		bool insert(const std::pair<const Key, T>& val);
		T& at(const Key& k);
		const T& at(const Key& k) const;
		size_t erase(const Key& k);
		void clear();
		size_t count(const Key& k);
};