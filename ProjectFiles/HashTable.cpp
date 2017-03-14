//*****************************************************************
//  HashTable.cpp
//  HashTable
//
//
//  This header file contains the Hash Table class definition.
//  Hash Table array elements consist of Linked List objects.
//*****************************************************************

#include "HashTable.h"
#include <iostream>

HashTable::HashTable(){
	//Initialize a new table of HashNode*'s and them all nullptrs
	hTable = new HashNode*[tableSize];
	top = new HashNode*[tableSize]; // Created for to store the prev items in the prev ptr
	for (int i = 0; i < tableSize; i++)
	{
		hTable[i] = nullptr;
		top[i] = nullptr;
	}
}

HashTable::~HashTable(){
	// destructor for the Hashtable
	delete[] hTable;
}

int HashTable::Hash(int key){
	return (key % tableSize);
}

int HashTable::getCollisions(){
	return collisions;
}

void HashTable::getItem(int key){
	//Hash the key
	//If the index at hashed key is the key return the data [i.e. if(hTable[index]->data == key)]
	//else while there is still a next node, check the next node
	//if found, move the node to the front of the list
	int hashy = Hash(key);
	bool flag = false;
	HashNode* entry = hTable[hashy];

	if (entry != nullptr){
		while (entry != nullptr){ // parses through the hash table
			if (entry->key == key){
				std::cout << "Element found at key: " << key << std::endl;
				std::cout << "Data: " << entry->data << std::endl;
				flag = true;
			}
		}
		if (!flag){ // if the items was not found prompts the user the item was not in the hash table
			std::cout << "Could not find your " << key << " inside the hash table." << std::endl;
		}
	}
}

void HashTable::addItem(SmashHero* data, int key) {
	//Hash the key
	//If the hashnode is a nullptr
	//	make a new hashnode at the index and point it to data
	//else while the next HashNode isn't a nullptr, make a tempptr that points to the next Hashnode
	//create a new hashnode at the end of the linked list and make it point to data, link HashNode*'s
	int hashy = Hash(key);
	HashNode *entry = hTable[hashy];
	if (entry == nullptr){ // Checks if the hash table is empty
		entry = new HashNode;
		entry->data = data;
		entry->key = key;
		entry->next = nullptr;
		entry->prev = nullptr;
		hTable[hashy] = entry;
		top[hashy] = entry;
	}
	else{
		while (entry != nullptr){ // If there are items within the hash table
			entry = entry->next;
			entry = new HashNode;
			entry->data = data;
			entry->key = key;
			entry->next = nullptr;
			entry->prev = top[hashy];
			top[hashy]->next = entry;
			top[hashy]->next = entry;
		}
	}
}

void HashTable::removeItem(int key){
	// Hash the key
	// If the hashNode is null do nothing 
	// else parses through the hash table until the item is found
	// remove the item then resets the pointer point to the correct spot
	int hashy = Hash(key);
	HashNode*entry = hTable[hashy];

	if (entry->key != key || entry == nullptr){
		std::cout << "No element found." << std::endl;
		return;
	}
	while (entry != nullptr){
		if (entry->next == nullptr){
			if (entry->prev == nullptr){
				hTable[hashy] = nullptr;
				top[hashy] = nullptr;
				delete entry;
				break;
			}
			else{
				top[hashy] = entry->prev;
				top[hashy]->next = nullptr;
				delete entry;
				entry = top[hashy];
			}
		}
		entry = entry->next;
	}

}
