#include <iostream>
#include "newMap.h"
using namespace std; 

Map::Map()
{
	map_size = 0;
	map_maxsize = DEFAULT_MAX_ITEMS; 
	m_point = new MapPoints[map_maxsize]; 
}

Map::Map(int size)
{
	if (size < 0)
	{
		cout << "Map size has to be greater than or equal to zero." << endl;
		exit(1); 
	}
	map_size = 0; 
	map_maxsize = size; 
	m_point = new MapPoints[map_maxsize]; 
}

Map::~Map()
{
	delete[] m_point; 
}

Map::Map(const Map &org)
{
	map_size = org.map_size;
	map_maxsize = org.map_maxsize;
	m_point = new MapPoints[map_maxsize];
	for (int i = 0; i < map_maxsize; i++)
	{
		m_point[i] = org.m_point[i];
	}
}

Map& Map::operator=(const Map &org)
{
	if (&org == this)
	{
		return *this; 
	}
	delete m_point; 
	map_size = org.map_size; 
	map_maxsize = org.map_maxsize; 
	m_point = new MapPoints[map_maxsize];
	for (int i = 0; i < map_maxsize; i++)
	{
		m_point[i] = org.m_point[i];
	}
	return *this; 
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
	if (map_size == map_maxsize)
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

	int tempSize = map_size;
	map_size = other.map_size;
	other.map_size = tempSize; 

	MapPoints *tempMap = m_point; 
	m_point = other.m_point; 
	other.m_point = tempMap; 

	int tempMax = map_maxsize;
	map_maxsize = other.map_maxsize;
	other.map_maxsize = tempMax;

}