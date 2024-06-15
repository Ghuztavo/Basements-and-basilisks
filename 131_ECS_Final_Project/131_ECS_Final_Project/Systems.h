#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Components.h"

class MovementSystem {
public:
    static void move(Position& position, int dx, int dy) {
        position.x += dx;
        position.y += dy;
    }
};

class ScoringSystem {
public:
    static void updateScore(int& score, int points) {
        score += points;
    }
};

class InventorySystem {
public:
    InventorySystem(Weapon& playerWeapon, Armor& playerArmor, int& healthPotions)
        : playerWeapon(playerWeapon), playerArmor(playerArmor), healthPotions(healthPotions) {}

    void initializeItems() {
        weapons = {
            {"Iron Sword", 15, Weapon::Type::Sword},
            {"Steel Sword", 25, Weapon::Type::Sword},
            {"Iron Mace", 15, Weapon::Type::Mace},
            {"Steel Mace", 25, Weapon::Type::Mace}
        };
        armors = {
            {"Iron Armor", 10},
            {"Steel Armor", 20}
        };
    }

    void printInventory() {
        std::cout << "Weapons:\n";
        for (size_t i = 0; i < weaponInventory.size(); ++i) {
            std::cout << i + 1 << ". " << weaponInventory[i].name << " (Attack: " << weaponInventory[i].attack << ")\n";
        }
        std::cout << "Armors:\n";
        for (size_t i = 0; i < armorInventory.size(); ++i) {
            std::cout << i + 1 << ". " << armorInventory[i].name << " (Defense: " << armorInventory[i].defense << ")\n";
        }
        std::cout << "Health Potions: " << healthPotions << "\n";
    }

