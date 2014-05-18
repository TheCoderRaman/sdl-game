//! \file map_helpers.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! various helpers for stl map and multimap containers
//!

#include "types.h" // For eError

#include <map>			// For the multimap and map
#include <functional>	// For std::function used in visit functions

//========================================================
//! \brief remove one element of key type from a multimap
template< typename TKey, typename TKeyVal >
void multimap_remove_one(std::multimap<TKey, TKeyVal>& tMap, const TKey key)
{
	// Find the value
	typename std::multimap<TKey, TKeyVal>::iterator it = tMap.find(key);

	// Remove it
	if (it != tMap.end())
		tMap.erase(it);
}

//========================================================
//! \brief remove ALL elements of key type from a multimap
template< typename TKey, typename TKeyVal >
void multimap_remove_all(std::multimap<TKey, TKeyVal>& tMap, const TKey key)
{
	// Erase all values associated with the key
	tMap.erase(key);
}

//========================================================
//! \brief remove a single exact pair match key and val from a multimap
template< typename TKey, typename TKeyVal >
void multimap_remove_pair(std::multimap<TKey, TKeyVal>& tMap, const TKey key, const TKeyVal val)
{
	typedef std::multimap<TKey, TKeyVal> TMap;

	// Grab the range of keys matching the same key value
	std::pair<typename TMap::iterator,typename TMap::iterator> iterPair = tMap.equal_range(key);

	// Iterate through all these key pairs and erase them
	for (typename TMap::iterator it = iterPair.first; it != iterPair.second; ++it)
	{
		if (it->second == val)
		{
			tMap.erase(it);
			break;
		}
	}
}

//========================================================
//! \brief remoce a pair method, reversed
template< typename TKey, typename TKeyVal >
void multimap_remove_pair(std::multimap<TKey, TKeyVal>& tMap, const TKeyVal val, const TKey key)
{
	// Call the other remove method
	multimap_remove_pair(tMap, key, val);
}

//========================================================
//! \brief visit every pair in the whole multimap
template< typename TKey, typename TKeyVal >
void multimap_visit_all(std::multimap<TKey, TKeyVal>& tMap, std::function<eError(TKey, TKeyVal)> func)
{
	typedef std::multimap<TKey, TKeyVal> TMap;

	// for every item in the map call the function that takes each part
	for (typename TMap::iterator it = tMap.begin(); it != tMap.end(); it++)
	{
		func(it->first,it->second);
	}
}

//========================================================
//! \brief visit all elements of a key type is a multimap
template< typename TKey, typename TKeyVal >
eError multimap_visit_all(std::multimap<TKey, TKeyVal>& tMap, TKey key, std::function<eError(TKeyVal)> func)
{
	eError err = eError::NoErr;

	typedef std::multimap<TKey, TKeyVal> TMap;

	// grab the first and last item in the map matching the key
	std::pair<typename TMap::iterator, typename TMap::iterator> iterPair = tMap.equal_range(key);

	// Iterate over all these pairs and call the function
	for (typename TMap::iterator it = iterPair.first; it != iterPair.second; ++it)
	{
		err |= func(it->second);
	}

	return err;
		
}

//========================================================
//! \brief visit all keys matching a value in a multimap (slow)
template< typename TKey, typename TKeyVal >
void multimap_visit_all_slow(std::multimap<TKey, TKeyVal>& tMap, int val, std::function<eError(TKey)> func)
{
	typedef std::multimap<TKey, TKeyVal> TMap;

	// For all the items in the whole map
	for (typename TMap::iterator it = tMap.begin(); it != tMap.end(); it++)
	{
		// if the value type matches, call the function
		if (it->second == val)
		{
			func(it->first);
		}
	}
}
