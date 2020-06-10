#ifndef HEAP_H
#define HEAP_H

/*
Heap

Implements a max heap using an array at the backend. It uses the indexing trick
where the 2*index and 2*index + 1 are the children of any given node.
Specifically, 2*index will be the left node and 2*index + 1 will be the right
node for the sake of heapifying.

Also for convention, the max heap will be based on operator<. Thus, the
structure is well defined for classes that impose some sort of ordering,
specifically with the less than operator.

Note: I based this off using the idiom that we can define lhs > rhs based on
operator< by simply switching lhs and rhs, i.e. lhs > rhs == rhs < lhs.
*/
template<typename T>
class Heap<T> {
private:
public:
};

/*
Binary Node

Implements a binary node for the backbone of a binary tree, such as a max heap.
Has an explicit left and right node.
*/
template<typename T>
class BinaryNode<T> {
private:
	T* data;
	BinaryNode<T> left;
	BinaryNode<T> right;
public:
	BinaryNode<T>() : data(nullptr), left(nullptr), right(nullptr) {};
};

/*
Heap

Implements a max heap using
*/
template<typename T>
class HeapNodes<T> {
private:
	BinaryNode<T>* head;
public:

};

#include"Heap.cpp"

#endif
