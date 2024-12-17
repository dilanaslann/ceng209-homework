# ceng209-homework
23050121004
Dilan Aslan

Dungeon Adventure Game
About the Game:
Dungeon Adventure is an adventure game. The player can explore different rooms in the dungeon to collect items, fight against enemies, and use the correct commands to progress in the game.

Commands:
look: Examine the room.
move <direction>: Move in room directions (up: u, down: d, left: l, right: r).
pickup <item>: Take the item found in the room to your inventory.
drop <item>: Leave the item from your inventory in the room.
attack: Attack the enemy in the room.
save: Save the game.
load: Load the saved game.
stats: Shows player health and power information.
exit: End the game.

Code Descriptions:
Player Struct: Stores player's health, power and inventory information.
Room Struct: Contains room descriptions, items and enemies in the room, and transitions between rooms.
Item Struct: Defines items owned by the player and rooms.
Creature Struct: Defines enemies (monsters) placed in the room.
