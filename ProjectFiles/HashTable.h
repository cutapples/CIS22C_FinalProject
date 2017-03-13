#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"
#include "SmashHero.h"

class HashTable {
private:
	HashNode** hTable;
	int collisions;

public:
	HashTable();
	int Hash(double key);
	SmashHero* getItem(double key);
	void addItem(SmashHero* data, double key);
	

}

HashTable::HashTable(){
//Initialize a new table of HashNode*'s and them all nullptrs
}

SmashHero* HashTable::getItem(double key){
//Hash the key
//If the index at hashed key is the key return the data [i.e. if(hTable[index]->data == key)]
//else while there is still a next node, check the next node
//if found, move the node to the front of the list
}

void HashTable::addItem(SmashHero* data, double key) {
//Hash the key
//If the hashnode is a nullptr
//	make a new hashnode at the index and point it to data
//else while the next HashNode isn't a nullptr, make a tempptr that points to the next Hashnode
//create a new hashnode at the end of the linked list and make it point to data, link HashNode*'s
}

#endif HASHTABLE_H