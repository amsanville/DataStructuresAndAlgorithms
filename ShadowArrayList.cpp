#ifndef SHADOWARRAYLIST_CPP
#define SHADOWARRAYLIST_CPP
#include"ShadowArrayList.h"

// Default Constructor
template<typename T>
ShadowArrayList::ShadowArrayList() :
	primary(new T[5]), shadow(new T[10]), size(0), capacity(5) {
}

// Constructor 1
template<typename T>
ShadowArrayList::ShadowArrayList(const T points[], const int size) :
	primary(new T[size]), shadow(new T[2 * size]), size(size), capacity(size) {
	// Copy into the array
	for (int i = 0; i < size; i++) {
		primary[i] = points[i];
	}
}

// Copy Constructor
template<typename T>
ShadowArrayList::ShadowArrayList(const ShadowArrayList& pv) :
	primary(new Point[pv.size]), shadow(new Point[2 * pv.size]), size(pv.size), capacity(pv.size) {
	// Copy into the arrays
	for (int i = 0; i < size && i < capacity; i++) {
		primary[i] = pv.primary[i];
	}
	// Ensure that copied entries are copied into shadow too
	for (int i = capacity; i < size; i++) {
		shadow[i] = pv.shadow[i];
		shadow[i - capacity] = pv.shadow[i - capacity];
	}
}

// Explicit Size Constructor
template<typename T>
ShadowArrayList::ShadowArrayList(const int cap) :
	primary(new Point[cap]), shadow(new Point[2 * cap]), size(0), capacity(cap) {
}


// Destructor
template<typename T>
ShadowArrayList::~ShadowArrayList() {
	// TODO
}

// Push_Back
// Now constant time for all cases
template<typename T>
void ShadowArrayList::push_back(const Point& p) {
	// If at less than capacity of primary array
	if (size < capacity) {
		primary[size] = p;
		size++;
	}
	// If adding into the shadow array
	else {
		// If at capacity of shadow array
		if (size == 2 * capacity) {
			// Primary is entirely copied so delete
			delete[] primary;
			// Double the capacity and shuffle the pointers
			capacity *= 2;
			primary = shadow;
			// Create a new shadow array
			shadow = new Point[2 * capacity];
		}

		// Add in point
		shadow[size] = p;
		// Copy one point from the primary array into the shadow array
		shadow[size - capacity] = primary[size - capacity];
		size++;
	}
}

// Insert
/*
A real nuisance - shadow arrays are really good at allowing you to expand their
capacity, but not really at adding things in at arbitrary places. When an
element is added in arbitrarily, it requires us to make sure the shadow array
has the proper data at the end of the insertion. If in the middle of the array,
we simply need to move things down and recopy as appropriate. If outside the
array, we need to possibly resize everything. We also assume that all the blank
elements are the proper elements of the array, so we need to make sure those
are appropriately copied as well.
*/
template<typename T>
void ShadowArrayList::insert(const int position, const Point& p) {
	// Bad Input
	if (position < 0) {
		std::cout << "Error: cannot insert at negative indices." << std::endl;
	}
	// Adding beyond the end of the current array
	else if (position > size) {
		// Three cases:
		// Shadow array sufficient:
		if (position < 2 * capacity) {
			// Copy elements out of primary as is appropriate
			for (int i = size - capacity; i < position - capacity; i++) {
				shadow[i] = primary[i];
			}

			// Add in the new element
			size = position + 1;
			shadow[position] = p;
		}
		// Shadow array insufficient, but one 2 fold will capture everything		
		else if (position > 2 * capacity && position < 4 * capacity) {
			// Copy everything that still needs to be copied into the shadow array
			for (int i = size - capacity - 1; i < capacity; i++) {
				shadow[i] = primary[i];
			}

			// Pointer shuffle and reallocate
			delete[] primary;
			primary = shadow;
			capacity *= 2;
			shadow = new Point[2 * capacity];

			// Add in the point
			size = position + 1;
			shadow[position] = p;

			// Copy everything, as appropriate, into the new shadow array
			for (int i = 0; i < size - capacity; i++) {
				shadow[i] = primary[i];
			}
		}
		// Much larger than that
		else {
			// Allocate new memory
			Point* newPrimary = new Point[position + 1];
			Point* newShadow = new Point[2 * (position + 1)];

			// Copy elements out of primary as appropriate
			for (int i = 0; i < capacity && i < size; i++) {
				newPrimary[i] = primary[i];
			}
			// Copy elements out of shadow as appropriate
			for (int i = capacity; i < size; i++) {
				newPrimary[i] = shadow[i];
			}

			// Pointer shuffle
			delete[] primary;
			primary = newPrimary;
			delete[] shadow;
			shadow = newShadow;

			// Update
			primary[position] = p;
			capacity = position + 1;
			size = position + 1;
		}
	}
	else {
		// TODO
	}
}

