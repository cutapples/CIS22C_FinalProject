/////////////////////////////////////////////////////////////////////
//
//Name: Steve Tu
//Date: 03/05/17
//
/////////////////////////////////////////////////////////////////////
#ifndef BST_H
#define BST_H

#include <iostream>
#include "BSTNode.h"

using namespace std;

template <class T>
class BST {
private:
	Node<T>* root;	//The node at the top of the tree or the root Node.
public:
	//Construct a empty BST.
	BST();
	//Construct a BST with a root Node of data type T.
	BST(Node<T>* newNode) : root(newNode) {}
	//Destructor
	~BST();
	int size(Node<T>* root);
	//returns true if empty and false if not empty.
	bool isEmpty();
	//int size(Node<T>* root);
	//creates a new leaf and inserts into the tree as sorted from left to right.
	void insert(T newData);
	//removes the node that contains the data and accounts for if 0 children, 1 children, or 2 children.
	void remove(T oldData);
	//returns the node that contains the data specified.
	bool search(T oldData);
	//sends root node to inorder(Node<T>* root).
	void print_inOrder();
	//Recursively print all data from least to greatest or in-order form.
	void inOrder(Node<T>* root);
	//sends root node to preOrder(Node<T>* root).
	void print_preOrder();
	//Recursively print all data from greatest to least or pre-order form.
	void preOrder(Node<T>* root);
	//sends root node to postOrder(Node<T>* root).
	void print_postOrder();
	//Recursively print all data in post-order form.
	void postOrder(Node<T>* root);
	//Starts the recursive clearing process.
	void clear();
	//Recursively clears the tree.
	void clearRecursive(Node<T>* root);
	friend ostream& operator <<(ostream& out, const Node<T>* root) {
		out << root->data;
		return out;
	}
};

template<class T>
BST<T>::BST() {
	root = NULL;
}

template<class T>
BST<T>::~BST() {
	delete root;
	//root = NULL;
}



template<class T>
int BST<T>::size(Node<T>* root) {
	/*if (root == nullptr || root == NULL)
	{
	return 0;
	}*/
	if (!root) {
		return 0;
	}
	else {
		return(size(root->left) + 1 + size(root->right));
	}
}

template<class T>
void BST<T>::insert(T newData) // insert from left to right.
{
	Node<T>* newLeaf = new Node<T>(newData);
	Node<T>* parent = NULL;
	if (isEmpty()) //if we are creating a new tree, set the root to the new data.
	{
		root = newLeaf;
	}
	else //if not, insert data as a leaf node.
	{
		Node<T>* temp = root;
		while (temp) //find the parent node until we reach NULL
		{
			parent = temp;
			if (newLeaf->data > temp->data) {
				temp = temp->right; //move to the right
			}
			else {
				temp = temp->left; //move to the left
			}
		}
		if (newLeaf->data < parent->data) {
			parent->left = newLeaf; //set left child of parent to the new data if it is less than the parent's data.
		}
		else {
			parent->right = newLeaf; //set right child of parent to the new data if it is greater than the parent's data.
		}
	}
}

template<class T>
void BST<T>::remove(T oldData) {
	if (isEmpty()) //check if tree is empty or not.
	{
		cout << "This Tree is empty!" << endl;
		return;
	}
	Node<T>* temp = root;
	Node<T>* parent = NULL;
	bool found = false;
	while (temp != NULL) //find the specified data until NULL
	{
		if (temp->data == oldData) {
			found = true;
			break;
		}
		else //if not found, move to the next child.
		{
			parent = temp;
			if (oldData > temp->data) {
				temp = temp->right;
			}
			else {
				temp = temp->left;
			}
		}
	}
	if (!found) //if data was not found after going through each child, then return.
	{
		cout << "Specified data was not found." << endl;
		return;
	}

	//Here we have 3 cases:
	//1. Removing a node with 0 children.
	//2. Removing a node with 1 child.
	//3. Removing a node with 2 children.

	//Case 1: if statement is checking if node has 0 children.
	if (temp->left == NULL && temp->right == NULL) {
		if (parent->left == temp) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
		delete temp;
		return;
	}

	//Case 2: if statement is checking if we are removing  a node with 1 child.
	if (temp->left == NULL && temp->right != NULL || temp->left != NULL && temp->right == NULL) {
		if (temp->left == NULL && temp->right != NULL) {
			//if node has only right child.
			if (parent->left == temp) {
				parent->left = temp->right;
				delete temp;
			}
			else {
				parent->right = temp->right;
				delete temp;
			}
		}
		else {
			if (parent->left == temp) {
				parent->left = temp->left;
				delete temp;
			}
			else {
				parent->right = temp->right;
				delete temp;
			}
		}
		return;
	}

	//Case 3: if statement is checking if node has 2 children.
	if (temp->left != NULL && temp->right != NULL) {
		Node<T>* checkRightChild = temp->right;
		//We check to see if the right child of temp Node has any children.
		if (checkRightChild->left == NULL && checkRightChild->right == NULL) {
			temp = checkRightChild;
			delete checkRightChild;
			temp->right = NULL;
		}
		else //the right child of temp Node has children.
		{
			if ((temp->right)->left != NULL) //if right child of temp Node has a left child...
			{
				//find the smallest value from the children of the right child.
				Node<T>* rightChild = temp->right;
				Node<T>* rightChildWithLeftChild = (temp->right)->left;
				while (rightChildWithLeftChild->left != NULL) {
					//Here we are trying to find the smallest value from right child's left child.
					rightChild = rightChildWithLeftChild;
					rightChildWithLeftChild = rightChildWithLeftChild->left;
					//and then move them up.
				}
				//when done, replace the parent with the lowest value and 
				temp->data = rightChildWithLeftChild->data;
				delete rightChildWithLeftChild;
				rightChild->left = NULL;
			}
			else //if right child of temp Node has a right child...
			{
				Node<T>* rightChildWithRightChild = temp->right;
				temp->data = temp->data;
				temp->right = rightChildWithRightChild->right;
				delete rightChildWithRightChild;
			}
		}
		return;
	}
}

