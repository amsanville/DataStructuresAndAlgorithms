#define _USE_MATH_DEFINES
#include"MyMath.h"
#include"Sort.h"
#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>
#include<time.h>
#include<vector>
using namespace std;

/*
Write Data

Writes the data desired to the file specified.

Parameters:
filename - the name of the file
data - array of pointers to arrays desired to be printed
numCol - number of columns of data (i.e. number of arrays of data)
numDataPoints - the number of data points in each array
*/
void writeData(string fileName, double** data, int numCol, int numDataPoints) {
	ofstream output;
	output.open(fileName.c_str());
	for (int i = 0; i < numDataPoints; i++) {
		for (int j = 0; j < numCol; j++) {
			output << data[j][i] << " ";
		}
		output << "\n";
	}
	output.close();
}

/*
Create a series of test arrays for use with the sorting algorithms. The idea
is that each of the sorting algorithms will in place sort the different arrays
so these algorithms will provide a way to easily reset our test arrays.
*/

// Test 0: already sorted int array, all different
void test0(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
}

// Test 1: already sorted int array, all the same
void test1(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = i;
	}
}

/*
Test 2: random permutation of elements

Uses in place swaps to randomize the elements. Breaks the array into two
parts a randomized and non-randomized part. The idea is that we randomly select
an element from the non-randomized part and swap it with the first non-random
element. That then becomes part of the randomized part.
*/
void test2(int* arr, int size) {
	for (int i = size - 1; i > 0; i--) {
		// Randomly select
		int index = rand() % i;
		// Swap
		int temp = arr[index];
		arr[index] = arr[size - i];
		arr[size - i] = temp;
	}
}

/*
Test 3: random elements

Generates random numbers and populates the array
*/
void test3(int* arr, int size) {
	for (int i = 0; i < size; i++){
		arr[i] = rand() % (2 * size) - size;
	}
}

/*
Test 4: random CharWrapper elements

Generates characters using random integers between 32 and 127 (these all render
nicely and correspond to obvious keys on the keyboard).
*/
void test4(CharWrapper* arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = CharWrapper((rand() % 95) + 32);
	}
}

/*
Test 5: easy verification CharWrapper elements

Since we know that upper case letters come before lower case letters we can 
specifically initialize CharWrapper with only those characters to easily
verify that an array is sorted by inspecting the contents.
*/
void test5(CharWrapper* arr, int size) {
	for (int i = 0; i < size; i++) {
		// Flip coin for upper case or lower case
		if (rand() % 2) {
			arr[i] = CharWrapper(rand() % 26 + 65);
		}
		else {
			arr[i] = CharWrapper(rand() % 26 + 97);
		}
	}
}


