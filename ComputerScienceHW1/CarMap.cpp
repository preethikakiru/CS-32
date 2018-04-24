#include "Map.h"
#include "CarMap.h"
#include <iostream>
using namespace std; 

CarMap::CarMap()
{
	Map m_Map; 
}

bool CarMap::addCar(KeyType license)
{
	if (m_Map.contains(license))
		return false; 
	if (m_Map.size() > DEFAULT_MAX_ITEMS)
		return false; 
	return m_Map.insert(license, 0); 
}

ValueType CarMap::gas(KeyType license) const
{
	ValueType g; 
	if (m_Map.get(license, g))
	{
		return g;
	}
	return -1; 
}

bool CarMap::addGas(KeyType license, ValueType gallons)
{
	if (!m_Map.contains(license))
	{
		return false; 
	}
	if (gas(license) < 0)
	{
		return false;
	}
	return m_Map.update(license, gas(license) + gallons); 
}

bool CarMap::useGas(KeyType license, ValueType gallons)
{
	if (!m_Map.contains(license))
		return false; 
	if (gallons > gas(license))
		return false; 
	return m_Map.update(license, gas(license) - gallons);
}
	
int CarMap::fleetSize() const
{
	return m_Map.size(); 
}

void CarMap::print() const
{
	KeyType license;
	ValueType numGall;
	for (int i = 0; i < fleetSize(); i++)
	{
		m_Map.get(i, license, numGall);
		cout << license << " " << numGall << endl;
	}
}
 