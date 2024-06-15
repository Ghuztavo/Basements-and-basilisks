#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <string>
#include <vector>

// Entity Types
enum class EntityType {
    Zombie,
    Skeleton,
    Wolf,
    Goblin
};

// Health Component
struct Health {
    int hp;
};

// Position Component
struct Position {
    int x;
    int y;
};

// Weapon Struct
struct Weapon {
    std::string name;
    int attack;
    enum class Type {
        Sword,
        Mace
    } type;
};

// Armor Struct
struct Armor {
    std::string name;
    int defense;
};

// Experience Component
struct Experience {
    int exp;
};

// Level Component
struct Level {
    int level;
};

// Mana Component
struct Mana {
    int mana;
};

// Skill Struct
struct Skill {
    std::string name;
    int damage;
    int manaCost;
};

// Entity Struct
struct Entity {
    EntityType type;
    Position position;
    Health health;
};

#endif // COMPONENTS_H
