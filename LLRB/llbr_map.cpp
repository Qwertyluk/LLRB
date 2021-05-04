#include <cstddef>
#include <stdexcept>

#include "llbr_map.h"

template<class Key, class T>
LLRB_Map<Key, T>::LLRB_Map()
{

}

template<class Key, class T>
LLRB_Map<Key, T>::~LLRB_Map()
{

}

template<class Key, class T>
bool LLRB_Map<Key, T>::empty() const
{
	return(this->length == 0 ? true : false);
}

template<class Key, class T>
size_t LLRB_Map<Key, T>::size() const
{
	return this->length;
}

template<class Key, class T>
bool LLRB_Map<Key, T>::insert(const std::pair<const Key, T>& val)
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

template<class Key, class T>
T& LLRB_Map<Key, T>::at(const Key& k)
{
	KeyValue<Key, T> *kv = this->LLRB.Find(k);
	if (kv == NULL)
	{
		throw std::out_of_range("llbr_map");
	}
	return kv->Value;
}

template<class Key, class T>
const T& LLRB_Map<Key, T>::at(const Key& k) const
{
	KeyValue<Key, T>* kv = this->LLRB.Find(k);
	if (kv == NULL)
	{
		throw std::out_of_range("llbr_map");
	}
	return kv->Value;
}

template<class Key, class T>
size_t LLRB_Map<Key, T>::erase(const Key& k)
{
	bool ret = (size_t)this->LLRB.Delete(k);

	if (ret)
	{
		this->length--;
	}
	
	return ret;
}

template<class Key, class T>
void LLRB_Map<Key, T>::clear()
{
	this->length = 0;
	this->LLRB.Clear();
}

template<class Key, class T>
size_t LLRB_Map<Key, T>::count(const Key& k)
{
	if (this->LLRB.Find(k) != NULL)
	{
		return 1;
	}

	return 0;
}

