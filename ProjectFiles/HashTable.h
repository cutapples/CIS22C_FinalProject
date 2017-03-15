#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"
#include "SmashHero.h"

class HashTable {
private:
	const int tableSize = 257;
	HashNode** hTable;
	int collisions;

public:
	HashTable();
	~HashTable();
	int Hash(int key);
	int getCollisions();
	SmashHero* getItem(int key);
	void addItem(SmashHero* data);
	void removeItem(int key);

};



#endif HASHTABLE_H
