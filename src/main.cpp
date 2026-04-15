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

    void takeAction(Entity& to) {
	Ability ability = heldWeapon->getRandomAbility();
	ability.action(*this, to);
	std::cout << name << " " << ability.verb << " with the " << heldWeapon->name << " (" << ability.effect << ").\n";
    };
};


// ENTITY _ ENTITY with the _. (_)


int main() {
    Weapon stick{"twig"};
    stick.abilityList = {
	{"swung", "Dealt 1 damage", [](Entity& from, Entity& to){ to.health -= 1; }},
    };

    Weapon sword{"Sword"};
    sword.abilityList = {
	{"Hit", "Dealth 5 damage",[](Entity& from, Entity& to){ to.health -= 5; }},
	{"Hit", "Dealth 5 damage",[](Entity& from, Entity& to){ to.health -= 5; }},
	{"Hit", "Dealth 5 damage",[](Entity& from, Entity& to){ to.health -= 5; }},
	{"Hit", "Dealth 5 damage",[](Entity& from, Entity& to){ to.health -= 5; }},
	{"Missed and hurt itself", "Dealt 2 damage", [](Entity& from, Entity& to){ from.health -= 2; }},
	{"Missed", "Did nothing", [](Entity& from, Entity& to){ }},
    };

    Entity player {"Player", 100, &sword};
    Entity basicEnemy {"Enemy", 10, &stick};
    Entity strongEnemy {"Strong Enemy", 25, &sword};


    Entity activeEnemy = basicEnemy;

    bool isGameActive = true;
    while(isGameActive) {

	if(activeEnemy.health <= 0) {
	    std::cout << "The enemy has died.\n";
	    activeEnemy = strongEnemy;
	};

	player.takeAction(activeEnemy);
	activeEnemy.takeAction(player);
	std::cout << "Player HP: " << player.health << " | Enemy HP: " << activeEnemy.health << "\n";

	if(activeEnemy.health <= 0) {
	    std::cout << "The enemy has died.\n";
	    activeEnemy = strongEnemy;
	};






	std::cin.get();
    };


    return 0;
}
