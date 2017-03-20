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

HashTable::HashTable() {
	//Initialize a new table of HashNode*'s and them all nullptrs
	hTable = new HashNode*[tableSize];
	for (int i = 0; i < tableSize; i++) {
		hTable[i] = nullptr;
	}
	collisions = 0;
}

HashTable::~HashTable() {
	// destructor for the Hashtable
	for (int i = 0; i < tableSize; i++) {
		if (hTable[i] != nullptr) {
			HashNode* tempPtr = hTable[i];
			//Find the last node in the linked list
			while (tempPtr->next != nullptr) {
				tempPtr = tempPtr->next;
			}
			//Backtrack through the linked list deleting nodes as you go through
			while (tempPtr->prev != nullptr) {
				tempPtr = tempPtr->prev;
				delete tempPtr->next->data;
				delete tempPtr->next;
			}
			delete tempPtr->data;
			delete tempPtr;
		}
	}
	delete[] hTable;
}

int HashTable::Hash(int key) {
	return ((53 * key) % tableSize);
}

int HashTable::getCollisions() {
	return collisions;
}

SmashHero* HashTable::getItem(int key) {
	//Hash the key
	//If the index at hashed key is the key return the data [i.e. if(hTable[index]->data == key)]
	//else while there is still a next node, check the next node
	//if found, move the node to the front of the list
	int hashy = Hash(key);
	bool flag = false;
	HashNode* entry = hTable[hashy];
	HashNode* temp = hTable[hashy];
	if (entry != nullptr) {
		while (entry != nullptr) { // parses through the hash table
			if (*entry->data == key) {
				if (*entry->data == temp->data->getPrimaryKey()) {
					flag = true;
					return entry->data;
				}
				else {
					//Relinking middle nodes
					entry->prev->next = entry->next;
					if (entry->next != nullptr) {
						entry->next->prev = entry->prev;
					}

					//Moving entry to front of list
					entry->prev = nullptr;
					entry->next = temp;
					temp->prev = entry;
					hTable[hashy] = entry;

					flag = true;
					return entry->data;
				}
			}
			entry = entry->next;
		}
		if (!flag) { // if the items was not found prompts the user the item was not in the hash table
			std::cout << "Could not find your " << key << " inside the hash table." << std::endl;
			entry->data = nullptr;
			return entry->data; //not sure what you're supposed to return if found nothing?
		}
	}
	return (entry->data = nullptr); //not sure what you're supposed to return if found nothing?
}

void HashTable::addItem(SmashHero* data) {
	//Hash the key
	//If the hashnode is a nullptr
	//	make a new hashnode at the index and point it to data
	//else while the next HashNode isn't a nullptr, make a tempptr that points to the next Hashnode
	//create a new hashnode at the end of the linked list and make it point to data, link HashNode*'s
	int hashy = Hash(data->getPrimaryKey());
	HashNode* curPtr = hTable[hashy];
	if (curPtr == nullptr) {
		curPtr = new HashNode(data, nullptr, nullptr);
		hTable[hashy] = curPtr;
	}
	else {
		collisions++;
		while (curPtr->next != nullptr) {
			curPtr = curPtr->next;
			collisions++;
		}
		curPtr->next = new HashNode(data, nullptr, curPtr);
	}
}

void HashTable::removeItem(int key) {
	// Hash the key
	// If the hashNode is null do nothing 
	// else parses through the hash table until the item is found
	// remove the item then resets the pointer point to the correct spot
	int hashy = Hash(key);
	HashNode*entry = hTable[hashy];
	HashNode* temp = hTable[hashy];

	while (entry != nullptr) {
		if (*entry->data == key) {
			//Relinking middle nodes
			if (entry->prev != nullptr) {
				entry->prev->next = entry->next;
			}
			else {
				hTable[hashy] = entry->next;
			}
			if (entry->next != nullptr) {
				entry->next->prev = entry->prev;
			}
			delete entry;
			return;
		}
		entry = entry->next;
	}
}

ostream& operator<<(ostream& os, HashTable& hashTable) {
	for (int i = 0; i < hashTable.tableSize; i++) {
		if (hashTable.hTable[i] != nullptr) {
			HashNode* tempPtr = hashTable.hTable[i];
			os << *tempPtr->data << endl;
			while (tempPtr->next != nullptr) {
				tempPtr = tempPtr->next;
				os << *tempPtr->data << endl;
			}
		}
	}
	return os;
}

//displayInsequence()
// displayEfficiency()
