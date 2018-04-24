#include <iostream>
#include <string>
#include <stack>
using namespace std; 

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	Coord s(sr, sc); 
	Coord e(er, ec); 
	stack<Coord> coordStack;
	coordStack.push(s); 
	maze[sr][sc] = '#';

	while (!coordStack.empty())
	{
		Coord b = coordStack.top();
		coordStack.pop();
		if (b.r() == e.r() && b.c() == e.c())
			return true; 
		int row = b.r(); 
		int col = b.c();
		Coord east(row, col + 1); 
		if (maze[row][col + 1] == '.')
		{
			coordStack.push(east);
			maze[row][col + 1] = '#';
		}
		Coord south(row + 1, col); 
		if (maze[row + 1][col] == '.')
		{
			coordStack.push(south); 
			maze[row + 1][col] = '#'; 
		}
		Coord west(row, col - 1); 
		if (maze[row][col - 1] == '.')
		{
			coordStack.push(west); 
			maze[row][col - 1] = '#'; 
		}
		Coord north(row - 1, col); 
		if (maze[row - 1][col] == '.')
		{
			coordStack.push(north); 
			maze[row - 1][col] = '#'; 
		}
	}
	return false; 
}

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X...X..X.X",
		"X..XX....X",
		"X.X.XXXX.X",
		"XXX......X",
		"X...X.XX.X",
		"X.X.X..X.X",
		"X.XXXX.X.X",
		"X..X...X.X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}
