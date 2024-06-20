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
- Procedurally Generated Dungeons: Every playthrough is unique with different layouts and challenges.

- Turn-Based Combat: Engage in strategic battles where every move matters.

- ECS Architecture: A modular system that separates data from behavior, allowing for easy expansion and maintenance.

# Controls:
'W' 'A' 'S' 'D' to navigate the dungeon
# Scoring system:
- Player gets this quantity of points for doing these actions:
- 100 points if an enemy is defeates.
- 50 points if the player finds a chest.
- 10 points if the player goes to an empty room.
# Combat system:
- The player chooses between attacking, using a healing potion, using armour or run away from the enemy.
- If player chooses a weapon that is on their inventory to attack (swords can damage tanks, bows can damage rangers and daggers can damage assasins).
- The number of damage from the player's weapon is substracted from the enemy's health and the amount of damage than the enemy does is substracted from, the player's health.
- If the player chooses healing potion the player is going to use a healing potion if they have one and health of the player is going to be restored. Then the healing potion breaks.
- If the player uses an armour the player is going to use the armour if they have one and they block 1 attack from the enemy. Then the armour breaks.
- If the player decides to escape the player is going to have a 50% chance to skip the fight and continue moving.
- This goes until either the enemy or the player dies or the player escapes.

# Entities:

When the main loop starts the player will be created as an entity with a series of comonents:
- health component
- position component
- armor component
- and inventory component: the inventory component will have a list of weapons which will be a vector of entities with damage component,
 a number of potions(a limit of 3) and number of armor (a limit of 1)

When the game start, a room entity will be created that will have the possibility to be an empty room which will return the entity empty, or
it can have a chest which will add the chest component to the room entity, or it can also have a monster which will add a monster component.

- If the room entity has a chest component, the game will then create a chest entity that will have the possibility to either have gold which means extra points,
or it can have a potion which will add a potion to the inventory of the player, or it can have armor which will add an armor to the inventory of the player.
- If the room entity has a monster component, the game will create a monster entity that can be of Tank type and it will add a health component and a damage component to it,
  the monster can also be an assassin type monster which will add the same components but with different numbers, or it can also be a ranger type monster which will be the same
  as the previous ones but again, with different numbers. The type of the monster is important for the combat of the game.



