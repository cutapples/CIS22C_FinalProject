#ifndef SMASHHERO_H
#define SMASHHERO_H
#include <string>
#include <stdlib.h>

using namespace std;

class SmashHero {
private:
	int primaryKey;
	string heroName;
	int rarityIndex;
	/////////////////stats that will automatically be generated based on rarityIndex when Database.h calls GenerateStats(). No need to add anything more to text file.
	int HP;
	int maxHP;
	int TurnOrder;
	int ATK;
	int DEF;
	int EXP;
	int Level;
public:
	SmashHero() {};
	SmashHero(string line) {
		//The tabs are being found from the input line that we ghet from the file.
		int tab1 = line.find("\t");
		int tab2 = line.find("\t", tab1 + 1);
		int tab3 = line.find("\t", tab2 + 1);

		//The string is being parsed into seperate variables.
		string primaryKey = line.substr(0, tab1);
		string heroName = line.substr(tab1 + 1, tab2 - tab1 - 1);
		string rarity = line.substr(tab2 + 1, tab2 - tab3 - 1);

		//The functions are beijng called and each SmashHero attribute is being set with the variable being passed in.
		SmashHero::setPrimaryKey(stoi(primaryKey));
		SmashHero::setHeroName(heroName);
		SmashHero::setRarity(stoi(rarity));
	};

	int getPrimaryKey() { return this->primaryKey; };
	string getHeroName() { return this->heroName; };
	int getRarityIndex() { return this->rarityIndex; };

	void setPrimaryKey(int primaryKey) { this->primaryKey = primaryKey; };
	void setHeroName(string heroName) { this->heroName = heroName; };
	void setRarity(int rarityIndex) { this->rarityIndex = rarityIndex; };
	friend ostream& operator<<(ostream& os, SmashHero& hero) {

		//Case being used if the Heroes are being output to the screen.

		// Case being used if the heroes are going to be saved into a file
		os << hero.primaryKey << "\t";
		os << hero.heroName << "\t";
		os << hero.rarityIndex << "\t";


		return os;
	}

	friend bool operator>(SmashHero hero, int userKey) {
		return (hero.getPrimaryKey() > userKey);
	}

	friend bool operator<(SmashHero hero, int userKey) {
		return(hero.getPrimaryKey() < userKey);
	}

	friend bool operator==(SmashHero hero, int userKey) {
		return(hero.getPrimaryKey() == userKey);
	}

	friend bool operator!=(SmashHero hero, int userKey) {
		return (hero.getPrimaryKey() != userKey);
	}

	//////// functions used by battle system.
	void GenerateStats();
	int getLevel() { return this->Level; }
	void AdjustDifficulty(int totalLevels);
	//void setHeroHP(int newHP);
	void HeroisHealed();
	int getHeroHP();
	void LoseHP(int attackpower);
	//void setHeroMaxHP(int newmaxHP);
	int getHeroMaxHP() { return this->maxHP; }
	void setTurnOrder() { srand(time(NULL)); this->TurnOrder = rand() % 10 + 1; }
	int getTurnOrder() { return this->TurnOrder; }
	//void setAttackPower(int newATK);
	int getAttackPower() { return this->ATK; }
	int getDefensePower() { return this->DEF; }
	bool isKnockedOut();
	bool didWeHit();
	bool didTheyHit();
	void setEXP(int amount);
};

void SmashHero::GenerateStats()
{
	// automatically generate stats for your acquired heroes when you purchase them based on their rarityIndex.
	if (rarityIndex == 1)
	{
		Level = 1;
		maxHP = rand() % 17 - 14;
		HP = maxHP;
		ATK = rand() % 7 - 5;
		DEF = rand() % 5 - 3;
	}
	else if (rarityIndex == 2)
	{
		Level = 1;
		maxHP = rand() % 22 - 18;
		HP = maxHP;
		ATK = rand() % 10 - 8;
		DEF = rand() % 8 - 6;
	}
	else if (rarityIndex == 3)
	{
		Level = 1;
		maxHP = rand() % 27 - 23;
		HP = maxHP;
		ATK = rand() % 14 - 11;
		DEF = rand() % 11 - 9;
	}
	else if (rarityIndex == 4)
	{
		Level = 1;
		maxHP = rand() % 32 - 28;
		HP = maxHP;
		ATK = rand() % 18 - 15;
		DEF = rand() % 15 - 12;
	}
}

void SmashHero::AdjustDifficulty(int totalLevels)
{
	// Adjusts difficulty by scaling HP, ATK and DEF of enemy team based on totalLevels of your team.
	if (totalLevels <= 15)
	{
		Level = rand() % 5 - 1;
		maxHP = rand() % 20 - 10;
		HP = maxHP;
		ATK = rand() % 6 - 3;
		DEF = rand() % 5 - 3;
	}
	else if (totalLevels > 15 && totalLevels <= 50)
	{
		Level = rand() % 15 - 5;
		maxHP = rand() % 40 - 20;
		HP = maxHP;
		ATK = rand() % 12 - 7;
		DEF = rand() % 8 - 6;
	}
	else if (totalLevels > 50 && totalLevels <= 100)
	{
		Level = rand() % 25 - 15;
		maxHP = rand() % 60 - 40;
		HP = maxHP;
		ATK = rand() % 20 - 10;
		DEF = rand() % 13 - 8;
	}
	else if (totalLevels > 100 && totalLevels <= 300)
	{
		Level = rand() % 50 - 25;
		maxHP = rand() % 120 - 60;
		HP = maxHP;
		ATK = rand() % 30 - 25;
		DEF = rand() % 18 - 15;
	}
	else if (totalLevels > 300 && totalLevels <= 600)
	{
		Level = rand() % 100 - 50;
		maxHP = rand() % 200 - 150;
		HP = maxHP;
		ATK = rand() % 50 - 30;
		DEF = rand() % 25 - 18;
	}
	else
	{
		Level = rand() % 300 - 100;
		maxHP = rand() % 500 - 200;
		HP = maxHP;
		ATK = rand() % 80 - 60;
		DEF = rand() % 35 - 28;
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
	srand(time(NULL));
	int chance = rand() % 100 - 1;
	if (chance >= 20)
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
	srand(time(NULL));
	int chance = (rand() % 100 - 1) - 10;
	if (chance >= 30)
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













#endif SMASHHERO_H
