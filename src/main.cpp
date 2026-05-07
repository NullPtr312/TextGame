#include "classes.hpp"
#include "game.hpp"

int main() {

	//GAME SETUP ---------
	//Status Effects
	srand(time(NULL));

	StatusEffect onFire{ "burned", [](Entity& e) { e.health -= 1; } };
	StatusEffect poisoned{ "poisoned", [](Entity& e) { e.health -= 5 - e.statusTimer; } };
	StatusEffect cursed{ "is cursed", [](Entity& e) { e.health -= 3; } };
	StatusEffect regen{ "healing", [](Entity& e) { e.health += e.statusTimer; } };
	StatusEffect quartered{ "quartered", [](Entity& e) { e.health = (int) ((float)e.health * 0.75); } };

	//Weapons
	Weapon debug{ "debug" };
	debug.abilityList = {
	{"ERROR", "ERROR", [](Entity& from, Entity& to) { std::cout << "THIS SHOULD NOT HAPPEN! SOMETHING HAS GONE WRONG"; }}
	};

	Weapon stick{ "Twig" };
	stick.abilityList = {
	{"Whiffed", "Did nothing",[](Entity& from, Entity& to) { to.health -= 0; }},
	};

	Weapon rustedSword{ "Rusted Sword" };
	rustedSword.abilityList = {
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to) { to.health -= 3; }},
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to) { to.health -= 3; }},
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to) { to.health -= 3; }},
	{"Slipped and hurt itself", "Dealt 2 damage",[](Entity& from, Entity& to) { from.health -= 2; }},
	{"Missed", "Did nothing",[](Entity& from, Entity& to) {}},
	};

	Weapon knife{ "Knife" };
	knife.abilityList = {
	{"Stabbed", "Dealt 2 damage",[](Entity& from, Entity& to) { to.health -= 2; }},
	};

	Weapon dagger{ "Dagger" };
	dagger.abilityList = {
	{"Stabbed", "Dealt 4 damage",[](Entity& from, Entity& to) { to.health -= 4; }},
	};

	Weapon massiveSword{ "Massive Sword" };
	massiveSword.abilityList = {
	{"Slammed", "Dealt 8 damage",[](Entity& from, Entity& to) { to.health -= 8; }},
	{"Missed", "Did nothing",[](Entity& from, Entity& to) {}},
	{"Missed", "Did nothing",[](Entity& from, Entity& to) {}},
	};

	Weapon leechBlade{ "Leech Blade" };
	leechBlade.abilityList = {
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to) { to.health -= 3; }},
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to) { to.health -= 3; }},
	{"Leeched", "Stole 2 health",[](Entity& from, Entity& to) { to.health -= 2; from.health += 2; }},
	{"Leeched", "Stole 2 health",[](Entity& from, Entity& to) { to.health -= 2; from.health += 2; }},
	{"Missed", "Did nothing",[](Entity& from, Entity& to) {}},
	};

	Weapon flameDagger{ "Fire Dagger" };
	flameDagger.abilityList = {
	{"Shanked", "Dealt 2 damage",[&onFire](Entity& from, Entity& to) { to.health -= 2; to.statusEffect = &onFire; to.statusTimer = 3; }},
	{"Shanked", "Dealt 3 damage",[&onFire](Entity& from, Entity& to) { to.health -= 3; to.statusEffect = &onFire; to.statusTimer = 2; }},
	};

	Weapon poisonNeedle{ "Poison Needle" };
	poisonNeedle.abilityList = {
	{"Pricked", "Dealt 1 damage",[&poisoned](Entity& from, Entity& to) { to.health -= 1; to.statusEffect = &poisoned; to.statusTimer = 4; }},
	};
	
	Weapon regenBlade{ "Regen Blade" };
	regenBlade.abilityList = {
	{"Swung", "Dealt 1 damage",[&regen](Entity& from, Entity& to) { to.health -= 1; from.statusEffect = &regen; to.statusTimer = 3; }},
	};

	Weapon snakeEyes{ "Snake Eyes" };
	snakeEyes.abilityList = {
	{"Rolled", "Dealt 1 damage",[](Entity& from, Entity& to) { to.health -= 1; }},
	{"Rolled", "Dealt 2 damage",[](Entity& from, Entity& to) { to.health -= 2; }},
	{"Rolled", "Dealt 3 damage",[](Entity& from, Entity& to) { to.health -= 3; }},
	{"Rolled", "Dealt 4 damage",[](Entity& from, Entity& to) { to.health -= 4; }},
	{"Rolled", "Dealt 5 damage",[](Entity& from, Entity& to) { to.health -= 5; }},
	{"Rolled", "Dealt 6 damage",[](Entity& from, Entity& to) { to.health -= 6; }},
	};

	Weapon cursedBlade{ "Cursed Blade" };
	cursedBlade.abilityList = {
	{"Missed", "Cursed the user",[&cursed](Entity& from, Entity& to) { from.statusEffect = &cursed; from.statusTimer = 2; }},
	{"Missed", "Cursed the user",[&cursed](Entity& from, Entity& to) { from.statusEffect = &cursed; from.statusTimer = 2; }},
	{"Missed", "Cursed the user",[&cursed](Entity& from, Entity& to) { from.statusEffect = &cursed; from.statusTimer = 2; }},
	{"Missed", "Cursed the user",[&cursed](Entity& from, Entity& to) { from.statusEffect = &cursed; from.statusTimer = 2; }},
	{"Missed", "Cursed the user",[&cursed](Entity& from, Entity& to) { from.statusEffect = &cursed; from.statusTimer = 2; }},
	{"Missed", "Cursed the user",[&cursed](Entity& from, Entity& to) { from.statusEffect = &cursed; from.statusTimer = 2; }},
	{"Missed", "Cursed the user",[&cursed](Entity& from, Entity& to) { from.statusEffect = &cursed; from.statusTimer = 2; }},
	{"Missed", "Cursed the user",[&cursed](Entity& from, Entity& to) { from.statusEffect = &cursed; from.statusTimer = 2; }},
	{"Missed", "Cursed the user",[&cursed](Entity& from, Entity& to) { from.statusEffect = &cursed; from.statusTimer = 2; }},
	{"Hit", "Killed the enemy",[](Entity& from, Entity& to) { to.health = 0; }},
	};

	Weapon healingPotion{ "Healing Potion" };
	healingPotion.abilityList = {
	{"Healed", "Healed the enemy",[](Entity& from, Entity& to) { to.health += 12; from.health = 0; }},
	};

	Weapon regenPotion{ "Regeneration Potion" };
	regenPotion.abilityList = {
	{"Applied regen", "Gave regen to the enemy",[&regen](Entity& from, Entity& to) { from.health = 0; to.statusEffect = &regen; to.statusTimer = 5; }},
	};

	Weapon devWeapon{ "The Dev Sword" };
	devWeapon.abilityList = {
	{"Killed", "Dealt all damage",[](Entity& from, Entity& to) { to.health = 0; from.health = 100; from.statusTimer = 0; }},
	};

	//Entities
	Entity player{ "Player", 100, &rustedSword, 0 };
	Entity lucio{ "Lucio", 5, &stick, 0 };
	Entity goblin{ "Goblin", 8, &debug, 1 };
	Entity frog{ "Dart Frog", 6, &debug, 1 };
	Entity ogre{ "Ogre", 18, &debug, 5 };
	Entity leech{ "Leech", 10, &debug, 2 };
	Entity mage{ "Goblin Mage", 12, &debug, 3 };
	Entity roller{ "High Roller", 13, &debug, 3 };
	Entity healer{ "Healer", 100, &debug, -1 };

	//Encounters
	Encounter goblinEncounter{ &goblin, {&rustedSword, &knife, &knife} };
	Encounter frogEncounter{ &frog, {&poisonNeedle} };
	Encounter ogreEncounter{ &ogre, {&massiveSword, &dagger} };
	Encounter leechEncounter{ &leech, {&leechBlade, &leechBlade, &leechBlade, &dagger} };
	Encounter mageEncounter{ &mage, {&flameDagger, &poisonNeedle, &flameDagger, &poisonNeedle, &regenBlade} };
	Encounter rollerEncounter{ &roller, {&snakeEyes} };
	Encounter healerEncounter{ &healer, {&healingPotion, &regenPotion} };

	std::vector<Encounter> encounterPool{ goblinEncounter, goblinEncounter, goblinEncounter, ogreEncounter, ogreEncounter, leechEncounter, leechEncounter, mageEncounter, mageEncounter, rollerEncounter, rollerEncounter, healerEncounter };

	Game game;
	game.encounterPool = std::move(encounterPool);
	game.activeEnemy = &lucio;
	game.player = &player;


	std::cout << "Welcome to your test of strength.\n";
	std::cout << "You enter the first level to face your opponent.\n\n";
	std::cout << "Lucio stands opposed to you, wielding a fierce weapon.\n";
	std::cout << "You have " << game.player->health << " HP and one life. Good luck. (Enter to continue)\n";
	std::cin.get();

	while(game.isGameActive) {
	    game.doGameLoop();
	}

	return 0;
}
