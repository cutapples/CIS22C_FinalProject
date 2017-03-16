#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"
#include "SmashHero.h"

class HashTable {
private:
	const int tableSize = 257;
	HashNode** hTable, **top;
	int collisions = 0;

public:
	HashTable();
	~HashTable();
	int Hash(int key);
	int getCollisions();
	void getItem(int key);
	void addItem(SmashHero* data, int key);
	void removeItem(int key);
	
	friend ostream& operator<<(ostream& os, HashTable& hashTable);
};



#endif HASHTABLE_H
