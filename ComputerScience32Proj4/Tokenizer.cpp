#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class TokenizerImpl
{
public:
	TokenizerImpl(string separators);
	vector<string> tokenize(const std::string& s) const;
private:
	vector<char> separator; 
	bool isSeparator(char s) const
	{
		for (int i = 0; i < separator.size(); i++)
		{
			if (separator[i] == s)
				return true; 
		}
		return false; 
	}
};

TokenizerImpl::TokenizerImpl(string separators)
{
	for (int i = 0; i < separators.size(); i++)
	{
		separator.push_back(separators[i]); 
	}
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
	bool addLetter = false; 
	vector<string> separated;
	string element = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (addLetter == false && !isSeparator(s[i]))
		{
			addLetter = true;
			element += s[i];
		}
		else if (addLetter == true && isSeparator(s[i]))
		{
			separated.push_back(element);
			element = "";
			addLetter = false;
		}
		else if (addLetter == true)
		{
			element += s[i];
		}
	}
	if (!separated.empty() && addLetter == true)
		separated.push_back(element); 
	return separated; 
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
	m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
	delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
	return m_impl->tokenize(s);
}

/*void rip()
{
	TokenizerImpl	t("	,.!");
	vector<string>	v = t.tokenize("This,,	is	a				test!	It's	the...	best!");
	//	v	now	contains	"This",	"is",	"a",	"test",	"It's",	"the",	and	"best"
	string	s = "!!!!!";
	vector<string> hate = t.tokenize(s); 
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}

	for (int j = 0; j < hate.size(); j++)
	{
		cout << hate[j] << endl;
	}
	
	//	v	is	now	empty
}

int main()
{
	rip(); 
}*/