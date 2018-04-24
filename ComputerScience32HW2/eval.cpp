#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool isOperator(char opr); 
bool validInfixExpression(string infix); 
bool isBracketMatch(string infix); 
void convertInfixPostfix(string infix, string& postfix);
void removeSpaces(string &infix); 

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
	removeSpaces(infix); 
	if (!isBracketMatch(infix))
		return 1; 
	if (!validInfixExpression(infix))
		return 1; 
	//checks to see if values are in the map 
	for (int j = 0; j < infix.size(); j++)
	{
		if (isalpha(infix[j]))
		{
			KeyType temp = ""; 
			temp += infix[j];
			if (!values.contains(temp))
			{
				int temp = result; 
				convertInfixPostfix(infix, postfix);
				result = temp; 
				return 2;
			}
		}
	}
	//postfix is set to postfix form of the expression
	convertInfixPostfix(infix, postfix); 
	//Evaluate Starts
	stack<int> operandStack; 
	int tempx = result;
	for (int a = 0; a < postfix.size(); a++) 
	{
		if (!isOperator(postfix[a]))
		{
			ValueType v; 
			KeyType k = ""; 
			k += postfix[a];
			values.get(k, v); 
			operandStack.push(v);
			if (postfix.size() == 1)
			{
				result = v;
				return 0; 
			}
			continue; 
		}
		else
		{
			int operand2 = operandStack.top();
			operandStack.pop();
			int operand1 = operandStack.top(); 
			operandStack.pop(); 
			
			result = 0; 
			switch (postfix[a])
			{
			case '+':
				result += operand1 + operand2;
				break;
			case '-':
				result += operand1 - operand2;
				break;
			case '*':
				result += operand1 * operand2;
				break;
			case '/':
				if (operand2 == 0)
				{
					result = tempx; 
					return 3;
				}
				result += operand1 / operand2;
				break;
			}
			operandStack.push(result); 
		}
	}
	return 0; 
}


void removeSpaces(string &infix)
{
	string temp = ""; 
	for (int k = 0; k < infix.size(); k++)
	{
		if (infix[k] != ' ')
		{
			temp += infix[k]; 
		}
	}
	infix = temp; 
}

bool isOperator(char opr)
{
	if (opr == '+' || opr == '-' || opr == '*' || opr == '/')
		return true;
	return false;
}

bool isBracketMatch(string infix)
{
	int left = 0; 
	int right = 0; 
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			left++;
		else if (infix[i] == ')')
			right++; 
	}
	if (left != right)
		return false; 
	return true; 
}

bool validInfixExpression(string infix)
{
	//checks the syntax rules
	int operandCount = 0;
	int operatorCount = 0;

	//empty string
	if (infix.size() == 0)
		return false;

	// can't start or end with opeartor
	if (isOperator(infix[0]) || isOperator(infix[infix.size() - 1]))
		return false;


	//check to see if they are all lowercase letters
	for (int i = 0; i < infix.size(); i++)
	{
		// All opearand are lower case
		if (isalpha(infix[i]) && !islower(infix[i]))
			return false;
		// operand followd by operator
		else if (isalpha(infix[i]) && i != infix.size() - 1 && !isOperator(infix[i + 1]) && infix[i + 1] != ')' &&  infix[i + 1] != ' ')
			return false;
		// (  followd by operand
		else if (infix[i] == '(' && i != infix.size() - 1 && isOperator(infix[i + 1]))
			return false;
		else if (infix[i] == '(' && i != infix.size() - 1 && infix[i + 1] == ')')
			return false;
		// )  followd by operand
		else if (infix[i] == ')' && i != infix.size() - 1 && isOperator(infix[i + 1]))
			return false;
		else if (infix[i] == ')' && i != infix.size() - 1 && infix[i - 1] == '(')
			return false; 

		if (isOperator(infix[i]))
			operatorCount++;
		if (isalpha(infix[i]))
			operandCount++;
	}
	// operands count should be greater than 1 and operators count. operators count greater than zero.
	if (operandCount < 1 || operandCount <= operatorCount)
		return false;
	if (operandCount > 1 && operatorCount < 1)
		return false; 

	return true;
}

void convertInfixPostfix(string infix, string &postfix)
{
	postfix = "";
	stack<char> operatorStack;
	for (int k = 0; k < infix.size(); k++)
	{
		switch (infix[k])
		{
		case ' ':
			break;
		case '(':
			operatorStack.push(infix[k]);
			break;
		case ')':
			while (operatorStack.top() != '(')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.pop();
			break;
		case '+':
		case '-':
		case '/':
		case '*':
			//+ae
			//a+e
			//a is already in the stack so its not going to be empty
			while (!operatorStack.empty() && operatorStack.top() != '(')
			{
				if ((infix[k] == '*' || infix[k] == '/') && (operatorStack.top() == '+' || operatorStack.top() == '-'))
				{
					break;
				}
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(infix[k]);
			break;
		default:
			postfix += infix[k];
			break;
		}
	}
	while (!operatorStack.empty())
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}
}

int main()
{
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
	{
		KeyType key = "";
		key += vars[k];
		m.insert(key, vals[k]);
	}
	string pf;
	int answer;


	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+"  &&  answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*"  &&  answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+"  &&  answer == -1);
	answer = 999;

	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/"  &&  answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	cout << "Passed all tests" << endl;
}
