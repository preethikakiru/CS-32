#include "provided.h"
#include "MyHash.h"
#include <functional>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class WordListImpl
{
public:
	bool loadWordList(std::string filename);
	bool contains(string word) const;
	vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
	MyHash<string, vector<string>> m_hash;
	string pattern(string word) const
	{
		string lower = word; 
		for (int i = 0; i < lower.size(); i++)
		{
			lower[i] = tolower(lower[i]); 
		}
		string code = ""; 
		if (lower == "")
			return ""; 
		vector<char> pattern; 
		bool check = false; 
		for (int i = 0; i < lower.size(); i++)
		{
			check = false; 
			for (int j = 0; j < pattern.size(); j++)
			{
				if (pattern[j] == lower[i])
				{
					check = true; 
					code += j + 97; 
					break;
				}
			}
			if (check == false)
			{
				pattern.push_back(lower[i]);
				code += (pattern.size() - 1) + 97; 
			}
		}
		return code; 
	}
};

bool WordListImpl::loadWordList(string filename)
{
	m_hash.reset(); 
	ifstream infile(filename);
	if (!infile)
	{
		return false;
	}
	
	while (infile)
	{
		bool valid = true;
		string line;
		getline(infile, line); 
		vector<string> s;
		while(getline(infile, line))
		{
			if (m_hash.find(pattern(line)) == nullptr)
			{
				vector<string> s;
				for (int i = 0; i < line.size(); i++)
				{
					line[i] = tolower(line[i]); 
				}
				s.push_back(line);
				m_hash.associate(pattern(line), s);
			}
			else
			{
				for (int i = 0; i < line.size(); i++)
				{
					line[i] = tolower(line[i]);
				}
				m_hash.find(pattern(line))->push_back(line); 
			}
		}
	}
	return true;
}

void isAddable(string& word)
{
	for (int i = 0; i < word.size(); i++)
	{
		if (isupper(word[i]))
		{
			word[i] = tolower(word[i]); 
		}
	}
}

bool WordListImpl::contains(string word) const
{
	isAddable(word); 
	const vector<string>* p = m_hash.find(pattern(word));
	if (p == nullptr)
		return false; 
	else
	{
		vector<string>::const_iterator it;
		it = p->begin();
		while (it != p->end())
		{
			if ((*it) == word)
				return true;
			it++; 
		}
	}
	return false; 
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
	string test = cipherWord; 
	for (int b = 0; b < test.size(); b++)
	{
		test[b] = tolower(test[b]); 
	}

	for (int i = 0; i < test.size(); i++)
	{
		if (!isalpha(test[i]) && test[i] != '\'')
		{
			return vector<string>();
		}
	}
	if (currTranslation.size() != test.size())
	{
		return vector<string>();
	}
	for (int j = 0; j < currTranslation.size(); j++)
	{
		if (!isalpha(currTranslation[j]) && currTranslation[j] != '\'' && currTranslation[j] != '?')
		{
			return vector<string>();
		}
	}
	string cipherPattern = pattern(test);
	bool istrue = true;
	const vector<string>* p = m_hash.find(cipherPattern);
	vector<string> vec;
	if (p != nullptr)
	{
		 vec = *(p);
	}
	vector<string> words;
	for (int i = 0; i < vec.size(); i++)
	{
		istrue = true; 
		for (int j = 0; j < vec[i].size(); j++)
		{
			if (currTranslation[j] != '?')
			{
				if (currTranslation[j] != vec[i][j])
					istrue = false; 
			}
		}
		if (istrue)
		{
			words.push_back(vec[i]); 
		}
	}
	return words; 
}

//***** hash functions for string, int, and char *****

unsigned int myHash(const std::string& s)
{
	return std::hash<std::string>()(s);
}

unsigned int myHash(const int& i)
{
	return std::hash<int>()(i);
}

unsigned int myHash(const char& c)
{
	return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
	m_impl = new WordListImpl;
}

WordList::~WordList()
{
	delete m_impl;
}

bool WordList::loadWordList(string filename)
{
	return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
	return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
	return m_impl->findCandidates(cipherWord, currTranslation);
}

/*void f()
{
	WordList wl;
	if (!wl.loadWordList("C:/wordlist.txt"))
	{
		cout << "Unable to load word list" << endl;
		return;
	}
	if (wl.contains("onomatopoeia"))
		cout << "I found onomatopoeia!" << endl;
	else
		cout << "Onomatopoeia is not in the word list!" << endl;
	string cipher = "xyqbbq";
	string decodedSoFar = "?r????";
	vector<string> v = wl.findCandidates(cipher, decodedSoFar);
	if (v.empty())
		cout << "No matches found" << endl;
	else
	{
		cout << "Found these matches:" << endl;
		for (size_t k = 0; k < v.size(); k++)
			cout << v[k] << endl; // writes grotto and troppo
	}
}
*/


