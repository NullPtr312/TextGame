#pragma once

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
		action(action) {
	};
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

	Entity(std::string name, int health, Weapon* weapon) : name(name), health(health), heldWeapon(weapon) {};

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
		if (statusTimer <= 0) return;
		statusTimer--;
		statusEffect->effect(*this);
		if (statusTimer == 1)
			std::cout << name << " " << statusEffect->verb << " (" << statusTimer << " turn left).\n";
		else
			std::cout << name << " " << statusEffect->verb << " (" << statusTimer << " turns left).\n";
	};
};


struct Encounter {
	Entity* enemy;
	std::vector<Weapon*> weaponSelections;

	Entity* generateEnemy() {
		int weaponIndex = rand() % weaponSelections.size();
		enemy->heldWeapon = weaponSelections[weaponIndex];
		enemy->health *= 1 + (float(rand() % 100) / 200.0);
		return enemy;
	}
};


