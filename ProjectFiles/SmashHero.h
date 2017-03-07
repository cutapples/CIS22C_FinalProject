#ifndef SMASHHERO_H
#define SMASHHERO_H
#include <string>

using namespace std;

class SmashHero {
private:
	double primaryKey;
	string heroName;
	int rarityIndex;
	//stats

public:
	SmashHero(){};
	SmashHero(string line){
		//The tabs are being found from the input line that we ghet from the file.
		int tab1 = line.find("\t");
		int tab2 = line.find("\t", tab1 + 1);
		int tab3 = line.find("\t", tab2 + 1);

		//The string is being parsed into seperate variables.
		string primaryKey = line.substr(0, tab1);
		string heroName = line.substr(tab1 + 1, tab2 - tab1 - 1);
		string rarity = line.substr(tab2 + 1, tab2 - tab3 - 1);

		//The functions are beijng called and each SmashHero attribute is being set with the variable being passed in.
		SmashHero::setPrimaryKey(stod(primaryKey));
		SmashHero::setHeroName(heroName);
		SmashHero::setRarity(stoi(rarity));
	};

	void setPrimaryKey(double primaryKey) { this->primaryKey = primaryKey; };
	void setHeroName(string heroName) { this->heroName = heroName; };
	void setRarity(int rarityIndex){ this->rarityIndex = rarityIndex; };
	friend ostream& operator<<(ostream& os, SmashHero& hero){

		//Case being used if the Heroes are being output to the screen.
		if(&os == &cout){


		}

		// Case being used if the heroes are going to be saved into a file
			os << hero.primaryKey << "\t";
			os << hero.heroName << "\t";
			os << hero.rarityIndex << "\t";
		

			return os;
	}


};

#endif SMASHHERO_H
