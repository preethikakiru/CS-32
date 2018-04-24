#ifndef MAP_H
#define MAP_H
#include <string>

using KeyType = std::string; //TheTypeOfTheKeysGoesHere
using ValueType = double; //TheTypeOfTheValuesGoesHere 

//using KeyType = int; //TheTypeOfTheKeysGoesHere
//using ValueType = std::string; //TheTypeOfTheValuesGoesHere 


class Map
{
public:
	//constructor
	Map();//Done, needs to be tested
	//copy constructor
	Map(const Map& other);//Done, needs to be tested
	//assignment operator
	Map& operator=(const Map& src);
	//destructor
	~Map();//Done, needs to be tested
	//tells you if map is emtpy
	bool empty() const;//Done, needs to be tested
	//returns size of map
	int size() const;//Done, needs to be tested
	//inserts node
	bool insert(const KeyType& key, const ValueType& value);
	//updates value of node
	bool update(const KeyType& key, const ValueType& value);//Done, needs to be tested
	bool insertOrUpdate(const KeyType& key, const ValueType& value);//Done, needs to be tested
	bool erase(const KeyType& key);//Done, needs to be tested
	bool contains(const KeyType& key) const;//Done, needs to be tested
	bool get(const KeyType& key, ValueType& value) const; //Done, needs to be tested
	bool get(int i, KeyType& key, ValueType& value) const;
	void swap(Map& other);
private:

	struct Pair
	{
		KeyType m_key;
		ValueType m_value;
	};

	//for linked list
	struct Node
	{
		Pair m_pair; 
		Node* next; 
		Node* prev; 
	};

	int map_size;
	Node *head; 
	Node *tail;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);
#endif

