#include "newMap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Map m;
	assert(m.insert("Fred", 2.956));
	assert(m.insert("Ethel", 3.538));
	assert(m.size() == 2);
	ValueType v = 42;
	assert(!m.get("Lucy", v) && v == 42);
	assert(m.get("Fred", v) && v == 2.956);
	v = 42;
	KeyType x = "Lucy";
	assert(m.get(0, x, v) &&
		((x == "Fred"  &&  v == 2.956) || (x == "Ethel"  &&  v == 3.538)));
	KeyType x2 = "Ricky";
	assert(m.get(1, x2, v) &&
		((x2 == "Fred"  &&  v == 2.956) || (x2 == "Ethel"  &&  v == 3.538)) &&
		x != x2);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}

/*void test()
{
	Map m;
	assert(m.insert("Fred", 2.956));
	assert(m.insert("Ethel", 3.538));
	assert(m.size() == 2);
	ValueType v = 42;
	assert(!m.get("Lucy", v) && v == 42);
	assert(m.get("Fred", v) && v == 2.956);
	v = 42;
	KeyType x = "Lucy";
	assert(m.get(0, x, v) &&
		((x == "Fred"  &&  v == 2.956) || (x == "Ethel"  &&  v == 3.538)));
	KeyType x2 = "Ricky";
	assert(m.get(1, x2, v) &&
		((x2 == "Fred"  &&  v == 2.956) || (x2 == "Ethel"  &&  v == 3.538)) &&
		x != x2);
}


int main()
{
	Map m;
	m.insert("A", 10);
	m.insert("B", 44);
	m.insert("C", 10);
	string all;
	double total = 0;
	for (int n = 0; n < m.size(); n++)
	{
		string k;
		double v;
		m.get(n, k, v);
		all += k;
		total += v;
	}
	cout << all << total;
	test();
	cout << "Passed all tests" << endl;


	Map gpas;
	gpas.insert("Fred", 2.956);
	gpas.insert("Ethel", 3.538);
	double j;
	string k1;
	assert(gpas.get(1, k1, j) && (k1 == "Fred" || k1 == "Ethel"));
	string k2;
	assert(gpas.get(1, k2, j) && k2 == k1);
}*/

/*
	Map a(1000);   // a can hold at most 1000 key/value pairs
	Map b(5);      // b can hold at most 5 key/value pairs
	Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
	KeyType k[6] = {"water", "soda", "milkshake", "boba", "tea", "coffee" };//a list of six distinct values of the appropriate type
	ValueType v = 12345; //a value of the appropriate type

	// No failures inserting pairs with 5 distinct keys into b
	for (int n = 0; n < 5; n++)
		assert(b.insert(k[n], v));

	// Failure if we try to insert a pair with a sixth distinct key into b
	assert(!b.insert(k[5], v));

	// When two Maps' contents are swapped, their capacities are swapped
	// as well:
	a.swap(b);
	assert(!a.insert(k[5], v) && b.insert(k[5], v));
}
*/
/*void test()
{
	Map m;
	assert(m.insert(10, "diez"));
	assert(m.insert(20, "veinte"));
	assert(m.size() == 2);
	ValueType v = "cuarenta y dos";
	assert(!m.get(30, v) && v == "cuarenta y dos");
	assert(m.get(10, v) && v == "diez");
	v = "cuarenta y dos";
	KeyType x = 30;
	assert(m.get(0, x, v) &&
		((x == 10 && v == "diez") || (x == 20 && v == "veinte")));
	KeyType x2 = 40;
	assert(m.get(1, x2, v) &&
		((x2 == 10 && v == "diez") || (x2 == 20 && v == "veinte")) &&
		x != x2);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}

}*/