    void handleChestEvent() {
        std::cout << "You found a chest! Open it? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            int itemType = rand() % 3;
            if (itemType == 0) {
                Weapon weapon = getRandomWeapon();
                weaponInventory.push_back(weapon);
                std::cout << "You found a " << weapon.name << " (Attack: " << weapon.attack << ")\n";
            }
            else if (itemType == 1) {
                Armor armor = getRandomArmor();
                armorInventory.push_back(armor);
                std::cout << "You found a " << armor.name << " (Defense: " << armor.defense << ")\n";
            }
            else {
                healthPotions++;
                std::cout << "You found a health potion!\n";
            }
        }
        else {
            std::cout << "You decided not to open the chest.\n";
        }
    }

    void changeWeapon() {
        std::cout << "Choose a weapon to equip (1-" << weaponInventory.size() << "): ";
        int choice;
        std::cin >> choice;
        if (choice > 0 && choice <= static_cast<int>(weaponInventory.size())) {
            playerWeapon = weaponInventory[choice - 1];
            std::cout << "You equipped " << playerWeapon.name << ".\n";
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }

    void changeArmor() {
        std::cout << "Choose an armor to equip (1-" << armorInventory.size() << "): ";
        int choice;
        std::cin >> choice;
        if (choice > 0 && choice <= static_cast<int>(armorInventory.size())) {
            playerArmor = armorInventory[choice - 1];
            std::cout << "You equipped " << playerArmor.name << ".\n";
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }

private:
    Weapon getRandomWeapon() {
        Weapon weapon = weapons[rand() % weapons.size()];
        weapon.attack = rand() % 26 + 5; // Random attack between 5 and 30
        return weapon;
    }

    Armor getRandomArmor() {
        Armor armor = armors[rand() % armors.size()];
        armor.defense = rand() % 21 + 5; // Random defense between 5 and 25
        return armor;
    }

    Weapon& playerWeapon;
    Armor& playerArmor;
    int& healthPotions;
    std::vector<Weapon> weapons;
    std::vector<Armor> armors;
    std::vector<Weapon> weaponInventory;
    std::vector<Armor> armorInventory;
};

class CombatSystem {
public:
    CombatSystem(int& playerHealth, Weapon& playerWeapon, Armor& playerArmor, int& score, int& healthPotions, int& playerMana)
        : playerHealth(playerHealth), playerWeapon(playerWeapon), playerArmor(playerArmor), score(score), healthPotions(healthPotions), playerMana(playerMana) {}

    void combat(Entity& enemy) {
        bool inCombat = true;

        while (inCombat) {
            std::cout << "Your Health: " << playerHealth << "\n";
            std::cout << "Your Mana: " << playerMana << "\n";
            std::cout << "Enemy Health: " << enemy.health.hp << "\n";

            std::cout << "Choose your action: (A)ttack, (D)rink potion, (S)kill, (E)scape: ";
            char action;
            std::cin >> action;

            switch (action) {
            case 'a':
            case 'A':
                playerAttacksEnemy(enemy);
                break;
            case 'd':
            case 'D':
                useHealthPotion();
                break;
            case 's':
            case 'S':
                useSkill(enemy);
                break;
            case 'e':
            case 'E':
                if (attemptEscape()) {
                    std::cout << "You successfully escaped!\n";
                    inCombat = false;
                }
                else {
                    std::cout << "Escape failed! The enemy attacks you.\n";
                    playerAttackedByEnemy(enemy);
                }
                break;
            default:
                std::cout << "Invalid action.\n";
                continue; // Skip enemy attack if invalid action
            }

            if (enemy.health.hp <= 0) {
                ScoringSystem::updateScore(score, 20); // Update total score
                std::cout << "You defeated the enemy! +20 points\n";
                inCombat = false;
            }

            if (inCombat && playerHealth > 0) {
                playerAttackedByEnemy(enemy);
            }

            if (playerHealth <= 0) {
                std::cout << "You have been defeated!\n";
                inCombat = false;
            }
        }
    }

private:
    int& playerHealth;
    Weapon& playerWeapon;
    Armor& playerArmor;
    int& score;
    int& healthPotions;
    int& playerMana;

    void playerAttacksEnemy(Entity& enemy) {
        int damage = playerWeapon.attack - rand() % 5;
        if (playerWeapon.type == Weapon::Type::Sword && enemy.type == EntityType::Zombie) {
            damage *= 2; // Sword does double damage to zombies
        }
        else if (playerWeapon.type == Weapon::Type::Mace && enemy.type == EntityType::Skeleton) {
            damage *= 2; // Mace does double damage to skeletons
        }
        enemy.health.hp -= damage;
        std::cout << "You attacked the enemy for " << damage << " damage.\n";
    }

    void useHealthPotion() {
        if (healthPotions > 0) {
            playerHealth += 20;
            healthPotions--;
            std::cout << "You used a health potion and restored 20 health points.\n";
        }
        else {
            std::cout << "You have no health potions left.\n";
        }
    }

    void useSkill(Entity& enemy) {
        Skill playerSkill = { "Fireball", 20, 10 }; // Example skill
        if (playerMana >= playerSkill.manaCost) {
            enemy.health.hp -= playerSkill.damage;
            playerMana -= playerSkill.manaCost;
            std::cout << "You used " << playerSkill.name << " for " << playerSkill.damage << " damage.\n";
        }
        else {
            std::cout << "Not enough mana to use " << playerSkill.name << ".\n";
        }
    }

    bool attemptEscape() {
        return rand() % 100 < 45; // 45% chance to escape
    }

    void playerAttackedByEnemy(Entity& enemy) {
        int damage;
        switch (enemy.type) {
        case EntityType::Zombie:
            damage = rand() % 11 + 5;
            break;
        case EntityType::Skeleton:
            damage = rand() % 6 + 10;
            break;
        case EntityType::Wolf:
            damage = rand() % 11 + 15;
            break;
        case EntityType::Goblin:
            damage = rand() % 11 + 10;
            break;
        }
        damage -= playerArmor.defense; // Reduce damage by player's armor defense
        damage = std::max(damage, 0); // Ensure damage is not negative
        playerHealth -= damage;
        std::cout << "The enemy attacked you for " << damage << " damage.\n";
    }
};

class LevelSystem {
public:
    static void checkLevelUp(Experience& playerExperience, Level& playerLevel, Health& playerHealth, Mana& playerMana) {
        int experienceNeeded = playerLevel.level * 100; // Example formula
        if (playerExperience.exp >= experienceNeeded) {
            playerLevel.level++;
            playerExperience.exp -= experienceNeeded;
            playerHealth.hp += 10; // Increase max health
            playerMana.mana += 5; // Increase max mana
            std::cout << "You leveled up! You are now level " << playerLevel.level << ".\n";
            std::cout << "Your max health increased to " << playerHealth.hp << " and your max mana increased to " << playerMana.mana << ".\n";
        }
    }
};

#endif // SYSTEMS_H
