#ifndef NODE_H
#define NODE_H
#include <cstddef>

template <class T>
class Node
{
public:
	T data;
	Node * left;
	Node * right;
	Node() : left(NULL), right(NULL) {}
	Node(T newData) : data(newData), left(NULL), right(NULL) {}
};

#endif
