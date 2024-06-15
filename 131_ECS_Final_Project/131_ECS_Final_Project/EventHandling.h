#ifndef EVENTHANDLING_H
#define EVENTHANDLING_H

#include "Components.h"
#include <cstdlib>

class EventHandling {
public:
    static Entity generateRandomEnemy() {
        EntityType type = static_cast<EntityType>(rand() % 4);
        int hp;
        switch (type) {
        case EntityType::Zombie:
            hp = rand() % 51 + 100; // Random HP between 100 and 150
            break;
        case EntityType::Skeleton:
            hp = rand() % 51 + 50;  // Random HP between 50 and 100
            break;
        case EntityType::Wolf:
            hp = rand() % 31 + 70;  // Random HP between 70 and 100
            break;
        case EntityType::Goblin:
            hp = rand() % 41 + 60;  // Random HP between 60 and 100
            break;
        }
        Position position = { 0, 0 }; // Default position for enemies (could be randomized)

        return Entity{ type, position, {hp} };
    }
};

#endif // EVENTHANDLING_H