// Remove
// Note: remove, because the elements need to be moved is still order N
template<typename T>
void ShadowArrayList::remove(const int pos) {
	// Nominally, should throw an index out of bounds exception
	if (pos >= size) {
		std::cout << "Error: nothing to remove, position beyond end of the array." << std::endl;
	}
	else if (pos < 0) {
		std::cout << "Error: negative position." << std::endl;
	}
	// If removing something only stored in the shadow array
	if (pos >= capacity) {
		for (int i = capacity; i < size - 1; i++) {
			shadow[i] = shadow[i + 1];
		}
		size--;
	}
	// If removing something stored in both the primary and shadow arrays.
	else {
		// Move all shared elements to the left
		for (int i = pos; i < capacity - 1; i++) {
			primary[i] = primary[i + 1];
			shadow[i] = shadow[i + 1];
		}

		// Move non-shared elements
		primary[capacity - 1] = shadow[capacity];
		for (int i = capacity; i < size - 1; i++) {
			shadow[i] = shadow[i + 1];
		}
		size--;
	}
}

// Get Size
template<typename T>
const int ShadowArrayList::getSize() const {
	return size;
}

// Clear
template<typename T>
void ShadowArrayList::clear() {
	// Delete the old data
	delete[] primary;
	delete[] shadow;

	// Reallocate the memory at the same capacity
	size = 0;
	primary = new Point[capacity];
	shadow = new Point[2 * capacity];
}

// Clear to new size
template<typename T>
void ShadowArrayList::clear(const int newCap) {
	// Delete the old data
	delete[] primary;
	delete[] shadow;

	// Reallocate the memory at the same capacity
	size = 0;
	capacity = newCap;
	primary = new Point[capacity];
	shadow = new Point[2 * capacity];
}

// Mutator
template<typename T>
void ShadowArrayList::set(int position, Point p) {
	// Bad input
	if (position < 0) {
		std::cout << "Error: no negative indices." << std::endl;
	}

	// Replace the current element if appropriate
	else if (position < size) {
		if (position < capacity) {
			primary[position] = p;
			if (position)
		}
		else {
			shadow[position] = p;
		}
	}
	// Otherwise use insert
	else {
		// TODO
	}
}

// Accessors
// Simply need to make sure we pull from the correct array
template<typename T>
Point* ShadowArrayList::get(const int position) {
	if (position >= 0 && position < size) {
		if (position < capacity) {
			return &primary[position];
		}
		else {
			return &shadow[position];
		}
	}
	else {
		// Warning might not be necessary
		std::cout << "Warning: accessing beyond the end of the array" << std::endl;
		return nullptr;
	}
}

template<typename T>
const Point* ShadowArrayList::get(const int position) const {
	if (position >= 0 && position < size) {
		if (position < capacity) {
			return &primary[position];
		}
		else {
			return &shadow[position];
		}
	}
	else {
		// Warning might not be necessary
		std::cout << "Warning: accessing beyond the end of the array" << std::endl;
		return nullptr;
	}
}

// Print (for debugging)
template<typename T>
void ShadowArrayList::print() const {
	// Print out of the primary array
	for (int i = 0; i < capacity && i < size; i++) {
		primary[i].print();
	}
	// Print out of the shadow array
	for (int i = capacity; i < size; i++) {
		shadow[i].print();
	}
}

// Get Status (for debugging)
template<typename T>
void ShadowArrayList::getStatus() const {
	std::cout << "Shadow Array Status:" << std::endl;
	std::cout << "Size: " << size << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;
	std::cout << "Contents of the primary array:" << std::endl;
	for (int i = 0; i < capacity; i++) {
		primary[i].print();
	}
	std::cout << std::endl;
	std::cout << "Contents of the shadow array:" << std::endl;
	for (int i = 0; i < 2 * capacity; i++) {
		shadow[i].print();
	}
	std::cout << std::endl;
}

#endif