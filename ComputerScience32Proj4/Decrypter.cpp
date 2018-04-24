#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//no map or un_ordered map!!!!!!!!!!!!!!!
//,;:.!()[]{}-"#$%^&
//should have a wordlist object

class DecrypterImpl
{
public:
	DecrypterImpl();
	~DecrypterImpl();
	bool load(string filename);
	vector<string> crack(const string& ciphertext);
private:
	WordList m_wordList;
	int checkLeastTrans(string cipherWord, string txtWord)
	{
		//cerr << "in checkLeastTrans" << endl;
		int count = 0;
		//cerr << cipherWord.size() << endl;
		for (int i = 0; i < txtWord.size(); i++)
		{
			if (txtWord[i] == '?')
				count++;
		}
		return count;
	}
	void helper(string cipherMessage, Translator* m_translate, vector<string>& finalTranslations);
};

DecrypterImpl::DecrypterImpl()
{

}

DecrypterImpl::~DecrypterImpl()
{

}

bool DecrypterImpl::load(string filename)
{
	if (m_wordList.loadWordList(filename))
		return true;
	else
		return false;
}

bool isQuestionMark(string trans)
{
	for (int k = 0; k < trans.size(); k++)
	{
		if (trans[k] == '?')
		{
			return true;
		}
	}
	return false;
}

void DecrypterImpl::helper(string cipherMessage, Translator* m_translator, vector<string>& finalTranslations)
{
	string separators = ",;:.!()[]{}-\"#$%^&0123456789  ";
	Tokenizer t(separators);
	vector<string> tokenized = t.tokenize(cipherMessage);
	int minIndex = -1;
	int countMax = 0;
	for (int g = 0; g < tokenized.size(); g++)
	{
		//cerr << "At beginning of a loop for token in helper" << endl;
		//cerr << "print out element that being looked at " << tokenized[g] << endl;
		string least = m_translator->getTranslation(tokenized[g]);
		int numQ = checkLeastTrans(tokenized[g], least);
		if (numQ >= countMax)
			minIndex = g;
	}
	string leastTrans = tokenized[minIndex];
	string partiallyTrans;
	partiallyTrans = m_translator->getTranslation(leastTrans);
	vector<string> C = m_wordList.findCandidates(leastTrans, partiallyTrans);
	if (C.empty())
	{
		m_translator->popMapping();
		return;
	}
	for (int i = 0; i < C.size(); i++)
	{
		if (!m_translator->pushMapping(leastTrans, C[i]))
			continue;
		string translate = m_translator->getTranslation(cipherMessage);
		vector<string> translations = t.tokenize(translate);
		bool fullyTranslated = true;
		bool partiallyTranslated = false;
		bool invalidTrans = true;
		for (int b = 0; b < translations.size(); b++)
		{
			int numberQuest = 0;
			for (int k = 0; k < translations[b].size(); k++)
			{
				if (translations[b][k] == '?')
				{
					numberQuest++;
					partiallyTranslated = true;
					fullyTranslated = false;
				}
			}
			if (numberQuest == 0)
			{
				if (!m_wordList.contains(translations[b]))
				{
					m_translator->popMapping();
					invalidTrans = true; 
					continue; 
				}
			} 
			if (!m_wordList.contains(translations[b]))
			{
				invalidTrans = true; 
			}
		}
		if (invalidTrans == true)
		{ 
		}
		else if (invalidTrans == false && fullyTranslated == true)
		{
			m_translator->popMapping();
			finalTranslations.push_back(translate);
			continue;
		}
		else if (partiallyTranslated)
		{
			helper(cipherMessage, m_translator, finalTranslations);
		}
	}
	m_translator->popMapping(); 
	return; 
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{ 
	Translator* m_translator = new Translator; 
	vector<string> finalTranslations;
	helper(ciphertext, m_translator, finalTranslations);
	return finalTranslations;
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
	m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
	delete m_impl;
}

bool Decrypter::load(string filename)
{
	return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
	return m_impl->crack(ciphertext);
}

/*int main()
{
	Decrypter d;
	if (!d.load("wordslist.txt"))
	{
		cout << "Unable to load word list file " << "C:/wordlist.txt" << endl;
		return 0;
	} 
	string x = "Trcy oyc koon oz rweelycbb vmobcb, wyogrcn oecyb; hjg ozgcy tc moox bo moya wg grc vmobck koon grwg tc ko yog bcc grc oyc trlvr rwb hccy oecyck zon jb. - Rcmcy Xcmmcn";

	vector<string> ghy = d.crack(x);
	
	for (int i = 0; i < ghy.size(); i++)
		cout << ghy[i] << endl;
		
	return 0; 
}*/
