#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"
#include "SmashHero.h"

class HashTable {
private:
	const int tableSize = 257;
	HashNode** hTable;
	int collisions = 0;

public:
	HashTable();
	~HashTable();
	int Hash(int key);
	int getCollisions();
	SmashHero* getItem(int key);
	void addItem(SmashHero* data);
	void removeItem(int key);
	
	friend ostream& operator<<(ostream& os, HashTable& hashTable);
};



#endif HASHTABLE_H
