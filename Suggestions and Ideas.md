Name: Nintendo Smash Heroes (TBD)

* Open for Suggestions and Changes.

(?) means I don't know if idea should be implemented or not.
(??) means that these will probably be simplifed or removed entirely for being overly complicated.
(???) ughhh... too complicated maybe...
(????) my inner gamer is rambling right now.

********	IO		********
* Looping menus.
* Capitalize input if seaching for Hero name.
* Account for wrong input.

********	Hashing		********
* Resolve collisions by moving to another spot.

********	Text File	********
* Format: Name, skill name, Fighter, STR, AGI, etc. in string file for each line.
* When buying a Pack, go to line numbers in text file and parse out information for each Hero bought using string functions.
* Name
* Class(es) like Fighter, Tank, etc. (??)
* Skill name(s) (?)
* Stats like STR, AGI, etc. (?)
* Rarity (?)
* Higher rarity means higher stats than the lower tiers (?)
* Starting level (?)
* EXP (static or exponential) (?)

	Start of Program
* Read in text file of Heroes.
* Initialize hash table for all Heroes or Heroes in colleciton.
* Users will start program with random amount of money with a minimum and a maximum amount. (?)

********	Main Menu	********
1. Buy
2. Sell (?)
3. Send out to fight/quest (??)
4. View Collection of Heroes
5. Search Collection for a certain Hero (?)
6. Delete a certain Hero from Collection
.
.
.
n. Exit

********	Buy		********
* Additional menu here for options (?)
* Buy will give you a Pack of x number of random Heroes.
* Duplicates can happen...
* or automatically sold for some money to make code easier. (?)
* Special "Promotions" for increased rates for certain Heroes. They also cost more money than regular Packs. (?)
* All Heroes are seperated into Tiers of rarity like SSR, SR, R, N with lowering percentages. (?)
* If money is implemented, subtract from Pack's price.
* Keep track of total money spent (?)

********	Sell	********
* Delete Hero from collection
* Refund money (?)
* Deal with duplicates of sold Hero.

********	Send out to fight/quest		********
* Team of only n number of Heroes (?)
* If EXP is implemented, add random amount of EXP to Heroes if win. If lose, add reduced amount. (??)
* If money is implmeneted, add random amount or fixed amount to wallet. (?)
* Success rate of fight/quest influenced by team total of each individual stat. Means if quest requires 30 STR and 
team total is lower, reduce percentage of success. If higher, increase probability. (???)
* Each fight/quest has description and stat requirements + percentage of success. (??)
* We either find a way to randomize fight/quest or code in our own fight/quest. (???)
* Fight a predetermined enemy team of Heroes or random team of Heroes with difficulty levels seperating them. (???)
* Loot a random Hero. (???)
* Lose a Hero if HP is implemented. (???)
* Hit and miss percentages. (????)
* Code picks random Hero on opposing side to attack. (????)
* Code determines order of Heroes actions for that turn. (????)
* Show each turn including damage taken and dealt. (????)
* Includes indentations. (????)
* If Hero is knocked out, remove their place in the order and move everyone else forward. (????)
	Ex) ----------------------------------------------------
		Your Team                     Enemy Team
		Lucina: 10/14                 Luigi:       5/10           
		Kirby:  8/19                  Donkey Kong: 6/12
		Mario:  13/13
		Turn 1: Lucina deals 7 damage to Enemy Donkey Kong.
				Enemy Donkey Kong dies.
				Mario deals 4 damage to Luigi.
				Luigi deals 3 damage to Lucina.
				Kirby misses.
		Press any key to continue...
		----------------------------------------------------
		Your Team                     Enemy Team
		Lucina: 7/14                  Luigi:       1/10           
		Kirby:  8/19                  Donkey Kong: 0/12
		Mario:  13/13
		Turn 2: etc etc etc.
		Press any key to continue...
		
********	View Collection of Heroes	********
* Store Heroes in Binary Search Tree for easy sort,adding, and removal.
* View by page due to many Heroes in collection. (??)
* View information on all Heroes. (??)

********	Search Collection for a certain Hero	********
* Might be incorporated into View Collection of Heroes menu option.
* Search by name...
* or by hash. (?)
* Search from List of classes and returns list of Heroes with same class.

********	Delete a certain Hero from Collection	********
* Might be incorporated into View Collection of Heroes menu option.
* Delete Hero from Binary Search Tree and balance out the Tree by moving appropiate elements.
* If duplicate, deal with it appropiately. (??)	

********	Exit	********
* Save progress and collection to external file. 





********	Random Things here	********
* Clear screen after option to avoid clutter.
	
	
	
	
	
	
	
	
	
