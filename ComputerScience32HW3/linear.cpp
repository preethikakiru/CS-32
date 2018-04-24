#include <iostream>

using namespace std; 


bool somePredicate(double x)
{
	return x > 1;
}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
	if (n <= 0)
		return true;
	else if (n == 1)
		return somePredicate(a[0]);
	else if (!somePredicate(a[n - 1]))
			return false;
	return allTrue(a, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
	//minimum of zero elements
	if (n <= 0)
		return 0; 
	//if it return false at te last element 
	//then go look for how many more there are
	if (!somePredicate(a[n - 1]))
		return 1 + countFalse(a, n - 1);
	//if the last element isn't continue traversing through the array
	else
		return countFalse(a, n - 1); 
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
	if (n <= 0)
		return -1; 
	if (!somePredicate(a[0]))
		return 0; 
	int result = firstFalse(a + 1, n - 1); 
	//if the result is -1 then it never returns false
	if (result == -1)
		return -1; 
	//needs to be plus one since result 
	//is in terms of the smaller array
	return result + 1; 
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
	//if the array size is less than or equal to zero return -1
	if (n <= 0)
		return -1; 
	//if the size is equal to 1 than there's only one element
	if (n == 1)
		return 0; 
	//if the last element is less than output of the value of the function
	if (a[n - 1] < a[indexOfMin(a, n - 1)])
		return n - 1; 
	//return the int value
	return indexOfMin(a, n - 1); 
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{ 
	if (n2 <= 0)
		return true; 
	if (n1 <= 0)
		return false;
	//if both of the zero elements are equal change parameters
	if (a1[0] == a2[0])
		return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	//continue traversing thorugh the array
	else
		return includes(a1 + 1, n1 - 1, a2, n2); 
}

int main()
{
	double arr[] = { -2, 4, 3, 2, -7, 3 };
	allTrue(arr, 6);
	countFalse(arr, 6);
	firstFalse(arr, 6);
	cout << indexOfMin(arr, 6) << endl;
	double arr2[] = { 4, 2, 3};
	cout << "includes " << includes(arr, 6, arr2, 3) << endl;
}