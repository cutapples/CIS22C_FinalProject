#ifndef DATABASE_H
#define DATABASE_H

#include "Hashtable.h"
#include "BST.h"
#include "SmashHero.h"

#include <ctime>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Database {
private:
	fstream saveFile; //The file used to load and save data from
	HashTable<T> hashTable; //Hashtable of currently owned Heroes
	BST<T> binarySearchTree; //Sorted tree of currently owned Heroes
	double teamList[5]; //primaryKeys of last used Team
	int gold; //Gold value gained through doing battles

public:
	Database(fstream& saveFile);

	void purchaseNewHero();
	void sellHero(double primaryKey);
	void displayHeroList();
	void displayOrderedList();
	void swapTeamMember(int slot, double primaryKey);
	void addCustomHero(string attributeLine);
	void searchByKey(double primaryKey);
	void printIndentedTree();
	void displayEfficiency();
	void saveToFile();
	void insertNewHero(T data);

	~Database();
};

//Takes in a file and loads in data, creates, and initializes the hash table and BST
template <class T>
Database<T>::Database(fstream& saveFile) {
	string tempTeam;
	int space1 = tempTeam.find(" ");
	int space2 = tempTeam.find(" ",space1);
	int space3 = tempTeam.find(" ", space2);
	int space4 = tempTeam.find(" ", space3);

	saveFile >> gold;
	getline(saveFile, tempTeam);

	teamList[0] = stod(tempTeam.substr(0, space1));
	teamList[1] = stod(tempTeam.substr(space1, space2));
	teamList[2] = stod(tempTeam.substr(space2, space3));
	teamList[3] = stod(tempTeam.substr(space3, space4));
	teamList[4] = stod(teamTeam.substr())

	
	
	/*
	Load gold and team list (still thinking of how this can be done
	Load rest of file into the hashTable and binarySearchTree
	Loop while not at the end of file
	Get line until new line, store into temp string
	Make temp SmashHero pointer and create a new SmashHero using the constructor that takes an attribute string
	insert temp SmashHero pointer using Database::insertNewHero
	*/
}

//Purchases a new hero by RNG
template <class T>
void Database<T>::purchaseNewHero() {
	/*
	Subtract gold value
	Create a random number between 1-100 for rarity %'s
	Depending on rarity index, Get a random number with associated lines in the Hero List file
	Go to line in file and read into a string
	Create new SmashHero object at a pointer passing in the attribute string for the constructor
	Call insertNewHero function
	*/
}

//Removes a hero from the database by primaryKey
template <class T>
void Database<T>::sellHero(double primaryKey) {
	/*
	Make temp pointer to SmashHero searched through Hash Table using primary key
	Call hashTable delete function
	Call BST delete function
	(If theres gold values associated with heroes, increase gold)
	Delete temp
	*/
}

//Displays the hero list in the hash table sequence
template <class T>
void Database<T>::displayHeroList() {
	/*
	call HashTable display function
	*/
}

//Displays the hero list in order using the BST
template <class T>
void Database<T>::displayOrderedList() {
	/*
	call BST display inOrder function
	*/
}

//Switches the team list slot to the new primaryKey
template <class T>
void Database<T>::swapTeamMember(int slot, double primaryKey) {
	/*
	teamList[slot] = primaryKey;
	*/
}

//Makes a new hero using the given attribute line, adding it to the hash table and BST
template <class T>
void Database<T>::addCustomHero(string attributeLine){
	/*
	Make a temporary SmashHero pointer and create a new SmashHero constructed with the given attribute line
	Call the Database insertNewHero function passing in the SmashHero pointer
	*/
}

//Searches the Hash Table for the primary key and displays the hero if found
template <class T>
void Database<T>::searchByKey(double primaryKey) {
	/*
	Call Hash Table search function and display the hero with that key
	*/
}

//Prints out the tree indented by height
template <class T>
void Database<T>::printIndentedTree() {
	/*
	Calls the BST print indented tree function
	*/
}

//Displays the efficiency statistics of the Hash Table
template <class T>
void Database<T>::displayEfficiency() {
	/*
	Calls the Hash Table display efficiency function
	*/
}

//Saves the current data set to the file
template <class T>
void Database<T>::saveToFile() {
	/*
	Clear old save file
	Save the current team and current gold onto the first line
	Read the Hash Table in sequence onto the file
	*/
}

template <class T>
void Database<T>::insertNewHero(T data) {
	/*
	Calls the HashTable and BST insert functions passing in the SmashHero pointer
	*/
}
