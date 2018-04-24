#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
//Default constructor
Map original;

//test empty
assert(original.empty());
//test nothing to erase
assert(!original.erase("blank"));
//test inserting
original.insert("A", 1.23);		
original.insert("B", 2.34);
original.insert("C", 3.45);
assert(original.size() == 3);	//test size
KeyType k = "B";			//Setting values and keys
ValueType v = 9.87;
KeyType k1 = "D";
ValueType v1 = 2.36;
KeyType k2 = "A";
ValueType v2 = 5.67;
KeyType k3 = "B";
ValueType v4 = 5.89;
ValueType v3;
KeyType key;
ValueType val;

assert(original.get(0, key, val) && key == "C" && val == 3.45);		//testing get
assert(!(original.get(-1, key, val)&& key == "A" && val == 1.23));			//testing invalid i in get
assert(original.contains("A") && original.contains("B") && !original.contains("D"));
assert(original.update(k, v) && original.get(k, v3) && v3 == 9.87);				//testing update
assert(!original.insert(k3, v4) && original.get(k3, v3) && v3 == 9.87);			//testing invalid insert
assert(original.insertOrUpdate(k2, v2) && original.get(k2, v3) && v3 == 5.67);	//testing insertOrUpdate
assert(original.size() == 3);
assert(original.insertOrUpdate(k1, v1) && original.get(k1, v3) && v3 == 2.36);
assert(original.size() == 4);
assert(original.erase("C") && original.size() == 3);								//testing erase
assert(!original.get("C", v3));										//testing erase/invalid get
assert(v3 == 2.36);

//Testing swap
Map test1;
test1.insert("Z", 3.21);
test1.insert("Y", 5.43);
original.swap(test1);				//testing swap
assert(original.contains("Z") && original.contains("Y"));
assert(test1.contains("A") && test1.size() == 3);

//Testing assignment operator and copy constructor
ValueType vv;
Map test2(test1);		//testing copy constructor
assert(test2.contains("A") && test2.contains("B") && test2.get("B", vv) && vv == 9.87 && test2.size() == 3);
Map test3;
test3.insert("K", 1.23);
test3 = test1;			//testing assignment operator
assert(test3.contains("D") && test3.contains("B") && test3.get("D", vv) && vv == 2.36 && test3.size() == 3);
assert(test3.erase("A") && test3.size() == 2);	//testing erasing head
test3 = test2;
assert(test3.erase("B") && !test3.contains("B"));	//testing erasing middle
test3 = test1;
assert(test3.erase("D") && test3.size() == 2);	//testing erasing tail

Map m1;
assert(m1.empty());
assert(m1.insert("Ashley", 456));
assert(m1.insert("Kevin", 789));
assert(m1.insert("Michael", 789));
assert(m1.insert("Preethi", 123));

Map m2;
assert(m2.empty());
assert(m2.insert("Lauren", 458));
assert(m2.insert("Preethi", 123));
assert(m2.insert("Claire", 321));
assert(m2.insert("Steph", 567));

Map m3;
assert(m3.empty());
assert(m3.insert("Preethi", 123));
assert(m3.insert("Lauren", 475));
assert(m3.insert("Bruce", 586));
assert(m3.insert("Makenna", 734));

Map m4;
assert(m4.empty());
assert(m4.insert("Nicole", 729));
assert(m4.insert("Bruce", 586));
assert(m4.insert("John", 621));

Map result;
combine(m1, m2, result);
Map difference;
subtract(m1, m3, difference);
Map honey;
subtract(m2, m3, honey);
Map gold;
combine(m3, m4, gold);
int count = result.size();
int count3 = difference.size();
cout << count << endl;
cout << count3 << endl;
cout << "Test 1" << endl;
for (int i = 0; i < count; i++)
{
	KeyType key;
	ValueType value = 0;
	result.get(i, key, value);
	cout << key << " " << value << endl;
}
cout << "Test 2" << endl;
for (int j = 0; j < count3; j++)
{
	KeyType key;
	ValueType value = 0;
	difference.get(j, key, value);
	cout << key < < " " << value << endl;
}
cout << "Passed all Test Cases!" << endl;
}



