#include "provided.h"
#include <iostream>
#include <map>
#include <list>
#include <string>
using namespace std;

class TranslatorImpl
{
public:
	TranslatorImpl();
	bool pushMapping(string ciphertext, string plaintext);
	bool popMapping();
	string getTranslation(const string& ciphertext) const;
private:
	list<map<char, char>> connection;
};

TranslatorImpl::TranslatorImpl()
{
	char question = '?';
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	map<char, char> temp;
	for (int i = 0; i < alphabet.size(); i++)
	{
		temp.insert(make_pair(alphabet[i], question));
	}
	connection.push_front(temp);
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
	if (ciphertext.size() != plaintext.size())
		return false;
	map<char, char> temp;
	temp = connection.front();
	char p;
	char c;
	map<char, char> ::iterator it;
	for (int i = 0; i < ciphertext.size(); i++)
	{
		if ((!isalpha(ciphertext[i]) && ciphertext[i] != '?') || !isalpha(plaintext[i]))
			return false;
		p = tolower(plaintext[i]);
		c = tolower(ciphertext[i]);
		it = temp.begin();
		while (it != temp.end())
		{
			if ((it->first != c) && (it->second == p))
			{
				return false;
			}
			it++;
		}
		it = temp.begin(); 
		while (it != temp.end())
		{
			if (it->second != '?' && it->second != p)
			{
				return false;
			}
		}
	}
	connection.push_front(temp);
	return true;  // This compiles, but may not be correct
}

bool TranslatorImpl::popMapping()
{
	if (connection.size() == 1)
		return false;
	connection.pop_front();
	return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
	string translated = "";
	for (int i = 0; i <ciphertext.size(); i++)
	{
		map<char, char> temp;
		temp = connection.front();
		if (isalpha(ciphertext[i]))
		{
			char charlower = tolower(ciphertext[i]);
			if (temp.find(charlower) != temp.end())
			{
				if (islower(ciphertext[i]))
					translated += (temp.find(charlower))->second;
				else
					translated += toupper((temp.find(charlower))->second);
				continue;
			}
		}
		else
			translated += ciphertext[i]; 
	}
	return translated;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
	m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
	delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
	return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
	return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
	return m_impl->getTranslation(ciphertext);
}

/*void f()
{
	Translator t;
	t.pushMapping("DHL", "ERD"); // D‡E, H‡R, L‡D
	if (!t.pushMapping("QX", "RY")) // Q‡R, X‡Y
		cout << "Both H and Q would map to R!" << endl;
	// The current mapping is still D‡E, H‡R, L‡D with no
	// mapping for Q or X
	cout << t.getTranslation("HDX") << endl; // writes RE?
	if (!t.pushMapping("H", "S")) // H‡S
		cout << "H would map to both R and S!" << endl;
	else
		cout << "You stupid" << endl;
}

int main()
{
	f();
}*/