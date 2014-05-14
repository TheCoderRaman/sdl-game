//! \file map_helpers.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! various helpers for stl map and multimap containers
//!

#include <map>
#include <functional>


template< typename TKey, typename TKeyVal >
void multimap_remove_one(std::multimap<TKey, TKeyVal>& tMap, const TKey key)
{
	// Find the value
	typename tMap::iterator it = tMap.find(key);

	// Remove it
	if (it != tMap.end())
		tMap.erase(it);
}

template< typename TKey, typename TKeyVal >
void multimap_remove_all(std::multimap<TKey, TKeyVal>& tMap, const TKey key)
{
	// Erase all values associated with the key
	tMap.erase(key);
}

template< typename TKey, typename TKeyVal >
void multimap_remove_pair(std::multimap<TKey, TKeyVal>& tMap, const TKey key, const TKeyVal val)
{
	typedef std::multimap<TKey, TKeyVal> TMap;

	std::pair<TMap::iterator, TMap::iterator> iterPair = tMap.equal_range(key);

	for (TMap::iterator it = iterPair.first; it != iterPair.second; ++it)
	{
		if (it->second == val)
		{
			tMap.erase(it);
			break;
		}
	}
}

template< typename TKey, typename TKeyVal >
void multimap_remove_pair(std::multimap<TKey, TKeyVal>& tMap, const TKeyVal val, const TKey key)
{
	// Call the other remove method
	multimap_remove_pair(tMap, key, val);
}



template< typename TKey, typename TKeyVal >
void multimap_visit_all(std::multimap<TKey, TKeyVal>& tMap, std::function<void(TKey, TKeyVal)> func)
{
	for (std::multimap<TKey, TKeyVal>::iterator it = tMap.begin(); it != tMap.end(); it++)
	{

	}
}

template< typename TKey, typename TKeyVal >
void multimap_visit_all(std::multimap<TKey, TKeyVal>& tMap, TKey key)
{
	typedef std::multimap<TKey, TKeyVal> TMap;

	std::pair<TMap::iterator, TMap::iterator> iterPair = tMap.equal_range(key);

	for (TMap::iterator it = iterPair.first; it != iterPair.second; ++it)
	{

	}
		
}

template< typename TKey, typename TKeyVal >
void multimap_visit_all(std::multimap<TKey, TKeyVal>& tMap, int val)
{
	typedef std::multimap<TKey, TKeyVal> TMap;

	// Must be a better way to do this
	for (TMap::iterator it = tMap.begin(); it != tMap.end(); it++)
	{
		if (it->second == val)
		{

		}
	}
}
