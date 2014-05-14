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
void multimap_visit_all(std::multimap<TKey, TKeyVal>& tMap, std::function<eError(TKey, TKeyVal)> func)
{
	typedef std::multimap<TKey, TKeyVal> TMap;

	for (TMap::iterator it = tMap.begin(); it != tMap.end(); it++)
	{
		func(it->first,it->second);
	}
}

template< typename TKey, typename TKeyVal >
eError multimap_visit_all(std::multimap<TKey, TKeyVal>& tMap, TKey key, std::function<eError(TKeyVal)> func)
{
	eError err = eError::NoErr;

	typedef std::multimap<TKey, TKeyVal> TMap;

	std::pair<TMap::iterator, TMap::iterator> iterPair = tMap.equal_range(key);

	for (TMap::iterator it = iterPair.first; it != iterPair.second; ++it)
	{
		err |= func(it->second);
	}

	return err;
		
}

template< typename TKey, typename TKeyVal >
void multimap_visit_all(std::multimap<TKey, TKeyVal>& tMap, int val, std::function<eError(TKey, TKeyVal)> func)
{
	typedef std::multimap<TKey, TKeyVal> TMap;

	// Must be a better way to do this
	for (TMap::iterator it = tMap.begin(); it != tMap.end(); it++)
	{
		if (it->second == val)
		{
			func(it->first, it->second);
		}
	}
}
