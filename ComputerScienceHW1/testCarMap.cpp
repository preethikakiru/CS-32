#include "CarMap.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std; 

int main()
{
	CarMap m; 
	assert(m.fleetSize() == 0); 
	assert(m.addCar("bomb"));
	assert(m.addCar("cool"));
	assert(m.fleetSize() == 2);
	assert(!m.addCar("bomb"));
	assert(m.fleetSize() == 2);
	assert(m.addGas("cool", 25));
	assert(m.gas("cool") == 25);
	assert(m.useGas("cool", 10));
	assert(m.gas("cool") == 15);
	m.print();
}
