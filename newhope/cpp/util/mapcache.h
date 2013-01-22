#ifndef UTIL_MAPCACHE_H
#define UTIL_MAPCACHE_H

#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "util/logger.h"

template <typename K, typename V>
class mapcache {
public:
	mapcache(unsigned int size, V(*fctfault)(void*,K), void* obj)
		: size(size), fctfault(fctfault), obj(obj) { }

	inline V operator[](K key)
	{
		try
		{
			return cmap.at(key);
		}
		catch(out_of_range& e)
		{
			V value = fctfault(obj, key);
			cmap[key] = value;
			if(find(deq.begin(), deq.end(), key) == deq.end())
				deq.push_back(key);
			if(cmap.size() > size)
			{
				for(typename vector<K>::iterator it=deq.begin(); 
						it != deq.begin() + (size*0.5); 
						it++)
				{
					cmap.erase(*it);
					it = deq.erase(it);
				}
			}
			if(cmap.size() != deq.size())
				abort();
			return value;
		}
	}

private:
	map<K,V> cmap;
	vector<K> deq;
	const unsigned int size;
	V(*fctfault)(void*,K);
	void* obj;
};

#endif
