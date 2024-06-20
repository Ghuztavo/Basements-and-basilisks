#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include <vector>

class Entity;

//Components that will be used to create entities
class Component {
public:
	Component() {}
	virtual ~Component() {}
};

class Health : public Component {
public:
	Health(int health) : health(health) {}
	int health;
};

class Position : public Component {
public:
	Position(int x, int y) : x(x), y(y) {}
	int x, y;
};

class Damage : public Component {
public:
	Damage(int damage) : damage(damage) {}
	int damage;
};

class Armor : public Component {
public:
	Armor(bool hasArmor) : hasArmor(hasArmor) {}
	bool hasArmor;
};

class Inventory : public Component {
public:
	std::vector<Entity*> weapons;
	int healingPotions;
	int armor;

	Inventory(std::vector<Entity*> weapons, int healingPotions, int armor)
		: weapons(weapons), healingPotions(healingPotions), armor(armor) {}
};

class Score : public Component {
public:
	int score;
	Score(int score) : score(score) {}
};

//component that will only indicate that there is a monster in the room
class Monster : public Component {
public:
	bool monster;
	Monster(bool monster) : monster(monster) {}
};

//component that will only indicate that there is a chest in the room
class Chest : public Component {
public:
	bool chest;
	Chest(bool chest) : chest(chest) {}
};

//Entity class to create entities with components
class Entity {
private:
	std::vector<Component*> components;
	int id;
	std::string name;

public:
	Entity(int id, std::string name) : id(id), name(name) {}

	~Entity() {
		for (auto component : components) {
			delete component;
		}
	}

	void addComponent(Component* component) {
		components.push_back(component);
	}

	template <typename T>
	T* getComponent() {
		for (auto component : components) {
			if (T* t = dynamic_cast<T*>(component)) {
				return t;
			}
		}
		return nullptr;
	}

	int getId() {
		return id;
	}

	std::string getName() {
		return name;
	}
};