#pragma once

#include <utility>
#include <memory>
#include <stdexcept>

#include "Node.h"
#include "LeftLeaningRedBlackTree.h"
#include "Iterator.h"
#include "ConstantIterator.h"
#include "ReverseIterator.h"
#include "ReverseConstantIterator.h"

template<typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<Node<Key, T>>>
class LLRB_Map
{
	private:
		LeftLeaningBlackTree<Key, T, Compare, Alloc> LLRB;
		size_t length;
		T& GetValue(const Key& k)
		{
			Node<Key, T>* node = this->LLRB.Find(k); 
			if (node == this->LLRB.GetIteratorRoot())
			{
				throw std::out_of_range("llbr_map");
			}
			return node->getKeyValue().Value;
		}

	public:
		LLRB_Map()
		{

		}

		~LLRB_Map()
		{

		}


		// element access
		T& at(const Key& k)
		{
			return GetValue(k);
		}

		const T& at(const Key& k) const
		{
			return GetValue(k);
		}

		T& operator[] (const Key& k)
		{
			return GetValue(k);
		}

		
		// iterators
		Iterator<Key, T> begin()
		{
			return Iterator<Key, T>(this->LLRB.GetMin());
		}

		Iterator<Key, T> end()
		{
			return Iterator<Key, T>(this->LLRB.GetIteratorRoot());
		}

		ConstantIterator<Key, T> cbegin() const
		{
			return Iterator<Key, T>(this->LLRB.GetMin());
		}

		ConstantIterator<Key, T> cend() const
		{
			return Iterator<Key, T>(this->LLRB.GetIteratorRoot());
		}

		ReverseIterator<Key, T> rbegin()
		{
			return ReverseIterator<Key, T>(this->LLRB.GetMin());
		}

		ReverseIterator<Key, T> rend()
		{
			return ReverseIterator<Key, T>(this->LLRB.GetIteratorRoot());
		}

		ReverseConstantIterator<Key, T> crbegin() const
		{
			return ReverseConstantIterator<Key, T>(this->LLRB.GetMin());
		}

		ReverseConstantIterator<Key, T> crend() const
		{
			return Iterator<Key, T>(this->LLRB.GetIteratorRoot());
		}


		// capacity
		bool empty() const
		{
			return(this->length == 0 ? true : false);
		}
		
		size_t size() const
		{
			return this->length;
		}

		
		// modifiers
		std::pair<Iterator<Key, T>, bool> insert(const std::pair<const Key, T>& val)
		{
			KeyValue<Key, T> kv;
			kv.Key = val.first;
			kv.Value = val.second;

			std::pair<Iterator<Key, T>, bool> ret = this->LLRB.Insert(kv);

			if (ret.second)
			{
				this->length++;
			}

			return ret;
		}

		size_t erase(const Key& k)
		{
			bool ret = (size_t)this->LLRB.Delete(k);

			if (ret)
			{
				this->length--;
			}

			return ret;
		}
		
		void clear()
		{
			this->length = 0;
			this->LLRB.Clear();
		}

		
		// observers
		Compare key_compare() const
		{
			return this->LLRB.GetCompareObject();
		}


		// look up
		size_t count(const Key& k)
		{
			if (this->LLRB.Find(k) != this->LLRB.GetIteratorRoot())
			{
				return 1;
			}

			return 0;
		}

		Iterator<Key, T> find(const Key& k)
		{
			return Iterator<Key, T>(this->LLRB.Find(k));
		}

		Iterator<Key, T> upper_bound(const Key& k)
		{
			return Iterator<Key, T>(this->LLRB.FindUpperBound(k));
		}

		Iterator<Key, T> lower_bound(const Key& k)
		{
			return Iterator<Key, T>(this->LLRB.FindLowerBound(k));
		}
};