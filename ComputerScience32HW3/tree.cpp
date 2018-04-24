#include <iostream>
using namespace std;
// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
//  30 40 50 10 40 30 
// then for this value of a2     the function must return
//	10 20 40			1
//	10 40 30			2
//	20 10 40			0
//	50 40 30			3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
	int count = 0; 
	//if sizes are equal
	if (n2 <= 0)
		return 1;
	else if (n1 <= 0)
		return 0;
	else if (n1 == 1 && a1[0] == a2[0])
		return 1; 
	else
	{
		//10 50 40 20 50 40 30
		//50 40 30          3
		if (a1[0] == a2[0])
		{
			count += countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1); //increment count by the return value of the recursive call and by one for current
			count += countIncludes(a1 + 1, n1 - 1, a2, n2);
		}
		else 
			count += countIncludes(a1 + 1, n1 - 1, a2, n2); 
	}
	return count; 
}

// Exchange two doubles
void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > splitter come before all the other elements,
// and all the elements whose value is < splitter come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= splitter, or n if there is no such element, and firstLess is
// set to the index of the first element that is < splitter, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > splitter
//   * for firstNotGreater <= i < firstLess, a[i] == splitter
//   * for firstLess <= i < n, a[i] < splitter
// All the elements > splitter end up in no particular order.
// All the elements < splitter end up in no particular order.
void split(double a[], int n, double splitter,
	int& firstNotGreater, int& firstLess)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	//  Every element earlier than position firstNotGreater is > splitter
	//  Every element from position firstNotGreater to firstUnknown-1 is
	//    == splitter
	//  Every element from firstUnknown to firstLess-1 is not known yet
	//  Every element at position firstLess or later is < splitter

	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while (firstUnknown < firstLess)
	{
		if (a[firstUnknown] < splitter)
		{
			firstLess--;
			exchange(a[firstUnknown], a[firstLess]);
		}
		else
		{
			if (a[firstUnknown] > splitter)
			{
				exchange(a[firstNotGreater], a[firstUnknown]);
				firstNotGreater++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
	if (n <= 1)
		return; 
	double temp = 0; 
	if (a[0] < a[1])
	{
		temp = a[0];
		a[0] = a[1];
		a[1] = temp;
	}
	order(a + 1, n - 1);
	order(a, n - 1);
}

int main()
{
	const double a1[] = { 10, 50, 40, 20, 50, 40, 30 }; 
	const double a2[] = { 10, 20, 40};
	const double a3[] = { 10, 40, 30};
	const double a4[] = { 20, 10, 40};
	const double a5[] = { 50, 40, 30};
	cout << "a2: " << countIncludes(a1, 7, a2, 3) << " should be 1" << endl; //1
	cout << "a3: " << countIncludes(a1, 7, a3, 3) << " should be 2" << endl;//1
	cout << "a4: " << countIncludes(a1, 7, a4, 3)<< " should be 0" << endl;//0
	cout << "a5: " << countIncludes(a1, 7, a5, 3) << " should be 3" << endl;//0
	double a6[] = { 1, 8, 3, 8, 1}; 
	order(a6, 5); 
	for (int i = 0; i < 5; i++)
	{
		cout << a6[i] << endl;
	}
}