template<class T>
bool BST<T>::search(T oldData) {
	Node<T>* temp = root;
	while (temp != NULL) {
		if (temp->data == oldData) {
			break;
		}
		if (oldData > temp->data) {
			temp = temp->right;
		}
		else if (oldData < temp->data) {
			temp = temp->left;
		}
	}
	if (temp == NULL) {
		return false;
	}
	if (temp->data == oldData) {
		return true;
	}
	return false;
	//Node<T>* temp = root;
	//while (temp)
	//{
	//	if (temp->data == oldData) //if found, return the node.
	//	{
	//		return temp;
	//	}
	//	else if (oldData < temp->data) //if oldData is less than the temp's data, move on to the left child.
	//	{
	//		temp = temp->left;
	//	}
	//	else //if it is greater, move on to the right child.
	//	{
	//		temp = temp->right;
	//	}
	//}
	////if not found, print message and return back to main.
	//cout << "Unfortunately, we could not find " << oldData << endl;
	//return nullptr;
}

template<class T>
void BST<T>::print_inOrder() {
	if (!isEmpty()) {
		inOrder(root);
	}
	else {
		return;
	}
}

template<class T>
void BST<T>::inOrder(Node<T>* root) {
	if (root != NULL) {
		if (root->left) {
			inOrder(root->left);
		}
		cout << " " << root->data << " ";
		if (root->right) {
			inOrder(root->right);
		}
	}
	else {
		return;
	}
}

template<class T>
void BST<T>::print_preOrder() {
	if (!isEmpty()) {
		preOrder(root);
	}
	else {
		return;
	}
}

template<class T>
void BST<T>::preOrder(Node<T>* root) {
	if (root != NULL) {
		cout << " " << root->data << " ";
		if (root->left) {
			preOrder(root->left);
		}
		if (root->right) {
			preOrder(root->right);
		}
	}
	else {
		return;
	}
}

template<class T>
void BST<T>::print_postOrder() {
	if (!isEmpty()) {
		postOrder(root);
	}
	else {
		return;
	}
}

template<class T>
void BST<T>::postOrder(Node<T>* root) {
	if (root != NULL) {
		if (root->left) {
			postOrder(root->left);
		}
		if (root->right) {
			postOrder(root->right);
		}
		cout << " " << root->data << " ";
	}
	else {
		return;
	}
}

template<class T>
void BST<T>::clear() {
	clearRecursive(root);
}

template<class T>
void BST<T>::clearRecursive(Node<T>* root) {
	//if (root != NULL)
	//{
	//	clearRecursive(root->left);
	//	clearRecursive(root->right);
	//	delete root;
	//}

	if (root == NULL) {
		return;
	}
	//goes through each node and deletes the left nodes.
	clearRecursive(root->left);
	//goes through each node and deletes the right nodes.
	clearRecursive(root->right);
	delete root;	//deletes the node at the end of each recursion after going through each parent to child node.
					//root = NULL;
					//root->left = NULL;
					//root->right = NULL;
					//root->data = NULL;
}

template<class T>
bool BST<T>::isEmpty() {
	//return root == NULL;
	//if (root == 0)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
	if (root == NULL) //might need to change name to isNotEmpty() and change these 2 returns to false if checks are not correct.
	{
		return true;
	}
	else if (root->data == NULL) {
		return true;
	}
	else {
		return false;
	}
}

#endif
