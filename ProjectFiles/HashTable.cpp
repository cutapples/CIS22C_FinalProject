#include <iostream>
#include "HashTable.h"

HashTable::HashTable()
{
	for (int i = 0; i < tableSize; i++)
	{
		hTable[i] = new item;
		hTable[i]->keyValue = 0000;
		hTable[i]->name = "empty";
		hTable[i]->rarity = 0;
		hTable[i]->next = NULL;
	}
}
int HashTable::Hash(std::string key)
{
	int hash = 0;

	for (int i = 0; i < key.length(); i++)
	{
		hash = hash + (int)key[i];
	}

	return (hash % tableSize);
}

void HashTable::AddItem(int key, std::string name, int rarity)
{
	int index = Hash(name);
	if (hTable[index]->name == "empty")
	{
		hTable[index]->keyValue = key;
		hTable[index]->name = name;		
		hTable[index]->rarity = rarity;
	}
	else
	{
		item* ptr = hTable[index]; // points to the beginning
		item* temp = new item;

		temp->name = name; // passing in the key value
		temp->keyValue = key; // passing in the name value
		temp->next = NULL; //making the new item point to nothing 

		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = temp;
	}
}

int HashTable::numberOfItem(int index)
{
	int count = 0;
	if (hTable[index]->name == "empty")
	{
		return count;
	}
	else
	{
		count++;
		item* ptr = hTable[index];
		while (ptr->next != NULL)
		{
			count++;
			ptr = ptr->next;
		}
	}
	return count;
}

void HashTable::printTable()
{
	int num;
	for (int i = 0; i < tableSize; i++)
	{
		num = numberOfItem(i);
		std::cout << "\n-----------------------------\n";
		std::cout << "index = " << i << std::endl;
		std::cout << "-----------------------------\n";
		std::cout << "keyValue: " << hTable[i]->keyValue << std::endl;
		std::cout << "name: " << hTable[i]->name << std::endl;
		std::cout << "rarity: " << hTable[i]->rarity << std::endl;
		std::cout << "# of items = " << num << std::endl;
	}
}

void HashTable::printIndexItem(int index)
{
	item* ptr = hTable[index];
	if (ptr->name == "empty")
	{
		std::cout << "\nItem does not exist\n";
	}
	else
	{
		std::cout << "\nindex= " << index << " contains the following item\n";
		while (ptr != NULL)
		{
			std::cout << "\n-----------------------------\n";
			std::cout << "keyValue: " << ptr->keyValue << std::endl;
			std::cout << "name: " << ptr->name << std::endl;
			std::cout << "rarity: " << ptr->rarity << std::endl;
			std::cout << "-----------------------------\n";
			ptr = ptr->next;
		}
	}
}

void HashTable::searchByName(std::string namee)
{
	int index = Hash(namee);
	bool found = false;
	int key, rarity;


	item* ptr = hTable[index];
	while (ptr != NULL)
	{
		if (ptr->name == namee)
		{
			found = true;
			key = ptr->keyValue;
			rarity = ptr->rarity;
		}
		ptr = ptr->next;
	}
	if (found == true)
	{
		std::cout << "\nYour search has been found\n";
		std::cout << "You've searched for: " << namee << std::endl;
		std::cout << "KeyValue = " << key << std::endl;
		std::cout << "Rarity = " << rarity << std::endl;
	}
	else
	{
		std::cout << "Sorry. Could not find what you've searched for.\n";
	}
}

void HashTable::removeItem(std::string namee)
{
	int index = Hash(namee);
	item* delPtr;
	item* temp;
	item* curr;

	if (hTable[index]->name == "empty" && hTable[index]->rarity == 0) //checks if there no items in the hTable;
	{
		std::cout << namee << " was not found in the Hash Table\n";
	}
	else if (hTable[index]->name == namee && hTable[index]->next == NULL) //Checks if there only 1 item in the bucket and has a matching name
	{
		hTable[index]->name = "empty";
		hTable[index]->keyValue = 0;
		hTable[index]->rarity = 0;
	}
	else if (hTable[index]->name == namee) // deletes the item and points it to the next item on the list
	{
		delPtr = hTable[index];
		hTable[index] = hTable[index]->next; 
		delete delPtr;
		std::cout << "Your item has been removed.\n";
	}
	else
	{
		temp = hTable[index]->next;
		curr = hTable[index];

		while (temp != NULL && temp->name != namee)
		{
			curr = temp;
			temp = temp->next;
		}
		if (temp == NULL)
		{
			std::cout << namee << " was not found in the Hash Table\n";
		}
		else
		{
			delPtr = temp;
			temp = temp->next;
			curr->next = temp;
			delete delPtr;
			std::cout << "Your item has been removed.\n";
		}
	}
}