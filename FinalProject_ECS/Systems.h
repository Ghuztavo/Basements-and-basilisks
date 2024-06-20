#pragma once

#include "Components.h"

//System to handle the movement of the player with WASD keys, 
// if the player hits w the position of the player will increase by 1 in the y axis, if the player hits s the position of the player will decrease by 1 in the y axis
class MovementSystem {

public:
	void movePlayer(Entity* player, char direction) {

		Position* position = player->getComponent<Position>();
		if (direction == 'w' || direction == 'W') {
			position->y++;
		}
		else if (direction == 's' || direction == 'S') {
			position->y--;
		}
		else if (direction == 'a' || direction == 'A') {
			position->x--;
		}
		else if (direction == 'd' || direction == 'D') {
			position->x++;
		}
	}

};

//System to handle the room generation, if the player moves to a new room, the room will be generated with a random number between 1 and 3, 
// if the number is 1 the room will be empty, if the number is 2 the room will have a chest, 
// and if the number is 3 the room will have a monster
class RoomGenerationSystem {
public:
	Entity* generateRoom() {
		int roomType = rand() % 3 + 1;
		if (roomType == 1) {
			Entity* room = new Entity(3, "Empty");
			return room;

		}
		else if (roomType == 2) {
			Entity* room = new Entity(3, "Chest");
			room->addComponent(new Chest(true));
			return room;
		}
		else if (roomType == 3) {
			Entity* room = new Entity(3, "Monster");
			room->addComponent(new Monster(true));
			return room;
		}
		return nullptr;
	}
};

//System to generate a monster with a random type (tank, assassin, or ranger)
class GenerateMonster {
public:
	Entity* createMonster() {
		int monsterType = rand() % 3 + 1;
		if (monsterType == 1) {
			Entity* monster = new Entity(2, "Tank");
			monster->addComponent(new Health(100));
			monster->addComponent(new Damage(20));
			return monster;
		}
		else if (monsterType == 2) {
			Entity* monster = new Entity(2, "Assassin");
			monster->addComponent(new Health(50));
			monster->addComponent(new Damage(10));
			return monster;
		}
		else if (monsterType == 3) {
			Entity* monster = new Entity(2, "Ranger");
			monster->addComponent(new Health(75));
			monster->addComponent(new Damage(15));
			return monster;
		}
		return nullptr;
	}
};

//System to generate a chest with a random item (points, healing potion, or armor)
class GenerateChest {
public:
	Entity* createChest() {
		int chestType = rand() % 3 + 1;
		if (chestType == 1) {
			Entity* chest = new Entity(3, "Points");
			return chest;
		}
		else if (chestType == 2) {
			Entity* chest = new Entity(3, "Healing Potion");
			return chest;
		}
		else if (chestType == 3) {
			Entity* chest = new Entity(3, "Armor");
			return chest;
		}
		return nullptr;
	}
};

//system to handle combat, if the player is the attacker, the player will have to choose a weapon to attack the monster
//if the monster is the attacker, the monster will have damage attached to it and will attack the player

class CombatSystem {
public:

	//function in case the player is the attacker
	bool playerAttack(Entity* player, Entity* monster) {
		Inventory* inventory = player->getComponent<Inventory>();
		std::cout << "Choose your weapon:" << std::endl;
		for (size_t i = 0; i < inventory->weapons.size(); ++i) {
			std::cout << i + 1 << ". " << inventory->weapons[i]->getName() << std::endl;
		}

		int weaponChoice;
		std::cin >> weaponChoice;

		if (weaponChoice < 1 || weaponChoice > inventory->weapons.size()) {
			std::cout << "Invalid choice." << std::endl;
			return false;
		}

		Entity* weapon = inventory->weapons[weaponChoice - 1];
		std::string weaponName = weapon->getName();
		std::string monsterName = monster->getName();

		if ((weaponName == "Sword" && monsterName == "Tank") ||
			(weaponName == "Daggers" && monsterName == "Assassin") ||
			(weaponName == "Bow" && monsterName == "Ranger")) {

			Damage* playerDamage = weapon->getComponent<Damage>();
			Health* monsterHealth = monster->getComponent<Health>();
			monsterHealth->health -= playerDamage->damage;
			std::cout << "Player attacked " << monster->getName() << " with " << playerDamage->damage << " damage." << std::endl;
			return true;
		}
		else {
			std::cout << "Your " << weaponName << " is ineffective against the " << monsterName << "." << std::endl;
			monsterAttack(player, monster);
			return false;
		}
	}

