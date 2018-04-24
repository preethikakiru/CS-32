#include "Map.h"
#include <iostream>
using namespace std; 

Map::Map()
{
	map_size = 0;
}

bool Map::empty() const
{
	if (map_size == 0)
	{
		return true;
	}
	return false;
}

int Map::size() const   
{
	return map_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (contains(key))
	{
		return false;
	}
	if (map_size == DEFAULT_MAX_ITEMS)
	{
		return false;
	}
	m_point[map_size].m_x = key;
	m_point[map_size].m_y = value;
	map_size++;
	return true; 
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < map_size; i++)
	{
		if (m_point[i].m_x == key)
		{
			m_point[i].m_y = value;
			return true; 
		}
	}
	return false; 
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (update(key, value))
	{
		return true; 
	}
	if (insert(key, value))
	{
		return true; 
	}
	return false; 
}

bool Map::erase(const KeyType& key)
{
	int temp = map_size; 
	for (int i = 0; i < map_size; i++)
	{
		if (m_point[i].m_x == key)
		{
			for (int z = 0; z < temp - 1; z++)
			{
				m_point[z] = m_point[z + 1];
			}
			map_size--; 
			return true; 
		}
	}
	return false; 
}

bool Map::contains(const KeyType& key) const
{
	for (int i = 0; i < map_size; i++)
	{
		if (m_point[i].m_x == key)
		{
			return true;
		}
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	for (int i = 0; i < map_size; i++)
	{
		if (m_point[i].m_x == key)
		{
			value = m_point[i].m_y;
			return true; 
		}
	}
	return false; 
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (0 <= i && i < map_size)
	{
		key = m_point[i].m_x;
		value = m_point[i].m_y;
		return true; 
	}
	return false; 
}

void Map::swap(Map& other)
{
	int copySize = 0; 
	if (map_size <= other.map_size)
	{
		copySize = map_size;
	}
	else
	{
		copySize = other.map_size;
	}
	for (int j = 0; j < copySize; j++)
	{
		MapPoints tempElement = m_point[j]; 
		m_point[j] = other.m_point[j];
		other.m_point[j] = tempElement; 
	}

	//what if there is more left to copy from other into map or vice versa???????
	//then what!!!!!
	//look at lecture notes
	if (map_size > copySize)
	{
		for (int a = copySize; a < map_size; a++)
		{
			other.m_point[a] = m_point[a];
		}
	}
	else if (other.map_size > copySize)
	{
		for (int b = copySize; b < other.map_size; b++)
		{
			m_point[b] = other.m_point[b];
		}
	}

	int tempSize = map_size;
	map_size = other.map_size;
	other.map_size = tempSize;
}