/*
Test Sorting algorithms

Currently Tested:
* test0
* test1
* test2
* test3
* test4
* test5
* isSorted
* bubbleSort_int
* bubbleSort
* merge

Needs Testing:
* insertionSort
* mergeSort
* heapify
* heapSort
*/
void sortTest() {
	// Seed the RNG
	srand(time(NULL));

	// Initialize an array
	const int size = 8;
	int arr0[size];
	int arr1[size];
	int arr2[size];
	int arr3[size];
	CharWrapper arr4[size];
	CharWrapper arr5[size];
	
	// Test 0 Test
	test0(arr0, size);
	cout << "Test 0 Array (all 0s):" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr0[i] << " ";
	}
	cout << endl;

	// Test 1 Test
	test1(arr1, size);
	cout << "Test 1 Array (0, 1, 2, 3...):" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr1[i] << " ";
	}
	cout << endl;

	// Test 2 Test
	// Initialize
	test1(arr2, size);
	// Randomize
	test2(arr2, size);
	cout << "Test 2 Array (randomized Test 1):" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr2[i] << " ";
	}
	cout << endl;

	// Test 3 Test
	test3(arr3, size);
	cout << "Test 3 Array (random elements):" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;

	// Test 4 Test
	test4(arr4, size);
	cout << "Test 4 Array (random symbols):" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr4[i].getData() << " ";
	}
	cout << endl;

	// Test 5 Test
	test5(arr5, size);
	cout << "Test 5 Array (random letters):" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr5[i].getData() << " ";
	}
	cout << endl;

	// Test isSorted()
	cout << "\nExpected: Sorted, Actual: " << isSorted(arr0, size) << endl;
	cout << "Expected: Sorted, Actual: " << isSorted(arr1, size) << endl;
	cout << "Expected: Not Sorted, Actual: " << isSorted(arr2, size) << endl;
	cout << "Expected: Not Sorted, Actual: " << isSorted(arr3, size) << endl;
	cout << "Expected: Not Sorted, Actual: " << isSorted(arr4, size) << endl;
	cout << "Expected: Not Sorted, Actual: " << isSorted(arr5, size) << endl;
	cout << "Note: randomness does not gaurantee the last four results." << endl;
	cout << "Use the above as reference to whether or not they are sorted." << endl;

	//////////////////////////////////////////////////////////////////////////////
	// BUBBLE SORT ///////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	cout << "\nTest Bubble Sort:" << endl;
	cout << "All results should be sorted." << endl;
	bubbleSort_int(arr0, size);
	cout << "Test Array 0: " << isSorted(arr0, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr0[i] << " ";
	}
	cout << endl;

	bubbleSort_int(arr1, size);
	cout << "Test Array 1: " << isSorted(arr1, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr1[i] << " ";
	}
	cout << endl;

	bubbleSort_int(arr2, size);
	cout << "Test Array 2: " << isSorted(arr2, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr2[i] << " ";
	}
	cout << endl;

	bubbleSort_int(arr3, size);
	cout << "Test Array 3: " << isSorted(arr3, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr3[i]<< " ";
	}
	cout << endl;

	test3(arr3, size);
	bubbleSort(arr3, size);
	cout << "New Test 3 Array in template based Sort: " << isSorted(arr3, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;

	bubbleSort(arr4, size);
	cout << "Test 4 Array: " << isSorted(arr4, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr4[i].getData() << " ";
	}
	cout << endl;

	bubbleSort(arr5, size);
	cout << "Test 5 Array: " << isSorted(arr5, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr5[i].getData() << " ";
	}
	cout << endl;
	// Character test
	cout << "\nPrint out valid characters for sorting verification: " << endl;
	for (int i = 32; i < 127; i++) {
		cout << (char)i << " ";
	}
	cout << endl;

	//////////////////////////////////////////////////////////////////////////////
	// INSERTION SORT ////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	cout << "\nTest Insertion Sort:" << endl;
	// Integer array
	test3(arr3, size);
	cout << "Initial array:" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;
	insertionSort(arr3, size);
	cout << "Test Array 3 Final Result: " << isSorted(arr3, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;

	// Character array
	test5(arr5, size);
	cout << "Initial array:" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr5[i].getData() << " ";
	}
	insertionSort(arr5, size);
	cout << "Test Array 5 Final Result: " << isSorted(arr5, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr5[i].getData() << " ";
	}

	//////////////////////////////////////////////////////////////////////////////
	// MERGE SORT ////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	cout << "\nTest Merge and Merge Sort:" << endl;
	// Initialize the arrays
	const int size2 = 3;
	int arr6[size2];
	test0(arr6, size2);
	int arr7[size2];
	test1(arr7, size2);
	int arr8[2 * size2];
	// Run test
	merge(arr6, size2, arr7, size2, arr8, 2 * size2);
	cout << "Initial arrays:" << endl;
	for (int i = 0; i < size2; i++) {
		cout << arr6[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < size2; i++) {
		cout << arr7[i] << " ";
	}
	cout << endl;
	cout << "Merged result: " << endl;
	for (int i = 0; i <2*size2; i++) {
		cout << arr8[i] << " ";
	}
	cout << endl;
	// Swap the arrays and run again
	merge(arr7, size2, arr6, size2, arr8, 2 * size2);
	cout << "Initial arrays:" << endl;
	for (int i = 0; i < size2; i++) {
		cout << arr7[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < size2; i++) {
		cout << arr6[i] << " ";
	}
	cout << endl;
	cout << "Merged result: " << endl;
	for (int i = 0; i < 2*size2; i++) {
		cout << arr8[i] << " ";
	}
	cout << endl;

	// Test Merge Sort
	// Integer array
	test3(arr3, size);
	cout << "Initial array:" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;
	mergeSort(arr3, size);
	cout << "Test Array 3 Final Result: " << isSorted(arr3, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;

	// Character array
	test5(arr5, size);
	cout << "Initial array:" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr5[i].getData() << " ";
	}
	mergeSort(arr5, size);
	cout << "Test Array 5 Final Result: " << isSorted(arr5, size) << endl;
	for (int i = 0; i < size; i++) {
		cout << arr5[i].getData() << " ";
	}
	
	///////////////////////////////////////////////////////////////////////////
	// HEAP SORT //////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	cout << "\nTest Heapify and Heap Sort:" << endl;
	test3(arr3, size);
	cout << "Initial array:" << endl;
	for (int i = 0; i < size2; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;

	// Heapify
	heapify(arr3, 0, size);

	// Print the result
	cout << "Final Result:" << endl;
	treePrint(arr3, size);

	// Test Heap Sort
	// TODO
}


void searchTest() {

}

/*
Test Math Algorithms

Currently Tested:
* binarySearch_func
*/
void mathTest() {
	// Test binary search
	TestFunction0 test0;
	double root0 = binarySearch_func(test0, 0., 3.);
	cout << "Root of cosine fucntion between 0 and 3: " << root0 << endl;
}

/*
Function Test

Tests different ways to handle abstract function definitions. In this case, I'm
playing around with different ways to define parabolas.
*/

/*
Parabola Class

Child class to SimpleRealFunction which has only one virtual function that takes
one double and outputs one double. In this case, has a constructor and stores
a, b, c.
*/
class Parabola : public SimpleRealFunction {
private:
	double a, b, c;
public:
	// Construct the parabola from some prescribed values for a, b, and c
	Parabola(double a, double b, double c) : a(a), b(b), c(c) {};

	// Evaluate the parabola at x
	double operator()(double x) const {
		return a * pow(x, 2.) + b * pow(x, 1.) + c;
	}
};

/*
Polynomial Class

Child class to SimpleRealFunction that implements a general polynomial. The
coefficients are stored in the array at the index equivalent to the power to
which they correspond. In other words, at index 0 is the coefficient on the
x^0 term.
*/
class Polynomial: public SimpleRealFunction {
private:
	double* arr;
	int order;
public:
	// Construct the polynomial from some prescribed array
	Polynomial(double* arr, int order) : arr(arr), order(order) {};

	// Evaluate the polynomial at x
	double operator()(double x) const {
		double total = 0.;
		for (int i = 0; i < order; i++) {
			total += arr[i] * pow(x, (double)i);
		}
		return total;
	}
};

/*
Test Function Stuff

Currently Tested:
* Parabola Class
* writeData
* Polynomial Class
*/
void functionTest() {
	// Parameters of the data
	const int n = 101;	// Number of data points
	double a = -3.;		// Left end point
	double b = 3.;		// Right end point

	// Use class inheritance method to construct parabola data
	Parabola test0 = Parabola(1., -1., -2.);

	// Generate the data
	double x[n];
	double y0[n];
	for (int i = 0; i < n; i++) {
		x[i] = a + ((double)i) * (b - a) / ((double) (n - 1));
		y0[i] = test0(x[i]);
	}

	// Store the data in a data file
	double* outData[2];
	outData[0] = x;
	outData[1] = y0;
	writeData("test0Data.dat", outData, 2, n);

	// Test the polynomial class
	double coefs[3] = {1., -1., 2.};
	int order = 3;
	Polynomial test1 = Polynomial(coefs, order);

	// Generate the new y data
	double y1[n];
	for (int i = 0; i < n; i++) {
		y1[i] = test1(x[i]);
	}

	// Write to output file
	outData[0] = x;
	outData[1] = y1;
	writeData("test1Data.dat", outData, 2, n);
}

int main() {
	functionTest();
	return 0;
}