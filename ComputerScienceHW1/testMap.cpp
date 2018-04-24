#include "Map.h"
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

/*int main()
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
}*/

/*
void test()
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
*/
/*#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Map m;  // maps strings to doubles
	assert(m.empty());
	ValueType v = -1234.5;
	assert(!m.get("abc", v) && v == -1234.5); // v unchanged by get failure
	m.insert("xyz", 9876.5);
	assert(m.size() == 1);
	KeyType k = "hello";
	assert(m.get(0, k, v) && k == "xyz"  &&  v == 9876.5);
	cout << "Passed all tests" << endl;

	Map m1;
	m1.insert("A", 10);
	m1.insert("B", 44);
	m1.insert("C", 10);
	string all;
	double total = 0;
	for (int n = 0; n < m1.size(); n++)
	{
		string k;
		double v;
		m1.get(n, k, v);
		all += k;
		total += v;
	}
	cout << all << total;

	Map gpas;
	gpas.insert("Fred", 2.956);
	gpas.insert("Ethel", 3.538);
	double j;
	string k1;
	assert(gpas.get(1, k1, j) && (k1 == "Fred" || k1 == "Ethel"));
	string k2;
	assert(gpas.get(1, k2, j) && k2 == k1);

}*/

	/*Map gpas2;
	gpas2.insert("Fred", 2.956);
	assert(!gpas2.contains(""));
	gpas2.insert("Ethel", 3.538);
	gpas2.insert("", 4.000);
	gpas2.insert("Lucy", 2.956);
	assert(gpas2.contains(""));
	gpas2.erase("Fred");
	assert(gpas2.size() == 3 && gpas2.contains("Lucy") && gpas2.contains("Ethel") &&
		gpas2.contains(""));

	Map m1;
	m1.insert("Fred", 2.956);
	Map m2;
	m2.insert("Ethel", 3.538);
	m2.insert("Lucy", 2.956);
	m1.swap(m2);
	assert(m1.size() == 2 && m1.contains("Ethel") && m1.contains("Lucy") &&
		m2.size() == 1 && m2.contains("Fred"));
}

int main()
{
	Map m;  // maps ints to strings
	assert(m.empty());
	ValueType v = "Ouch";
	assert(!m.get(42, v) && v == "Ouch"); // v unchanged by get failure
	m.insert(123456789, "Wow!");
	assert(m.size() == 1);
	KeyType k = 9876543;
	assert(m.get(0, k, v) && k == 123456789 && v == "Wow!");
	cout << "Passed all tests" << endl;
}
*/

/*int main()
{

Map test;
test.insert("noob", 1.23);
test.insert("B", 2.34);
test.insert("C", 3.45);
KeyType fire = "noob";
ValueType ice = 10.23;
KeyType var1 = "D";
ValueType var2 = 5.89;
KeyType smooth = "A";
ValueType why = 7.93;
ValueType hide;
assert(test.update(fire, ice) && test.get(fire, hide) && hide == 10.23);
assert(test.insertOrUpdate(smooth, why) && test.get(smooth, hide) && hide == 7.93);
assert(test.insertOrUpdate(var1, var2) && test.get(var1, hide) && hide == 5.89);


cout << "Passed all tests" << endl;
}*/
