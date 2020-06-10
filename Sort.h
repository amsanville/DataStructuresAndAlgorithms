#ifndef SORT_H
#define SORT_H
#include<iostream>
/*
Sorting Algorithms

Note: all sorting algorithms sort elements smallest to largest. For each sort
algorithm:
arr - an array, of type T or otherwise specified
size - the size of the array
The algorithm does an in place swap on the array so that upon return the data
is sorted.
*/

/*
TODO:
* Play around with some user defined exceptions, particularly for the data
structures or any time I would output some sort of error message
*/

/*
Bubble Sort

Implements the bubble sort algorithm on an array of integers as a proof of 
concept. Assumes the arr is actually a pointer to an array and that size is
correct. Does some basic checks to validate the input, but mostly assumes
that these are good assumptions.

Checks performed:
* Make sure that the size is bigger than 1 - anything 1 or less either does
not make sense or is already sorted.
* Check for null pointers
* Check if already sorted. This is order N and asymptotically faster than the
actual sort algorithm.

Checks unable to perform:
* Size mismatch (any errors associated with this
*/
void bubbleSort_int(int* arr, int size) {
	// Check if array is longer than size 1
	if (size < 0) {
		// TODO: Exception
		std::cout << "Error: size given less than 0." << std::endl;
	}
	else if (size == 0) {
		// TODO: Exception
		std::cout << "Error: nothing to sort." << std::endl;
	}
	else if (arr == nullptr) {
		// TODO: Exception
		std::cout << "Error: array pointer is null. Nothing to sort." << std::endl;
	}
	else if (size == 1) {
		// TODO: remove?
		std::cout << "Note: Already sorted." << std::endl;
	}
	else {
		// Check to make sure that the array is not already sorted
		int i = 0;
		while (arr[i] <= arr[i + 1] && i < size) {
			i++;
		}

		// If not sorted
		if (i != size) {
			int iterations = 0;
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < size - iterations - 1; k++) {
					if (arr[k + 1] < arr[k]) {
						int temp = arr[k + 1];
						arr[k + 1] = arr[k];
						arr[k] = temp;
					}
				}
				iterations++;
			}
		}
	}
}

/*
Bubble Sort - now with templates

Implements the bubble sort algorithm on an array of class T.
*/
template<typename T>
void bubbleSort(T* arr, int size) {
	// Check if array is longer than size 1
	if (size < 0) {
		// TODO: Exception
		std::cout << "Error: size given less than 0." << std::endl;
	}
	else if (size == 0) {
		// TODO: Exception
		std::cout << "Error: nothing to sort." << std::endl;
	}
	else if (arr == nullptr) {
		// TODO: Exception
		std::cout << "Error: array pointer is null. Nothing to sort." << std::endl;
	}
	else if (size == 1) {
		// TODO: remove?
		std::cout << "Note: Already sorted." << std::endl;
	}
	else {
		// Check to make sure that the array is not already sorted
		int i = 0;
		while (arr[i] <= arr[i + 1] && i < size) {
			i++;
		}

		// If not sorted
		if (i != size) {
			int iterations = 0;
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < size - iterations - 1; k++) {
					if (arr[k + 1] < arr[k]) {
						T temp = arr[k + 1];
						arr[k + 1] = arr[k];
						arr[k] = temp;
					}
				}
				iterations++;
			}
		}
	}
}
// Note: because the bubble sort code is an exact copy and paste from the
// version that uses int* to the version that uses T*, I'm not actually going
// to worry about making separate versions for the different sorting algorithms

/*
Inserstion Sort

Similar to bubbleSort above in that it makes the same assumptions and checks.
Uses the insertion sort algorithm, which swaps neighbors until each item is in
the correct place in the sorted part of the list.
*/
template<typename T>
void insertionSort(T* arr, int size) {
	// Check if array is longer than size 1
	if (size < 0) {
		// TODO: Exception
		std::cout << "Error: size given less than 0." << std::endl;
	}
	else if (size == 0) {
		// TODO: Exception
		std::cout << "Error: nothing to sort." << std::endl;
	}
	else if (arr == nullptr) {
		// TODO: Exception
		std::cout << "Error: array pointer is null. Nothing to sort." << std::endl;
	}
	else if (size == 1) {
		// TODO: remove?
		std::cout << "Note: Already sorted." << std::endl;
	}
	else {
		// Check to make sure that the array is not already sorted
		int i = 0;
		while (arr[i] <= arr[i + 1] && i < size) {
			i++;
		}

		// If not sorted
		if (i != size) {
			for(int j = 1; j < size; j++){
				bool done = false;
				for (int k = j; k > 0 && !done; k--) {
					// If not in the correct place, perform swap
					if (arr[k - 1] < arr[k]) {
						T temp = arr[k - 1];
						arr[k - 1] = arr[k];
						arr[k] = temp;
					}
					// If in correct place, done
					else {
						done = true;
					}
				}
			}
		}
	}
}

