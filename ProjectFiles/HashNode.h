#ifndef HASHNODE_H
#define HASHNODE_H

#include "SmashHero.h"

using namespace std;

class HashNode {
public:
	SmashHero* data;
	HashNode* next;
	HashNode* prev;

	HashNode();
	HashNode(SmashHero* data, HashNode* next, HashNode* prev);
};

HashNode::HashNode(){
	this->data = nullptr;
	this->next = nullptr;
	this->prev = nullptr;
}

HashNode::HashNode(SmashHero* data, HashNode* next, HashNode* prev){
	this->data = data;
	this->next = next;
	this->prev = prev;
}

#endif HASHNODE_H