	//function in case the monster is the attacker
	void monsterAttack(Entity* player, Entity* monster) {
		Damage* monsterDamage = monster->getComponent<Damage>();
		Health* playerHealth = player->getComponent<Health>();
		Armor* playerArmor = player->getComponent<Armor>();

		if (!monsterDamage || !playerHealth) {
			std::cout << "Error: Missing components." << std::endl;
			return;
		}

		int finalDamage = monsterDamage->damage;
		if (playerArmor->hasArmor) {
			finalDamage -= 50;
			playerArmor->hasArmor = false; // Armor breaks after one hit
			if (finalDamage < 0) finalDamage = 0;
		}

		playerHealth->health -= finalDamage;
		std::cout << monster->getName() << " attacked player with " << finalDamage << " damage." << std::endl;
	}
};

//System to create a weapon entity with a damage component
class WeaponSystem {
public:
	Entity* generateWeapon(std::string weapon, int damage) {
		Entity* weaponEntity = new Entity(4, weapon);
		weaponEntity->addComponent(new Damage(damage));
		return weaponEntity;
	}
};

//system to handle the main loop of the game,
//the player will have an inventory with three weapons, a sword, daggers, and a bow and arrow, the player will start with 0 potions with no armor
//the player will start with 0 points
//the player will start at position 0,0
//the player will have to move through the rooms with WASD keys
//the loop will continue until the player dies

