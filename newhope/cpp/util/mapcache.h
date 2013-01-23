#ifndef UTIL_MAPCACHE_H
#define UTIL_MAPCACHE_H

#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "util/defines.h"
#include "util/logger.h"

template <typename K, typename V>
class mapcache {
public:
	mapcache(unsigned int size, V(*fctfault)(void*,K), void* obj)
		: size(size), fctfault(fctfault), obj(obj) { }

	~mapcache() { 
		cmap.clear();
		deq.clear();
	}

	inline V operator[](K key) {
		try {
			return cmap.at(key);
		}
		catch(std::out_of_range& e) {
			V value(fctfault(obj, key));
			cmap[key] = value;
			deq.push_back(key);
			if(cmap.size() > size) {
				for(auto it(deq.begin()); 
						it != deq.begin() + (size*0.1); 
						it++) {
					cmap.erase(*it);
				}
				deq.erase(deq.begin(), deq.begin()+(size*0.1));
			}
			if(cmap.size() != deq.size()) {
				abort();
			}
			return value;
		}
	}

private:
	std::map<K,V> cmap;
	std::vector<K> deq;
	const unsigned int size;
	V(*fctfault)(void*,K);
	void* obj;

	DISALLOW_COPY_AND_ASSIGN(mapcache);
};

#endif
