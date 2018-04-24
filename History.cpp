#include <iostream>
#include "History.h"
using namespace std;

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int i = 1; i <= m_rows; i++)
		for (int j = 1; j <= m_cols; j++)
			m_conversionHistory[i - 1][j - 1] = 0; //initializes array elements as 0
}

bool History::record(int r, int c)
{
	if (r > m_rows || c > m_cols || r <= 0 || c <= 0)
	{
		return false;
	}
	m_conversionHistory[r - 1][c - 1]++; //adds the position to the array
	return true;
}

void History::display() const
{
	clearScreen();
	char displayHistory[MAXROWS][MAXCOLS];
	for (int i = 1; i <= m_rows; i++)
	{
		for (int j =1; j <= m_cols; j++)
		{
			int numConverted = m_conversionHistory[i - 1][j - 1]; //chooses the letter for the point
			if (numConverted == 0)
				displayHistory[i - 1][j - 1] = '.';
			else if (numConverted >= 26)
				displayHistory[i - 1][j - 1] = 'Z';
			else
				displayHistory[i - 1][j - 1] = 64 + numConverted;
		}
	}
	for (int a = 1; a <= m_rows; a++)
	{
		for (int b = 1; b <= m_cols; b++)
		{
			cout << displayHistory[a - 1][b - 1];//how to display the grid
		}
		cout << endl;
	}
	cout << endl;//creates line between grid and comment
}