class Game {
private:
	int maxHealth = 100;
	int maxArmor = 1;
	int maxPotions = 3;
	MovementSystem movementSystem;
	RoomGenerationSystem roomGenerationSystem;
	CombatSystem combatSystem;
	WeaponSystem weaponSystem;

public:
	void start() {
		// Player created and entities added to the player's entity
		Entity player(1, "Player");
		player.addComponent(new Health(maxHealth));
		player.addComponent(new Position(0, 0));
		player.addComponent(new Inventory({}, 0, 0));
		player.addComponent(new Score(0));
		player.addComponent(new Armor(false));

		// Create weapon entities and add them to the player's inventory
		player.getComponent<Inventory>()->weapons.push_back(weaponSystem.generateWeapon("Sword", 50));
		player.getComponent<Inventory>()->weapons.push_back(weaponSystem.generateWeapon("Daggers", 30));
		player.getComponent<Inventory>()->weapons.push_back(weaponSystem.generateWeapon("Bow", 40));

		bool continueGame = true;

		std::cout << "Press enter to start the game." << std::endl;
		std::cin.get();
		std::cout << "You are an adventurer exploring a dungeon... " << std::endl;
		std::cout << "there is no way out, and each room you enter will be more dangerous than the last... " << std::endl;
		std::cout << "the rooms are forever shifting... " << std::endl;
		std::cout << "collect as many points as you can before you meet your end " << std::endl;

		// Main game loop
		while (continueGame) {
			char direction;
			while (true) {
				Health* playerHealth = player.getComponent<Health>();
				if (playerHealth->health <= 0) {
					std::cout << "You died. Game Over." << std::endl;
					std::cout << "Final score: " << player.getComponent<Score>()->score << std::endl;
					std::cout << "Play again? (y/n): ";
					char playAgain;
					std::cin >> playAgain;
					if (playAgain == 'y' || playAgain == 'Y') {
						system("CLS");
						playerHealth->health = maxHealth;
						player.getComponent<Position>()->x = 0;
						player.getComponent<Position>()->y = 0;
						player.getComponent<Score>()->score = 0;
						player.getComponent<Inventory>()->healingPotions = 0;
						player.getComponent<Inventory>()->armor = 0;
						player.getComponent<Armor>()->hasArmor = false;
						continue;
					}
					else {
						continueGame = false;
						break;
					}
				}

				do {
					printStatus(&player);
					std::cin >> direction;
					if (direction != 'w' && direction != 'W' && direction != 'a' && direction != 'A' && direction != 's' && direction != 'S' && direction != 'd' && direction != 'D') {
						std::cout << "Invalid choice." << std::endl;
					}
					else {
						break;
					}
					
				} while (true);
				movementSystem.movePlayer(&player, direction);
				

				// The game will generate a room:
			// if the room is empty, the player will get points
			// if the room has a chest, it will generate a chest with a random item:
				// if the chest has gold, the player will get extra points
				// if the chest has a healing potion, the player will get a healing potion if the player has less than 3 potions
				// if the chest has armor, the player will get armor if the player doesn't have armor in the inventory
			// if the room has a monster, the game will generate a monster and the player will be able to choose if they want to use a healing potion, or use armor,
			// and then they can attack
			//they can also choose to run away but there will be a chance they can't run away
				Entity* roomEntity = roomGenerationSystem.generateRoom();

				if (roomEntity->getComponent<Monster>()) {
					Entity* monster = GenerateMonster().createMonster();
					if (monster)
						std::cout << "You encountered a " << monster->getName() << std::endl;
					//using a switch statement to handle the player's choice
					//if the player chooses to run away, there will be a 50% chance they can't run away
					//the loop will continue until the monster is defeated or the player runs away or dies

					bool monsterDefeated = false;
					while (!monsterDefeated) {
						if (playerHealth->health <= 0) {
							break;
						}
						std::cout << "Choose your action:" << std::endl;
						std::cout << "1. Attack " << std::endl;
						std::cout << "2. Use healing potion " << std::endl;
						std::cout << "3. Use armor" << std::endl;
						std::cout << "4. Run away " << std::endl;

						int choice;
						std::cin >> choice;

						switch (choice) {
						case 1:
							if (combatSystem.playerAttack(&player, monster)) {
								if (monster->getComponent<Health>()->health <= 0) {
									std::cout << "You defeated the " << monster->getName() << std::endl;
									monsterDefeated = true;
									player.getComponent<Score>()->score += 100;
								}
								else {
									combatSystem.monsterAttack(&player, monster);
								}
							}
							break;
						case 2:
							if (player.getComponent<Inventory>()->healingPotions > 0) {
								player.getComponent<Inventory>()->healingPotions--;
								player.getComponent<Health>()->health += 20;
								std::cout << "You used a healing potion. Player health: " << player.getComponent<Health>()->health << std::endl;
							}
							else {
								std::cout << "You don't have any healing potions." << std::endl;
							}
							break;
						case 3:
							if (player.getComponent<Inventory>()->armor > 0) {
								std::cout << "You used your armor." << std::endl;
								player.getComponent<Armor>()->hasArmor = true;
								player.getComponent<Inventory>()->armor--;
								continue;
							}
							else {
								std::cout << "You don't have any armor." << std::endl;
							}
							break;
						case 4:
							if (rand() % 2 == 0) {
								std::cout << "You ran away." << std::endl;
								monsterDefeated = true;
							}
							else {
								std::cout << "You couldn't run away." << std::endl;
								combatSystem.monsterAttack(&player, monster);
							}
							break;
						default:
							std::cout << "Invalid choice." << std::endl;
							break;
						}
					}

				}
				else if (roomEntity->getComponent<Chest>()) {
					Entity* chest = GenerateChest().createChest();
					if (chest->getName() == "Points") {
						player.getComponent<Score>()->score += 50;
						std::cout << "You found a chest with gold. Score: " << player.getComponent<Score>()->score << std::endl;
					}
					else if (chest->getName() == "Healing Potion") {
						if (player.getComponent<Inventory>()->healingPotions < maxPotions) {
							player.getComponent<Inventory>()->healingPotions++;
							std::cout << "You found a healing potion.  Potions: " << player.getComponent<Inventory>()->healingPotions << std::endl;
						}
						else {
							std::cout << "You already have the maximum number of healing potions." << std::endl;
						}
					}
					else if (chest->getName() == "Armor") {
						if (player.getComponent<Inventory>()->armor == 0) {
							player.getComponent<Inventory>()->armor++;
							std::cout << "You found armor." << std::endl;
						}
						else {
							std::cout << "You already have armor equiped." << std::endl;
						}
					}
				}
				else {
					player.getComponent<Score>()->score += 10;
					std::cout << "You entered an empty room. Score: " << player.getComponent<Score>()->score << std::endl;
				}
			}
		}
	}

	//function to print the player's status
	void printStatus(Entity* player) {
		std::cout << "Player health: " << player->getComponent<Health>()->health << std::endl;
		std::cout << "Player score: " << player->getComponent<Score>()->score << std::endl;
		std::cout << "Player position: (" << player->getComponent<Position>()->x << ", " << player->getComponent<Position>()->y << ")" << std::endl;
		std::cout << "Choose where to go [W] [A] [S] [D]: " << std::endl;
		std::cout << "--------------------------------------" << std::endl;
	}

	//function to print the player's inventory
	void printInventory(Entity* player) {
		Inventory* inventory = player->getComponent<Inventory>();
		std::cout << "Inventory:" << std::endl;
		std::cout << "- Weapons:" << std::endl;
		for (auto weapon : inventory->weapons) {
			std::cout << weapon->getName() << std::endl;
		}
		std::cout << "- Healing potions: " << inventory->healingPotions << std::endl;
		std::cout << "- Armor: " << inventory->armor << std::endl;
	};
};