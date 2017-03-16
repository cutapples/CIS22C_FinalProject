#ifndef HASHNODE_H
#define HASHNODE_H

#include "SmashHero.h"

class HashNode {
public:
	SmashHero* data;
	HashNode* next;
	HashNode* prev;
	int key;

	HashNode();
	HashNode(SmashHero* data, HashNode* next, HashNode* prev);
};


#endif HASHNODE_H