//Test 1
/*
#include "Map.h"
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
	"Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
	"Map must be copy-constructible.");

void ThisFunctionWillNeverBeCalled()
{
	CHECKTYPE(&Map::operator=, Map& (Map::*)(const Map&));
	CHECKTYPE(&Map::empty, bool (Map::*)() const);
	CHECKTYPE(&Map::size, int  (Map::*)() const);
	CHECKTYPE(&Map::insert, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::update, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::erase, bool (Map::*)(const KeyType&));
	CHECKTYPE(&Map::contains, bool (Map::*)(const KeyType&) const);
	CHECKTYPE(&Map::get, bool (Map::*)(const KeyType&, ValueType&) const);
	CHECKTYPE(&Map::get, bool (Map::*)(int, KeyType&, ValueType&) const);
	CHECKTYPE(&Map::swap, void (Map::*)(Map&));

	CHECKTYPE(combine, bool(*)(const Map&, const Map&, Map&));
	CHECKTYPE(subtract, void(*)(const Map&, const Map&, Map&));
}

int main()
{}
*/

/*
//Test 2

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
Map m;
assert(m.insert("Fred", 123));
assert(m.insert("Ethel", 456));
assert(m.size() == 2);
ValueType v = 42;
assert(!m.get("Lucy", v)  &&  v == 42);
assert(m.get("Fred", v)  &&  v == 123);
v = 42;
KeyType x = "Lucy";
assert(m.get(0, x, v)  &&
((x == "Fred"  &&  v == 123)  ||  (x == "Ethel"  &&  v == 456)));
KeyType x2 = "Ricky";
assert(m.get(1, x2, v)  &&
((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  &&
x != x2);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}
*/

/*
//Test 3

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
Map m;
assert(m.insert(10, "diez"));
assert(m.insert(20, "veinte"));
assert(m.size() == 2);
ValueType v = "cuarenta y dos";
assert(!m.get(30, v)  &&  v == "cuarenta y dos");
assert(m.get(10, v)  &&  v == "diez");
v = "cuarenta y dos";
KeyType x = 30;
assert(m.get(0, x, v)  &&
((x == 10  &&  v == "diez")  ||  (x == 20  &&  v == "veinte")));
KeyType x2 = 40;
assert(m.get(1, x2, v)  &&
((x2 == 10  &&  v == "diez")  ||  (x2 == 20  &&  v == "veinte"))  &&
x != x2);
}

int main()
{
test();
cout << "Passed all tests" << endl;
}
*/

//Test 4
/*
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Map m1;
	assert(m1.empty()); 
	assert(m1.insert("Ashley", 456));
	assert(m1.insert("Kevin", 789));
	assert(m1.insert("Michael", 789));
	assert(m1.insert("Preethi", 123));
	
	Map m2; 
	assert(m2.empty());
	assert(m2.insert("Lauren", 458)); 
	assert(m2.insert("Preethi", 123));
	assert(m2.insert("Claire", 321));
	assert(m2.insert("Steph", 567));

	Map m3; 
	assert(m3.empty());
	assert(m3.insert("Preethi", 123));
	assert(m3.insert("Lauren", 475));
	assert(m3.insert("Bruce", 586));
	assert(m3.insert("Makenna", 734)); 
	
	Map m4; 
	assert(m4.empty());
	assert(m4.insert("Nicole", 729));
	assert(m4.insert("Bruce", 586));
	assert(m4.insert("John", 621)); 

	Map result;
	combine(m1, m2, result);
	Map difference; 
	subtract(m1, m3, difference);
	Map honey; 
	subtract(m2, m3, honey); 
	Map gold; 
	combine(m3, m4, gold); 
	int count = result.size(); 
	int count3 = difference.size(); 
	cout << count << endl;
	cout << count3 << endl;
	cout << "Test 1" << endl;
	for (int i = 0; i < count; i++)
	{
		KeyType key;
		ValueType value = 0;
		result.get(i, key, value);
		cout << key << " " << value << endl;
	}
	cout << "Test 2" << endl;
	for (int j = 0; j < count3; j++)
	{
		KeyType key; 
		ValueType value = 0; 
		difference.get(j, key, value); 
		cout << key << " " << value << endl;
	}
}
int main()
{
	test();
	cout << "Passed All Tests!" << endl;
}
*/