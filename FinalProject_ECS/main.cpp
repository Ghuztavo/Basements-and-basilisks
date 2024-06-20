// Gustavo, Santiago, Jack
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include <vector>

#include "Systems.h"

//Text based dungeon crawler / rouge like game with scoring system where the player will advance through rooms where
//each time the player advances there will be three possibilities : an empty room, a room with a chest that can give extra points, a healing potion, or an armor that has only one use and then breaks,
//or a room with a monster.
//There will be three types of monsters : a big monster that deals a lot of damage but is slow, a smaller monster that deals low damage but is fast, and a ceiling monster.
//The player will have three weapon options to deal with the monster in the room depending on the monster, a sword that counters the big monster, daggers that counters the small monster,
//and bow and arrow that counters the ceiling monster.
//Every time the player passes through a room they get points, the player gets extra points by opening a chest with points and by defeating a monster.

int main() {
	srand(static_cast<unsigned>(time(0)));
	Game game;
	game.start();
	return 0;
}