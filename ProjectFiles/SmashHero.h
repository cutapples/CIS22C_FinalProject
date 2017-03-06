#ifndef SMASHHERO_H
#define SMASHHERO_H
#include <string>

using namespace std;

class SmashHero {
private:
	double primaryKey;
	string heroName;
	//rarity index
	//stats

public:
	SmashHero(string line);
	void setPrimaryKey(double primaryKey) { this->primaryKey = primaryKey; };
	void setHeroName(string heroName) { this->heroName = heroName; };
};

#endif SMASHHERO_H
