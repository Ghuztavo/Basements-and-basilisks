#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Components.h"
#include "Systems.h"
#include "EventHandling.h"

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    // Player initialization
    Position playerPosition = { 0, 0 };
    Health playerHealth = { 100 };
    Weapon playerWeapon = { "Basic Sword", 10, Weapon::Type::Sword };
    Armor playerArmor = { "Leather Armor", 5 };
    Experience playerExperience = { 0 };
    Level playerLevel = { 1 };
    Mana playerMana = { 50 };
    Skill playerSkill = { "Fireball", 20, 10 }; // Skill name, damage, mana cost
    int score = 0;
    int healthPotions = 0;

    // Inventory system initialization
    InventorySystem inventorySystem(playerWeapon, playerArmor, healthPotions);
    inventorySystem.initializeItems();

    // Combat system initialization
    CombatSystem combatSystem(playerHealth.hp, playerWeapon, playerArmor, score, healthPotions, playerMana.mana);

    // Track previous position to detect movement to a new room
    Position previousPosition = playerPosition;

    // Game loop
    bool running = true;
    while (running) {
        // Display player status
        std::cout << "Player Position: (" << playerPosition.x << ", " << playerPosition.y << ")\n";
        std::cout << "Player Health: " << playerHealth.hp << "\n";
        std::cout << "Player Mana: " << playerMana.mana << "\n";
        std::cout << "Player Experience: " << playerExperience.exp << "\n";
        std::cout << "Player Level: " << playerLevel.level << "\n";
        std::cout << "Total Score: " << score << "\n";

        // Movement input
        char move;
        std::cout << "Move (w/a/s/d), Inventory (i), Quit (q): ";
        std::cin >> move;

        switch (move) {
        case 'w':
            MovementSystem::move(playerPosition, 0, 1);
            break;
        case 'a':
            MovementSystem::move(playerPosition, -1, 0);
            break;
        case 's':
            MovementSystem::move(playerPosition, 0, -1);
            break;
        case 'd':
            MovementSystem::move(playerPosition, 1, 0);
            break;
        case 'i':
            inventorySystem.printInventory();
            std::cout << "Change Weapon (w), Change Armor (a): ";
            char invChoice;
            std::cin >> invChoice;
            if (invChoice == 'w') {
                inventorySystem.changeWeapon();
            }
            else if (invChoice == 'a') {
                inventorySystem.changeArmor();
            }
            continue; // Skip event handling and continue to next iteration
        case 'q':
            running = false;
            continue; // Skip event handling and exit loop
        default:
            std::cout << "Invalid input.\n";
            continue; // Skip event handling and continue to next iteration
        }

        // Check if player moved to a new room
        if (playerPosition.x != previousPosition.x || playerPosition.y != previousPosition.y) {
            ScoringSystem::updateScore(score, 100); // Update score for moving to a new room
            std::cout << "You moved to a new room! +100 points\n";
            previousPosition = playerPosition; // Update previous position
        }

        // Event handling after moving
        int eventChance = rand() % 100;
        if (eventChance < 40) {
            // 40% chance of encountering an enemy
            Entity enemy = EventHandling::generateRandomEnemy();
            std::cout << "An enemy appeared!\n";
            combatSystem.combat(enemy);
        }
        else if (eventChance < 60) {
            // 20% chance of finding a chest
            inventorySystem.handleChestEvent();
        }
        else {
            std::cout << "Nothing happened.\n";
        }

        if (playerHealth.hp <= 0) {
            running = false;
        }

        // Level up system
        LevelSystem::checkLevelUp(playerExperience, playerLevel, playerHealth, playerMana);
    }

    std::cout << "Game over! Your final score: " << score << "\n";
    return 0;
}
