#pragma once

#include <utility>
#include <memory>
#include <stdexcept>

#include "Node.h"
#include "LeftLeaningRedBlackTree.h"
#include "Iterator.h"
#include "ConstantIterator.h"

template<typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<Node<Key, T>>>
class LLRB_Map
{
	private:
		LeftLeaningBlackTree<Key, T, Compare, Alloc> LLRB;
		size_t length;

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
			KeyValue<Key, T>* kv = this->LLRB.Find(k);
			if (kv == NULL)
			{
				throw std::out_of_range("llbr_map");
			}
			return kv->Value;
		}

		const T& at(const Key& k) const
		{
			KeyValue<Key, T>* kv = this->LLRB.Find(k);
			if (kv == NULL)
			{
				throw std::out_of_range("llbr_map");
			}
			return kv->Value;
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
		bool insert(const std::pair<const Key, T>& val)
		{
			KeyValue<Key, T> kv;
			kv.Key = val.first;
			kv.Value = val.second;

			bool ret = this->LLRB.Insert(kv);

			if (ret)
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

		
		// look up
		size_t count(const Key& k)
		{
			if (this->LLRB.Find(k) != NULL)
			{
				return 1;
			}

			return 0;
		}
};