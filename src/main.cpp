#include <iostream>
#include <functional>
#include <string>
#include <vector>

class Entity;

struct Ability {
public:
    std::string verb; // Smacked, Struck, Threw etc.
    std::string effect; // Dealt 4 damage, Dealt 2 damage, Healed 4 points
    std::function<void(Entity& from, Entity& to)> action;

    Ability(std::string verb, std::string effect, std::function<void(Entity& from, Entity& to)> action) :
	verb(verb),
	effect(effect),
	action(action) { };
};

class Weapon {
public:
    std::string name;
    std::vector<Ability> abilityList;

    Ability getRandomAbility() {
	int actionIndex = rand() % abilityList.size();
	return abilityList[actionIndex];
    };
};

struct StatusEffect {
    std::string verb; // Burned, healed, died, etc.
    std::function<void(Entity& e)> effect;
};

class Entity {
public:

    Entity(std::string name, int health, Weapon* weapon) : name(name), health(health), heldWeapon(weapon) { };

    Entity(const Entity& other) : heldWeapon(other.heldWeapon) {
	name = other.name;
	health = other.health;
    };

    std::string name;
    int health;
    Weapon* heldWeapon;

    int statusTimer = 0; //If below zero, effect doesn't trigger
    StatusEffect* statusEffect;

    void takeAction(Entity& to) {
	Ability ability = heldWeapon->getRandomAbility();
	ability.action(*this, to);
	std::cout << name << " " << ability.verb << " with the " << heldWeapon->name << " (" << ability.effect << ").\n";

	//status
	if(statusTimer <= 0) return;
	statusTimer--;
	statusEffect->effect(*this);
	std::cout << name << " " << statusEffect->verb << ".\n"; 
    };
};


struct Encounter {
    Entity* enemy;
    std::vector<Weapon*> weaponSelections;

    Entity* generateEnemy() {
	int weaponIndex = rand() % weaponSelections.size();
	enemy->heldWeapon = weaponSelections[weaponIndex];
	return enemy;
    }
};



// ENTITY _ ENTITY with the _. (_)


int main() {

    //GAME SETUP ---------
    //Status Effects

    StatusEffect onFire {"burned", [](Entity& e){ e.health -= 1; }};
    StatusEffect cursed {"is cursed", [](Entity& e){ e.health -= 3; }};

    //Weapons
    Weapon debug{"debug"};
    debug.abilityList = {
	{"ERROR", "ERROR", [](Entity& from, Entity& to){ std::cout << "THIS SHOULD NOT HAPPEN! SOMETHING HAS GONE WRONG"; }}
    };

    Weapon stick{"Twig"};
    stick.abilityList = {
	{"swung", "Dealt 1 damage", [](Entity& from, Entity& to){ to.health -= 1; }},
    };

    Weapon rustedSword{"Rusted Sword"};
    rustedSword.abilityList = {
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to){ to.health -= 3; }},
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to){ to.health -= 3; }},
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to){ to.health -= 3; }},
	{"Slipped and hurt itself", "Dealt 2 damage", [](Entity& from, Entity& to){ from.health -= 2; }},
	{"Missed", "Did nothing", [](Entity& from, Entity& to){ }},
    };

    Weapon massiveSword{"Massive Sword"};
    massiveSword.abilityList = {
	{"Swung", "Dealth 8 damage",[](Entity& from, Entity& to){ to.health -= 8; }},
	{"Missed", "Did nothing",[](Entity& from, Entity& to){}},
	{"Missed", "Did nothing",[](Entity& from, Entity& to){}},
    };

    Weapon dagger{"Dagger"};
    dagger.abilityList = {
	{"Stabbed", "Dealt 4 damage",[](Entity& from, Entity& to){ to.health -= 4; }},
    };

    Weapon flameDagger{"Fire Dagger"};
    flameDagger.abilityList = {
	{"Stabbed", "Dealt 2 damage",[&onFire](Entity& from, Entity& to){ to.health -= 2; to.statusEffect = &onFire; to.statusTimer = 2; }},
	{"Stabbed", "Dealt 3 damage",[&onFire](Entity& from, Entity& to){ to.health -= 3; to.statusEffect = &onFire; to.statusTimer = 3; }},
    };




    //Entities
    Entity player {"Player", 100, &rustedSword};
    Entity basicEnemy {"Weak Enemy", 5, &debug};
    Entity strongEnemy {"Strong Enemy", 15, &debug};

    //Encounters
    Encounter tutorialEncounter {&basicEnemy, {&flameDagger}};

    Encounter basicEncounter {&basicEnemy, {&stick, &rustedSword}};
    Encounter strongEncounter {&strongEnemy, {&rustedSword, &massiveSword, &dagger}};

    std::vector<Encounter> encounterPool {basicEncounter, strongEncounter};

    Entity activeEnemy = *tutorialEncounter.generateEnemy();


    //GAME LOOP ----------
    bool isGameActive = true;
    while(isGameActive) {

	if(activeEnemy.health <= 0) {
	    std::cout << "The " << activeEnemy.name << " has died.\n";
	    std::cout << "The path forward has three enemies.\n";
	    activeEnemy = strongEnemy;
	};

	player.takeAction(activeEnemy);
	if(!(activeEnemy.health <= 0))
	    activeEnemy.takeAction(player);
	std::cout << "Player HP: " << player.health << " | Enemy HP: " << activeEnemy.health << "\n";

	if(activeEnemy.health <= 0) {
	    std::cout << "The enemy has died.\n";
	    std::cout << "Would you like to steal it's weapon? (" << activeEnemy.heldWeapon->name << ")\n(y/n)";
	    
	    char c;
	    bool accepted = false;
	    while (!accepted) {
		std::cin >> c;
		switch(c) {
		    case 'y':
			std::cout << "You take the " << activeEnemy.heldWeapon->name << ".\n";
			player.heldWeapon = activeEnemy.heldWeapon;
			accepted = true;
			break;
		    case 'n':
			accepted = true;
			break;

		    default:
			std::cout << "Invalid character\n";
		}
	    }
	   

	    std::cout << "The path branches into three:\n";

	    std::vector<Encounter> encounterChoices;

	    for(int i = 1; i <= 3; i++) {
		int encounterIndex = rand() % encounterPool.size();
		Encounter e = encounterPool[encounterIndex];
		encounterChoices.push_back(e);

		std::cout << i << ": A " << e.enemy->name << ".\n";
	    };

	    std::cout << "Who would you like to fight? (1-3): ";
	    
	    accepted = false;
	    while (!accepted) {
		std::cin >> c;

		switch(c) {
		    case '1': 
			std::cout << "You take the left path.\n";
			activeEnemy = *(encounterChoices[0].generateEnemy());
			accepted = true;
			break;

		    case '2': 
			std::cout << "You take the middle path.\n";
			activeEnemy = *(encounterChoices[1].generateEnemy());
			accepted = true;
			break;

		    case '3': 
			std::cout << "You take the right path.\n";
			activeEnemy = *(encounterChoices[2].generateEnemy());
			accepted = true;
			break;

		    default:
			std::cout << "Invalid choice\n";
		}
	    };

	    std::cin.get();
	    std::cout << "A " << activeEnemy.name << " blocks your path wielding a " << activeEnemy.heldWeapon->name << "!\n";
	};

	std::cin.get();
    };


    return 0;
}
