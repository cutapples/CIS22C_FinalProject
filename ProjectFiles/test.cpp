#include <iostream>
#include <string>
#include "Hashtable.h"

int main(){
	
	//test code

	HashTable hashy;
	//hashy.printTable();

	hashy.AddItem(0000, "Fox", 1);
	hashy.AddItem(0001, "Cloud", 1);
	hashy.AddItem(0002, "Shiek", 1);
	hashy.AddItem(0003, "Mario", 1);
	hashy.AddItem(0004, "Sonic", 2);
	hashy.AddItem(0005, "Ryu", 2);
	hashy.AddItem(0006, "MewTwo", 2);
	hashy.AddItem(0007, "Bayonetta", 2);
	hashy.AddItem(0010, "Villager", 3);
	hashy.AddItem(0011, "Megaman", 3);
	hashy.AddItem(0012, "Ness", 3);
	hashy.AddItem(0013, "Corrin", 2);
	hashy.AddItem(0014, "Marth", 3);
	hashy.printTable();
	//hashy.printIndexItem(15);

	std::string name = "";
	while (name != "exit")
	{
		std::cout << "\nSearch for ";
		std::cin >> name;
		if (name != "exit")
		{
			hashy.searchByName(name);
		}
	}
	

	system("pause");
	return 0;
}