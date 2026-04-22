

	//Weapons
	Weapon debug{ "debug" };
	debug.abilityList = {
	{"ERROR", "ERROR", [](Entity& from, Entity& to) { std::cout << "THIS SHOULD NOT HAPPEN! SOMETHING HAS GONE WRONG"; }}
	};

	Weapon stick{ "Twig" };
	stick.abilityList = {
	{"Missed", "Did nothing", [](Entity& from, Entity& to) { to.health -= 0; }},
	};

	Weapon rustedSword{ "Rusted Sword" };
	rustedSword.abilityList = {
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to) { to.health -= 3; }},
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to) { to.health -= 3; }},
	{"Swung", "Dealt 3 damage",[](Entity& from, Entity& to) { to.health -= 3; }},
	{"Slipped and hurt itself", "Dealt 2 damage", [](Entity& from, Entity& to) { from.health -= 2; }},
	{"Missed", "Did nothing", [](Entity& from, Entity& to) {}},
	};

	Weapon massiveSword{ "Massive Sword" };
	massiveSword.abilityList = {
	{"Swung", "Dealth 8 damage",[](Entity& from, Entity& to) { to.health -= 8; }},
	{"Missed", "Did nothing",[](Entity& from, Entity& to) {}},
	{"Missed", "Did nothing",[](Entity& from, Entity& to) {}},
	};

	Weapon dagger{ "Dagger" };
	dagger.abilityList = {
	{"Stabbed", "Dealt 4 damage",[](Entity& from, Entity& to) { to.health -= 4; }},
	};

	Weapon flameDagger{ "Fire Dagger" };
	flameDagger.abilityList = {
	{"Stabbed", "Dealt 2 damage",[&onFire](Entity& from, Entity& to) { to.health -= 2; to.statusEffect = &onFire; to.statusTimer = 3; }},
	{"Stabbed", "Dealt 3 damage",[&onFire](Entity& from, Entity& to) { to.health -= 3; to.statusEffect = &onFire; to.statusTimer = 2; }},
	};
