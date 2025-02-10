Hello,

This is a simple dungeon crawler type game that I made. It's quite simple, but was a lot of fun to make, and honestly a good amount of fun to play as well.
The premise is simple.

The Dungeon: The map is procedurally generated, meaning that every time you launch the game, the map will look completely different. The map is a 50 X 50 grid
which comprises of empty spaces '.', walls '#', loot 'l', food 'f', enemies 'e', an extraction point (x), and your player character 'p'.

Your character (p): Your character, notated by the lowercase letter 'p', can move up, down, left, and right, controlled by (wasd) on a keyboard. Your spawn
is completely random, and you spawn with 20 HP and an empty inventory. Your player can attack enemies, dealing +1 damage.

Enemies (e): A random number of enemies will spawn each time you launch the game. Their spawn points will be completely random. They can only spot you if you
are within a certain distance, at which point they will chase you. If you are not within their range of sight, they will wonder around the dungeon randomly.
Enemies have 10 HP and can deal +3 attack damage. Each time the game launches, one enemy will be randomly selected to be the carrier of the key. If that enemy
is killed, then the player character will receive the key to their inventory.

Walls (w): A random number of walls will spawn each time you launch the game, and their spawn points will be completely random. Walls cannot be travelled through,
whether by your player character, or by enemies.

Loot (l): A random number of loot will spawn each time you launch the game. Their spawn points will be completely random. Loot spaces can only be occupied by your 
player character and not by enemies. If the player moves over a space on the dungeon grid which is currently occupied by loot, then the player will receive that
loot to their inventory and the loot will then dissapear from the map. Each loot has a random chance of being one of several items, a small sword, a long sword,
a weak shield, or a strong shield.

Weapons: A small sword will enable the player to deal +3 attack damage against enemies. A large sword will enable the player to deal +5 attack damage against enemies.
If the player has both a small sword and a large sword, the large sword will automatically default to the player's current weapon.

Defenses: Each time the player is hit by an enemy, if they are currently wielding a weak shield, there is a 50% chance that the weak shield will negate the damage default
by 1. If the player is wielding a strong shield, then the damage dealt by enemies is always negated by 1. If the player has both a weak shield and a strong shield, the 
strong shield will automatically default to the player's current defense.

Combat: If a player has an enemy adjascent to them, then the player can choose to move their player character in the direction of said enemy. Neither the player nor the
enemy will move and will instead engage in combat. Each time this event occurs, the player has a 50% chance of landing an attack on the enemy, or the enemy landing an attack
on the player. If the player is hit by the enemy, then the amount of damage dealt is dependent upon which shield, if any, is currently wielded by the player character.
Inversely, if the enemy is hit by the player, then the amount of damage dealt is dependent upon which sword, if any, is currently wielded by the player character.

Food (f): A random number of food will spawn each time you launch the game. Their spawn points will be completely random. Food spaces can only be occupied by your
player character and not by enemies. If the player moves over a space on the dungeon grid which is currently occupied by food, then the player will receive that
food and the loot will then dissapear from the map. Each food has a random chance of regenerating the player's HP by either 1, 2, or 3.

Extraction (x): There will be exactly one extraction point which will spawn at a random location each time you launch the game. The extraction point's space can only be occupied
by the player character and not by enemies. The extraction point can be occupied by the player at any point during the game, but extraction is not possible unless the player has
the key. If the player chooses to move their player character into the space occupied by the extraction point while having the key in their inventory, then the game will end as
the player character has successfully been extracted.

Objective: Survival, of course... Don't be killed by the enemies, you silly goose... Defeat the enemies by any means necessary until retreaving the key, then reach the extraction
point and exit the dungeon.