# ECS-dungeon-game
Our ECS Game

# Game Description:

{Game Name} is a rogue-like dungeon rpg which the player are stuck in
a infinate loop dungeon which have no hope to escape and the only thing for them to
do is to survive as long as possible before they meet their inevitable end.

# How the game works:

Text based dungeon crawler / rouge like game with scoring system where the player will advance through rooms where
each time the player advances there will be three possibilities : an empty room, a room with a chest that can give 
extra points, a healing potion, or an armor that has only one use and then breaks, or a room with a monster.

There will be three types of monsters : a big monster: Tank that deals a lot of damage but is slow, a smaller 
monster: assassin that deals low damage but is fast, and a ranger that can only be damage by arrows.

The player will have three weapon options to deal with the monster in the room depending on the monster, 
a sword that counters the big monster, daggers that counters the small monster,
and bow and arrow that counters the ceiling monster.

Every time the player passes through a room they get points, the player gets extra points 
by opening a chest with points and by defeating a monster.



# Features:
-Procedurally Generated Dungeons: Every playthrough is unique with different layouts and challenges.

-Turn-Based Combat: Engage in strategic battles where every move matters.

-ECS Architecture: A modular system that separates data from behavior, allowing for easy expansion and maintenance.

# Controls:
-'W' 'A' 'S' 'D' to navigate the dungeon
# Scoring system:
- Player gets this quantity of points for doing these actions:
- 100 points if an enemy is defeates.
- 50 points if the player finds a chest.
- 10 points if the player goes to an empty room.
# Combat system:
- The player chooses a weapon that is on their inventory to attack (swords can damage tanks, bows can damage rangers and daggers can damage assasins).
- The number of damage from the player's weapon is substracted from the enemy's health and the amount of damage than the enemy does is substracted from, the player's health.
- This goes until either the enemy or the player dies.



