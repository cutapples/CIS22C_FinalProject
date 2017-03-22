#ifndef SMASHHERO_H
#define SMASHHERO_H
#include <string>

using namespace std;

class SmashHero 
{
private:
	int primaryKey;
	string heroName;
	int rarityIndex;
	//Extra Stats
	int HP;
	int maxHP;
	int TurnOrder;
	int ATK;
	int DEF;
	int EXP;
	int Level;
public:
	SmashHero() {};
	SmashHero(string line);

	int getPrimaryKey() { return this->primaryKey; };
	string getHeroName() { return this->heroName; };
	int getRarityIndex() { return this->rarityIndex; };

	void setPrimaryKey(int primaryKey) { this->primaryKey = primaryKey; };
	void setHeroName(string heroName) { this->heroName = heroName; };
	void setRarity(int rarityIndex) { this->rarityIndex = rarityIndex; };

	///////Operator Overloading
	friend ostream& operator<<(ostream& os, SmashHero& hero);
	friend bool operator>(SmashHero hero, int userKey) 
	{
		return (hero.getPrimaryKey() > userKey);
	};
	friend bool operator<(SmashHero hero, int userKey) 
	{
		return (hero.getPrimaryKey() < userKey);
	};
	friend bool operator==(SmashHero hero, int userKey) 
	{
		return (hero.getPrimaryKey() == userKey);
	};
	friend bool operator>(SmashHero hero, SmashHero hero2) 
	{
		return (hero.getPrimaryKey() > hero2.getPrimaryKey());
	};
	friend bool operator<(SmashHero hero, SmashHero hero2) 
	{
		return (hero.getPrimaryKey() < hero2.getPrimaryKey());
	};
	friend bool operator==(SmashHero hero, SmashHero hero2) 
	{
		return (hero.getPrimaryKey() == hero2.getPrimaryKey());
	};

	//////// functions used by battle system.
	void GenerateStats();
	int getLevel() { return this->Level; };
	void AdjustDifficulty(int totalLevels);
	//void setHeroHP(int newHP);
	void HeroisHealed();
	int getHeroHP();
	void LoseHP(int attackpower);
	//void setHeroMaxHP(int newmaxHP);
	int getHeroMaxHP() { return this->maxHP; };
	void setTurnOrder(int i) { this->TurnOrder = i; };
	int getTurnOrder() { return this->TurnOrder; };
	//void setAttackPower(int newATK);
	int getAttackPower() { return this->ATK; };
	int getDefensePower() { return this->DEF; };
	bool isKnockedOut();
	bool didWeHit();
	bool didTheyHit();
	void setEXP(int amount);
};

#endif SMASHHERO_H