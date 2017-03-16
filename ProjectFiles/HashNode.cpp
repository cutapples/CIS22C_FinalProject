#include "HashNode.h"

HashNode::HashNode() {
	this->data = nullptr;
	this->next = nullptr;
	this->prev = nullptr;
}

HashNode::HashNode(SmashHero* data, HashNode* next, HashNode* prev) {
	this->data = data;
	this->next = next;
	this->prev = prev;
}