#include <Windows.h>
#include <ctime>
#include <iostream>
#include "SmashHero.h"

using namespace std;

SmashHero::SmashHero(string line) 
{
	//The tabs are being found from the input line that we ghet from the file.
	int tab1 = line.find('\t');
	int tab2 = line.find('\t', tab1 + 1);
	int tab3 = line.find('\t', tab2 + 1);

	//The string is being parsed into seperate variables.
	string primaryKey = line.substr(0, tab1);
	string heroName = line.substr(tab1 + 1, tab2 - tab1 - 1);
	string rarity = line.substr(tab2 + 1, tab3 - tab2 - 1);

	//The functions are beijng called and each SmashHero attribute is being set with the variable being passed in.
	SmashHero::setPrimaryKey(stoi(primaryKey));
	SmashHero::setHeroName(heroName);
	SmashHero::setRarity(stoi(rarity));

	this->Level = 1;
}

ostream& operator<<(ostream& os, SmashHero& hero) 
{
	//Case being used if the Heroes are being output to the screen.

	// Case being used if the heroes are going to be saved into a file
	os << hero.primaryKey << "\t";
	os << hero.heroName << "\t";
	os << hero.rarityIndex << "\t";

	return os;
}

void SmashHero::GenerateStats() 
{
	// automatically generate stats for your acquired heroes when you purchase them based on their rarityIndex.
	if (rarityIndex == 1) 
	{
		Level = 1;
		EXP = 0;
		maxHP = rand() % 30 + 20;
		HP = maxHP;
		ATK = rand() % 15 + 5;
		DEF = rand() % 7 + 3;
	}
	else if (rarityIndex == 2)
	{
		Level = 1;
		EXP = 0;
		maxHP = rand() % 40 + 30;
		HP = maxHP;
		ATK = rand() % 15 + 8;
		DEF = rand() % 10 + 3;
	}
	else if (rarityIndex == 3) 
	{
		Level = 1;
		EXP = 0;
		maxHP = rand() % 50 + 40;
		HP = maxHP;
		ATK = rand() % 20 + 10;
		DEF = rand() % 15 + 5;
	}
	else if (rarityIndex == 4) 
	{
		Level = 1;
		EXP = 0;
		maxHP = rand() % 60 + 50;
		HP = maxHP;
		ATK = rand() % 30 + 20;
		DEF = rand() % 20 + 7;
	}
}

void SmashHero::AdjustDifficulty(int totalLevels) 
{
	// Adjusts difficulty by scaling HP, ATK and DEF of enemy team based on totalLevels of your team.
	if (totalLevels <= 15) 
	{
		Level = rand() % 10 + 1;
		maxHP = rand() % 25 + 15;
		HP = maxHP;
		ATK = rand() % 10 + 5;
		DEF = rand() % 3 + 1;
	}
	else if (totalLevels > 15 && totalLevels <= 50)
	{
		Level = rand() % 30 + 10;
		maxHP = rand() % 40 + 20;
		HP = maxHP;
		ATK = rand() % 10 + 5;
		DEF = rand() % 5 + 3;
	}
	else if (totalLevels > 50 && totalLevels <= 100)
	{
		Level = rand() % 50 + 30;
		maxHP = rand() % 50 + 30;
		HP = maxHP;
		ATK = rand() % 15 + 10;
		DEF = rand() % 6 + 3;
	}
	else if (totalLevels > 100 && totalLevels <= 300)
	{
		Level = rand() % 70 + 50;
		maxHP = rand() % 60 + 50;
		HP = maxHP;
		ATK = rand() % 20 + 15;
		DEF = rand() % 9 + 6;
	}
	else 
	{
		Level = rand() % 90 + 70;
		maxHP = rand() % 100 + 80;
		HP = maxHP;
		ATK = rand() % 30 + 25;
		DEF = rand() % 25 + 20;
	}
}

void SmashHero::HeroisHealed() 
{
	HP = maxHP;		// heals to full.
}

int SmashHero::getHeroHP() 
{
	if (HP < 0)		// if HP is negative.
	{
		HP = 0;		// want to make sure HP is not negative.
		return this->HP;
	}
	else 
	{
		return this->HP;
	}
}

void SmashHero::LoseHP(int attackpower) 
{
	HP = HP - attackpower;	// subtract attackpower from HP.
	if (HP < 0) 
	{
		HP = 0;		// set HP to zero if negative.
	}
}

bool SmashHero::isKnockedOut() 
{
	if (HP <= 0)	// double checking for negatives.
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool SmashHero::didWeHit() 
{
	// Dodge mechanic for us.
	int chance = rand() % 100 - 1;
	if (chance >= 5) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool SmashHero::didTheyHit() 
{
	// Dodge mechanic for enemy team.
	int chance = rand() % 100 - 1;
	if (chance >= 5) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void SmashHero::setEXP(int amount)
{
	EXP += amount;
	if (EXP >= 100) // level up and handle increase of stats and printing the relevant information for the user.
	{
		int overflow = EXP - 100;
		EXP = overflow;
		int tempLevel = Level;
		Level++;
		cout << heroName << " has leveled up! Level: " << tempLevel << " -> " << Level << "| EXP: " << EXP << "/100 |";
		int chance = rand() % 100 - 1;
		if (chance <= 25) 
		{
			cout << "ATK+ | ";
			ATK++;
			int tempmaxHP = maxHP;
			maxHP += 2;
			cout << "HP: " << tempmaxHP << "/" << tempmaxHP << " -> " << maxHP << "/" << maxHP << endl;
			HP = maxHP;		// completely heal the hero for leveling up.
		}
		else if (chance > 25 && chance < 90) 
		{
			cout << "ATK+ DEF+ | ";
			ATK++;
			DEF++;
			int tempmaxHP = maxHP;
			maxHP += 4;
			cout << "HP: " << tempmaxHP << "/" << tempmaxHP << " -> " << maxHP << "/" << maxHP << endl;
			HP = maxHP;		// completely heal the hero for leveling up.
		}
		else if (chance >= 90) 
		{
			cout << "ATK++ DEF++ | ";
			ATK += 2;
			DEF += 2;
			int tempmaxHP = maxHP;
			maxHP += 6;
			cout << "HP: " << tempmaxHP << "/" << tempmaxHP << " -> " << maxHP << "/" << maxHP << endl;
			HP = maxHP;		// completely heal the hero for leveling up.
		}
	}
}