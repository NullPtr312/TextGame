#pragma once
#include "classes.hpp"

class Game {
public:

    std::vector<Encounter> encounterPool;

    Entity* activeEnemy;
    Entity* player;

    void displayInitMessage() {
	std::cout << "Welcome to your test of strength.\n";
	std::cout << "You enter the first level to face your opponent.\n\n";
	std::cout << "Lucio stands opposed to you, wielding a fierce weapon.\n";
	std::cout << "You have " << player->health << " HP and one life. Good luck. (Enter to continue)\n";
	std::cin.get();
    }

    bool isGameActive = true;

    void doGameLoop() {

	player->takeAction(*activeEnemy);
	if (!(activeEnemy->health <= 0))
	    activeEnemy->takeAction(*player);
	std::cout << "Player HP: " << player->health << " | Enemy HP: " << activeEnemy->health << "\n";

	if (player->health <= 0) {
	    std::cout << "\n\nYou have failed in your quest to defeat Lucio.\n";
	    std::cout << "You defeated " << " enemies in your short-lived lifespan.\n";
	    std::cout << "Let it be known to all that you are not worthy of text based games.\n";
	    std::cin.get();
	    isGameActive = false;
	    return;
	}

	if (activeEnemy->health <= 0) {
	    std::cout << "The enemy has died.\n";
	    std::cout << "Would you like to steal their weapon? (" << activeEnemy->heldWeapon->name << ")\n(y/n)";

	    char c;
	    bool accepted = false;
	    while (!accepted) {
		std::cin >> c;
		switch (c) {
		    case 'y':
			std::cout << "You take the " << activeEnemy->heldWeapon->name << ".\n";
			player->heldWeapon = activeEnemy->heldWeapon;
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

	    for (int i = 1; i <= 3; i++) {
		int encounterIndex = rand() % encounterPool.size();
		Encounter e = encounterPool[encounterIndex];
		encounterChoices.push_back(e);

		std::cout << i << ": A " << e.enemy->name << ".\n";
	    };

	    std::cout << "Who would you like to fight? (1-3): ";

	    accepted = false;
	    while (!accepted) {
		std::cin >> c;

		switch (c) {
		    case '1':
			std::cout << "You take the left path.\n";
			activeEnemy = (encounterChoices[0].generateEnemy());
			accepted = true;
			break;

		    case '2':
			std::cout << "You take the middle path.\n";
			activeEnemy = (encounterChoices[1].generateEnemy());
			accepted = true;
			break;

		    case '3':
			std::cout << "You take the right path.\n";
			activeEnemy = (encounterChoices[2].generateEnemy());
			accepted = true;
			break;

		    default:
			std::cout << "Useless.\n";
		}
	    };

	    std::cin.get();
	    std::cout << "A " << activeEnemy->health << " HP " << activeEnemy->name << " blocks your path wielding a " << activeEnemy->heldWeapon->name << "!\n";
	};

	std::cin.get();
    }

};