/*
Merge of merge sort

Merges two two sorted arrays into a single array. Makes no checks to ensure
that none of the arrays are aliasing as each other. I expect that if this is
used imporperly it will create subtle and complicated errors that will be hard
to catch and fix. Thus, I suggest not using this function outside of mergeSort
(which is what it was written for in the first place).
*/
template<typename T>
void merge(T* arr1, int size1, T* arr2, int size2, T* arr3, int size3) {
	// Current index for each array
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;

	// Add elements from each array to arr3
	bool done = false;
	for (; !done; index3++) {
		// Add an element from arr1 if smaller
		if (arr1[index1] < arr2[index2]) {
			arr3[index3] = arr1[index1];
			index1++;
		}
		// Add an element from arr2 if smaller
		else {
			arr3[index3] = arr2[index2];
			index2++;
		}
		// Check if all of one array was added to the third array
		if (index1 >= size1 || index2 >= size2) {
			done = true;
		}
	}

	// Add remaining elements from arr1
	for (; index1 < size1; index1++) {
		arr3[index3] = arr1[index1];
		index3++;
	}

	// Add remaining elements from arr2
	for (; index2 < size2; index2++) {
		arr3[index3] = arr2[index2];
		index3++;
	}
}

/*
Merge Sort

Sorts an array using merge sort. Makes similar checks in the above. Requires a
second array of equal size to the input array. Makes use of pointer arithmetic
to efficiently perform merges.

Merge Sort is recursive and performs poorly for small size arrays, I create an
artificial bottom for the recursive algorithm that will then rely on one of the
other sorting algorithms, in this case insertion sort. THRESHOLD_SIZE is base
case size tuned on my desktop. See included plot for details on THRESHOLD_SIZE
choice.

Note: the reason for poor performance is excess recursive calls. If the base
case is size 1, at 8 elements, it needs to split into 4 layers. This is
inefficient when compared to the other sorts.
*/
const int THRESHOLD_SIZE = 2;

template<typename T>
void mergeSort(T* arr, int size) {
	// Check if array is longer than size 1
	if (size < 0) {
		// TODO: Exception
		std::cout << "Error: size given less than 0." << std::endl;
	}
	else if (size == 0) {
		// TODO: Exception
		std::cout << "Error: nothing to sort." << std::endl;
	}
	else if (arr == nullptr) {
		// TODO: Exception
		std::cout << "Error: array pointer is null. Nothing to sort." << std::endl;
	}
	else if (size == 1) {
		// TODO: remove?
		std::cout << "Note: Already sorted." << std::endl;
	}
	else {
		// Check to make sure that the array is not already sorted
		int i = 0;
		while (arr[i] <= arr[i + 1] && i < size) {
			i++;
		}

		// If not sorted
		if (i != size) {
			// Split cases
			if (size < THRESHOLD_SIZE) {
				insertionSort<T>(arr, size);
			}
			else {
				// Step one: make a copy
				// Note: this is order N, so it will not affect the asymptotic 
				// behavior of the program
				T arrCopy[size];
				for (int i = 0; i < size; i++) {
					arrCopy[i] = arr[i];
				}

				// Split the copy and merge into the original
				mergeSort<T>(arrCopy, size - size / 2);
				mergeSort<T>(arrCopy + size - size / 2, size / 2);
				merge<T>(arrCopy, size - size / 2, arrCopy + size - size / 2, size / 2, arr, size);
			}
		}
	}
}

