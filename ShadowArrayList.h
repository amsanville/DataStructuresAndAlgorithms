#ifndef SHADOWARRAYLIST_H
#define SHADOWARRAYLIST_H

/*
Shadow Array List

This version of a list uses an array based structure with a shadow array at the
backend to manage resizing the array. What I mean by a shadow array is a second
array of exactly twice the size of the original array. The default
implementation in this case will use an array of size 5 and size 10. Once the
array of size fills up, we start adding things into the array of size 10 in the
proper place. Each time an item is added to the array of size 10, we copy one
element from the array of size 5 into the array of size 10. Once the array of
size 10 fills up, we delete the array of size 5, allocate memory for an array
of size 20 repeat the process. This prevents adding things into the list always
onstant time, which overcomes one of the downsides of using array-based lists.
*/
template<typename T>
class ShadowArrayList {
private:
	// Primary list
	T* primary;
	// Shadow list
	T* shadow;
	// Number of elements in use
	int size;
	// Size of the actual arrays (primary, and 2x for shadow)
	int capacity;
public:
	// Constructors
	ShadowArrayList();
	ShadowArrayList(const T data[], const int size);
	ShadowArrayList(const ShadowArrayList& pv);
	ShadowPoShadowArrayListintArray(const int cap);
	// Destructor
	~ShadowArrayList();
	// Other Functions
	// add a new T on the end
	void push_back(const T& p);
	// add a new T in the position specified
	void insert(const int position, const T& p);
	// remove the T at the position specified
	void remove(const int pos);
	// get the size of the array
	const int getSize() const;
	// remove everything and set the size to zero
	void clear();
	// remove everything and set capacity to new capacity
	void clear(const int newCap);
	// Set elements
	void set(int position, T p);
	// Get a pointer to the element at some arbitrary position, null if the
	// position is outside the array
	T* get(const int position);
	const T* get(const int position) const;
	// For Debugging
	void print() const;
	void getStatus() const;
};

#include"ShadowArrayList.cpp"

#endif