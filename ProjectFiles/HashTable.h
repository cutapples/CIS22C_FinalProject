#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include "Node.h"

class HashTable
{
private:
	static const int tableSize = 17;

	struct item{
		int keyValue, rarity;
		std::string name;
		item* next;
	};
	
	item *hTable[tableSize];

public:
	HashTable();
	int Hash(std::string key);
	void AddItem(int key, std::string name, int rarity);
	int numberOfItem(int index);
	void printTable();
	void printIndexItem(int index);
	void searchByName(std::string namee);
	void removeItem(std::string namee);
};

#endif