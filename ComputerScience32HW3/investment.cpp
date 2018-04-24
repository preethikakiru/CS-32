#include <iostream>
#include <string>
using namespace std;

//base class
class Investment
{
public:
	Investment(string name, int price)
	{
		m_price = price; 
		m_name = name; 
	}
	virtual ~Investment()
	{}
	string name() const
	{
		return m_name; 
	}
	virtual string description() const = 0; 
	virtual bool fungible() const
	{
		return false;
	}
	int purchasePrice() const
	{
		return m_price; 
	}
private:
	int m_price;
	string m_name; 
};

class Painting:public Investment
{
public:
	Painting(string name, int price):Investment(name, price)
	{}
	virtual ~Painting()
	{
		cout << "Destroying " << name() << ", a painting" << endl;
	}
	virtual string description() const
	{
		return "painting";
	}
};

class Stock:public Investment
{
public:
	Stock(string name, int price, string company):Investment(name, price)
	{
		m_name2 = company; 
	}
	virtual ~Stock()
	{
		cout << "Destroying " << name() << ", a stock holding" << endl;
	}
	virtual bool fungible() const
	{
		return true;
	}
	virtual string description() const
	{
		return "a stock trading as " + m_name2;
	}
private:
	string m_name2; 
};

class House:public Investment
{
public:
	House(string address, int price) : Investment(address, price)
	{}
	virtual ~House()
	{
		cout << "Destroying the house " << name() << endl;
	}
	virtual string description() const
	{
		return "house"; 
	}
};

void display(const Investment* inv)
{
	cout << inv->name();
	if (inv->fungible())
		cout << " (fungible)";
	cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

int main()
{
	Investment* portfolio[4];
	portfolio[0] = new Painting("Salvator Mundi", 450300000);
	// Stock holdings have a name, value, and ticker symbol
	portfolio[1] = new Stock("Alphabet", 100000, "GOOGL");
	portfolio[2] = new Stock("Symantec", 50000, "SYMC");
	portfolio[3] = new House("4 Privet Drive", 660000);

	for (int k = 0; k < 4; k++)
		display(portfolio[k]);

	// Clean up the investments before exiting
	cout << "Cleaning up" << endl;
	for (int k = 0; k < 4; k++)
		delete portfolio[k];
}