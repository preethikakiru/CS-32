// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

#ifndef MYHASH_H
#define MYHASH_H
template<typename KeyType, typename ValueType>

class MyHash
{
public:
	MyHash(double maxLoadFactor = 0.5)
	{
		m_LoadFactor = maxLoadFactor; 
		if (maxLoadFactor > 2)
		{
			m_LoadFactor = 2;
		}
		else if (maxLoadFactor <= 0)
		{
			m_LoadFactor = 0.5;
		}
		size = 100; 
		m_numItems = 0; 
		Buckets = new Node*[100]; 
		for (int i = 0; i < 100; i++)
		{
			Buckets[i] = nullptr; 
		}
	}

	~MyHash()
	{
		for (int i = 0; i < size; i++)
		{
			while (Buckets[i] != nullptr)
			{
				Node * temp = Buckets[i];
				Buckets[i] = Buckets[i]->next;
				delete temp;
			}
		}
	}

	void reset()
	{
		for (int i = 0; i < size; i++)
		{
			while (Buckets[i] != nullptr)
			{
				Node * temp = Buckets[i];
				Buckets[i] = Buckets[i]->next;
				delete temp;
			}
		}
		size = 100;
		m_numItems = 0;
		Buckets = new Node*[100];
		for (int i = 0; i < 100; i++)
		{
			Buckets[i] = nullptr;
		}
	}

	void associate(const KeyType& key, const ValueType& value)
	{
		if (getLoadFactor() > m_LoadFactor)
		{
			Node** tempArray = new Node*[size * 2]; 
			m_numItems = 0;
			for (int i = 0; i < size * 2; i++)
			{
				tempArray[i] = nullptr; 
			}
			int oldSize = size; 
			size = size * 2; 
			for (int i = 0; i < oldSize; i++)
			{
				if (Buckets[i] != nullptr)
				{
					unsigned int x = getBucketNumber(Buckets[i]->key);
					if (Buckets[x] == nullptr)
					{
						tempArray[x] = new Node;
						tempArray[x]->key = Buckets[i]->key;
						tempArray[x]->value = Buckets[i]->value;
					}
					else
					{
						Node* temp = tempArray[x];
						while (temp->next != nullptr)
							temp = temp->next;
						temp->next = new Node;
						temp->next->value = Buckets[x]->value;
						temp->next->key = Buckets[x]->key;
					}
					Node* erase = Buckets[x]; 
					Buckets[x] = Buckets[x]->next; 
					delete erase; 
				}
			}
			delete[] Buckets; 
			Buckets = tempArray;
		}
		else
		{
			int wasFound = 0;
			bool isFound = false;
			for (int i = 0; i < size; i++)
			{
				if (Buckets[i] != nullptr)
				{
					if (Buckets[i]->key == key)
					{
						wasFound = i;
						isFound = true;
						break;
					}
				}
			}
			if (isFound == false)
			{
				int bucketNumber = getBucketNumber(key);
				Node* temp = new Node; 
				if (Buckets[bucketNumber] != nullptr)
				{
					Node* p = Buckets[bucketNumber]; 
					while (p->next != nullptr)
					{
						p = p->next; 
					}
					p->next = temp; 
					temp->key = key;
					temp->value = value;
					m_numItems++;
				}
				else
				{
					temp->next = nullptr; 
					temp->key = key; 
					temp->value = value; 
					Buckets[bucketNumber] = temp; 
					m_numItems++;
				}
			}
			else if (isFound == true)
			{
				Buckets[wasFound]->value = value; 
			}
		}
	}

	int getNumItems() const
	{
		return m_numItems; 
	}


	double getLoadFactor() const
	{
		double x = double(m_numItems)/double(size); 
		return x; 
	}

	// for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const
	{
		unsigned int number = getBucketNumber(key); 
		Node* p = Buckets[number]; 
		while (p != nullptr)
		{
			if(p->key == key)
				return &(p->value); 
			p = p->next; 
		}
		return nullptr; 
	}


	// for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
	}

	// C++11 syntax for preventing copying and assignment
	MyHash(const MyHash&) = delete;
	MyHash& operator=(const MyHash&) = delete;

private:
	double m_LoadFactor; 
	int m_numItems; 
	int size; 

	struct Node
	{
		KeyType key; 
		ValueType value; 
		Node* next = nullptr;
	};

	Node** Buckets; 
	unsigned int getBucketNumber(const KeyType& key) const
	{ 
		unsigned int myHash(const KeyType& s);
		unsigned int x = myHash(key); 
		unsigned int y = x % size; 
		return y; 
	}

	void addBucket(Node* ptr)
	{
		Node* tmp = new Node;
	}
};
#endif



#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED

#include <unordered_map>  // YOU MUST NOT USE THIS HEADER IN CODE YOU TURN IN
#include <algorithm>

// In accordance with the spec, YOU MUST NOT TURN IN THIS CLASS TEMPLATE,
// since you are not allowed to use any STL containers, and this
// implementation uses std::unordered_map.

// This code is deliberately obfuscated.

// If you can not get your own MyHash class template working, you may use
// this one during development in order to let you proceed with implementing
// the other classes for this project; you can then go back to working on
// fixing your own MyHash class template.

/*
template<typename KeyType, typename ValueType>
class MyHash
{
public:
	MyHash(const MyHash&) = delete;
	MyHash& operator=(const MyHash&) = delete;
	using O = KeyType; using maxloadfactor = float; using O10 = int; void reset() {
		maxloadfactor max_1oad_factor = l01.max_load_factor(); l01.clear(); l01.
			max_load_factor(max_1oad_factor); l01.rehash(doub1e + doub1e);
	}using String =
		double; using l0 = ValueType; using l1O = O10 const; MyHash(String d0uble = doub1e / 10) :
		l01(doub1e + doub1e) {
		l01.max_load_factor(std::min<maxloadfactor>(doub1e / 5 / 5,
			std::max<maxloadfactor>((double)doub1e / (doub1e + doub1e), d0uble)));
	}using l10 = O
		const; using Const = MyHash<O, l0>; String getLoadFactor()const {
		return l01.
			load_factor();
	}using ll0 = l0 const; O10 getNumItems()const {
		return l01.size(
		);
	}using l00 = Const const; void associate(l10&Using, ll0&first) {
		l01[Using] =
			first;
	}using l1 = std::unordered_map<O, l0>; ll0*find(l10&l11)const {
		auto first(l01.
			find(l11)); return(first != l01.end() ? &first->second : 0);
	}l0*find(l10&l01) {
		return(
			l0*)(*(l00*)(this)).find(l01);
	}private:static l1O doub1e{ 50 }; l1 l01;
};
*/
#endif // MYHASH_INCLUDED