/*
Heapify

Enforces heap rules recursively.
*/
template<typename T>
void heapify(T* arr, int currIndex, int size) {
	// Check to see if the current node has children
	if (2 * currIndex < size) {
		// Check if parent node is smaller than either child
		if (arr[currIndex] < arr[2 * (currIndex + 1)] || arr[2 * (currIndex + 1) - 1]) {
			// Find which child is smaller
			if (arr[2 * (currIndex + 1)] < arr[2 * (currIndex + 1) - 1]) {
				// Swap
				T temp = arr[2 * (currIndex + 1) - 1];
				arr[2 * (currIndex + 1) - 1] = arr[currIndex];
				arr[currIndex] = temp;
				// Heapify
				heapify(arr, 2 * (currIndex + 1) - 1, size);
			}
			else {
				// Swap
				T temp = arr[2 * (currIndex + 1)];
				arr[2 * (currIndex + 1)] = arr[currIndex];
				arr[currIndex] = temp;
				// Heapify
				heapify(arr, 2 * (currIndex + 1), size);
			}
		}
	}
}

/*
Heap Sort

Treats the data in the array as if it were a max heap. Swaps the top element
with the last unsorted element and then heapifies in order to put items in order
from smallest to largest. Performs similar checks as the other sorting
algorithms.
*/
template<typename T>
void heapSort(T* arr, int size) {
	// Initial heapify
	heapify(arr, 0, size);
	for (int i = size - 1; i > 0; i--) {
		// Swap
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		// Re-heapify
		heapify(arr, 0, size - 1);
	}
}

/*
Tree Print

Print an array like it's a tree.
*/
void treePrint(int* arr, int size) {
	// Print out the rows of the tree
	int count = 0;
	for (int i = 0; i < size; i++) {
		for (int j = i; j < pow(2, count) && j < size; j++) {
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
		count++;
	}
}

/*
Quick Sort


*/
template<typename T>
void quickSort(T* arr, int size) {

}

/*
Radix Sort


*/
template<typename T>
void radixSort(T* arr, int size) {

}

/*
Bucket Sort

*/
template<typename T>
void bucketSort(T* arr, int size) {

}

/*
Shell Sort


*/
template<typename T>
void shellSort(T* arr, int size) {

}

///////////////////////////////////////////////////////////////////////////////
// DEBUG //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/*
CharWrapper

A wrapper class for characters to provide a meaningful test for the template
version of the sorts. Implements a < and <= operator for the sake of allowing
the template based sorting algorithms to work.

Overall, this class is likely unnecessary as you can compare chars using <
which likely automatically
*/
class CharWrapper {
private:
	char data;
public:
	// Constructors
	CharWrapper() : data(' ') {};
	CharWrapper(char newData) : data(newData) {};
	CharWrapper(int newData);

	// Accessor
	char getData() { return data; };

	// Less than based on ASCII code of the character
	friend bool operator<(const CharWrapper& lhs, const CharWrapper& rhs);
	// Equality based on ASCII code of the character
	friend bool operator==(const CharWrapper& lhs, const CharWrapper& rhs);
};

// Constructor using an integer
CharWrapper::CharWrapper(int newData) : data(' '){
	if (newData >= 32 && newData < 127) {
		data = (char) newData;
	}
	else {
		std::cout << "Error: unable to properly render character using white space." << std::endl;
	}
}

// Whole suite of comparison operations
inline bool operator<(const CharWrapper& lhs, const CharWrapper& rhs) {
	return ((int)lhs.data) < ((int)rhs.data);
}

inline bool operator==(const CharWrapper& lhs, const CharWrapper& rhs) {
	return ((int)lhs.data) == ((int)rhs.data);
}

inline bool operator>(const CharWrapper& lhs, const CharWrapper& rhs) {
	return rhs < lhs;
}

inline bool operator<=(const CharWrapper& lhs, const CharWrapper& rhs) {
	return lhs < rhs || lhs == rhs;
}

inline bool operator>=(const CharWrapper& lhs, const CharWrapper& rhs) {
	return rhs < lhs || rhs == lhs;
}

/*
Verify Something is Sorted

Follows the same sort of requirements as the above sorting algorithms.
*/
template<typename T>
bool isSorted(T* arr, int size) {
	// Assume array is sorted
	bool sorted = true;

	// Check each element in the array to see if it's sorted, exit condition
	// ensures that if the array is not sorted it will properly exit the while
	// loop setting the return properly as well.
	int i = 0;
	while (sorted && i < size - 1) {
		sorted = arr[i] <= arr[i + 1];
		i++;
	}

	// Return the final result
	return sorted;
}

/*
Test Sorting Algorithms

Makes use of lambda functions and the generic template of my above sorting
algorithms in order to provide a framework to test the sorting algorithms.
*/
#endif
