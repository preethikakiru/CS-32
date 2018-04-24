#include "Map.h"
#include <iostream>
using namespace std;
//member functions
Map::Map()
{
	//create an empty map
	map_size = 0;
	head = nullptr;
	tail = nullptr;
}

Map::Map(const Map& other)
{
	map_size = 0;
	head = nullptr;
	tail = nullptr;
	//if traversing from head
	Node *a = other.head;
	while (a != nullptr)
	{
		KeyType key = a->m_pair.m_key;
		ValueType value = a->m_pair.m_value;
		insert(key, value);
		a = a->next; 
	}
}

Map& Map::operator=(const Map& src)
{
	if (this == &src)
		return *this;
	Node *x = head;
	while (x != nullptr)
	{
		//set a temp variable to the value of the next node
		Node *y = x->next;
		//delete the current node
		delete x;
		//make the dangling pointer = the next node
		x = y;
	}
	map_size = 0;
	head = nullptr;
	tail = nullptr;
	//if traversing from head
	Node *a = src.head;
	while (a != nullptr)
	{
		KeyType key = a->m_pair.m_key;
		ValueType value = a->m_pair.m_value;
		insert(key, value);
		a = a->next;
	}
	return *this; 
}

Map::~Map()
{
	Node *x = head; 
	while (x != nullptr)
	{
		//set a temp variable to the value of the next node
		Node *y = x->next;
		//delete the current node
		delete x; 
		//make the dangling pointer = the next node
		x = y; 
	}
}

bool Map::empty() const
{
	if (head == nullptr && tail == nullptr)
		return true;
	else
		return false;
}

int Map::size() const
{
	return map_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	//if it already has the key returns false
	if (contains(key))
		return false;
	//allocates a new node
	Node *p = new Node;
	p->m_pair.m_key = key;
	p->m_pair.m_value = value;
	//if the list is empty
	if (empty())
	{
		head = p;
		tail = p;
		p->next = nullptr;
		p->prev = nullptr;
		map_size++;
		return true;
	}
	else
	{
		//add node
		p->next = head;
		head = p;
		p->next->prev = p;
		p->prev = nullptr;
		map_size++;
		return true;
	}
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	Node *q = head; 
	while (q != nullptr)
	{
		if (q->m_pair.m_key == key)
		{
			q->m_pair.m_value = value;
			return true; 
		}
		q = q->next;
	}
	return false; 
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (update(key, value))
		return true;
	//has to always return true
	else
		return (insert(key, value)); 
}

bool Map::erase(const KeyType& key)
{
	//if the list is empty
	if (head == nullptr)
		return false;
	//if the list doesnt contain the key
	if (!contains(key))
		return false; 
	
	//theres only one node
	if (head->next == nullptr)
	{
		delete head; 
		map_size--;
		head = nullptr; 
		tail = nullptr; 
		return true; 
	}
	else
	{
		//GIVES ERROR IF YOU TRY TO DELETE THE LAST ONE
		Node *q = head;
		while (q != nullptr)
		{
			//if you want to delete the first one!
			if (q->m_pair.m_key == key && q->next!= nullptr)
			{
				Node *temp = q;
				head = temp->next;
				delete temp;
				map_size--;
				return true;
			}
			//if you want to delete one in the middle of the linked list
			
			else if (q->next != nullptr)
			{
				if (q->next->m_pair.m_key == key && q->next->next != nullptr)
				{
					Node *temp = q->next;
					temp->next->prev = q;
					q->next = temp->next;
					delete temp;
					map_size--;
					return true;
				}
			}
			//if you want to delete the last one
			else if (q->next == nullptr && q->m_pair.m_key == key)
			{
				Node* temp = q;
				tail = temp->prev;
				temp->prev->next = nullptr; 
				delete temp; 
				map_size--; 
				return true; 
			}
			q = q->next;
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const
{
	Node *r = head; 
	while (r != nullptr)
	{
		if (r->m_pair.m_key == key)
			return true;
		else
			r = r->next; 
	}
	return false; 
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	Node *q = head; 
	while (q != nullptr)
	{
		if (q->m_pair.m_key == key)
		{
			value = q->m_pair.m_value;
			return true; 
		}
		q = q->next; 
	}
	return false; 
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i < 0)
		return false; 
	if (i >= size())
		return false; 
	else
	{
		Node *p = head; 
		int counter = 0; 
		while (p != nullptr)
		{
			if (i == counter)
			{
				key = p->m_pair.m_key; 
				value = p->m_pair.m_value; 
				return true; 
			}
			counter++; 
			p = p->next;
		}
	}
	return false; 
}

void Map::swap(Map& other)
{
	//saves the first map's location
	Node *tempHead = head; 
	Node *tempTail = tail; 
	int orgSize = size(); 

	//enters other's values into current map
	head = other.head; 
	tail = other.tail; 
	map_size = other.map_size; 

	//enter current maps old values into other
	other.head = tempHead; 
	other.tail = tempTail; 
	other.map_size = orgSize; 
}


//Non member functions
bool combine(const Map& m1, const Map& m2, Map& result)
{
	//make sure that result is empty
	result = m1;
	int insertCount = 0; 
	//get the size of m2
	int m2Count = m2.size(); 
	int resultCount = result.size(); //which is just currently the size of m1 
	bool found = false; 
	for (int i = 0; i < m2Count; i++) 
	{
		KeyType key; 
		ValueType value = 0; 
		m2.get(i, key, value); //get value of key and value
		for (int j = 0; j < resultCount; j++)
		{
			KeyType rkey; 
			ValueType rvalue = 0; 
			result.get(j, rkey, rvalue); //get value of key and value 
			if (key == rkey)
			{
				if (value != rvalue)
				{
					result.erase(key); 
				}
				found = true;
				break;
			}
		}
		if (found == false)
		{
			result.insert(key, value);
			resultCount = result.size();
			insertCount++; 
		}
		found = false; 
	}
	if (insertCount > 0)
		return true;
	else
		return false; 
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
	//make sure result doesnt have any random values
	result = m1;
	//get m2's size
	int m2Count = m2.size();
	//get results current size
	int resultCount = result.size(); 
	//go through result
	for (int i = 0; i < resultCount; i++)
	{
		KeyType key;
		ValueType value = 0;
		result.get(i, key, value); 
		//go through m2
		for (int j = 0; j < m2Count; j++)
		{
			KeyType rkey;
			ValueType rvalue = 0;
			m2.get(j, rkey, rvalue); //get value of key and value 
			if (key == rkey)
			{
				result.erase(key);
				resultCount = result.size();
				break;
			}
		}
	}
}
