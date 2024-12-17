#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 20
#define MAX_INVENTORY 5
#define MAX_COMMAND_LEN 100
#define MAX_DESC_LEN 256
#define SAVE_FILE "savefile.txt"  


typedef struct Item {
    char name[50];
} Item;

typedef struct Creature {
    char name[50];
    int health;
    int strength;
} Creature;

typedef struct Room {
    char description[MAX_DESC_LEN];
    Item *items[MAX_ITEMS];
    int itemCount;
    Creature *creature;
    struct Room *up;
    struct Room *down;
    struct Room *left;
    struct Room *right;
} Room;

typedef struct Player {
    int health;
    int strength;
    Item *inventory[MAX_INVENTORY];
    int inventoryCount;
} Player;


void initializePlayer(Player *player);
Room* createRoom(const char *description);
void setupRooms(Room **currentRoom);
void addItemToRoom(Room *room, const char *itemName);
void addCreatureToRoom(Room *room, const char *creatureName, int health, int strength);
void processCommand(const char *command, Player *player, Room **currentRoom);
void displayRoom(const Room *room, const Player *player);
void pickupItem(Player *player, Room *room, const char *itemName);
void dropItem(Player *player, Room *room, const char *itemName);
void attackCreature(Player *player, Room *room);
void saveGame(const Player *player, const Room *currentRoom);
Room* loadGame(Player *player);


void initializePlayer(Player *player) {
    player->health = 100;
    player->strength = 10;
    player->inventoryCount = 0;
    printf("\n[INFO] Player created! Health: %d, Strength: %d\n", player->health, player->strength);
}

Room* createRoom(const char *description) {
    Room *newRoom = (Room *)malloc(sizeof(Room));
    if (!newRoom) {
        perror("Failed to create room");
        exit(EXIT_FAILURE);
    }
    strncpy(newRoom->description, description, MAX_DESC_LEN);
    newRoom->itemCount = 0;
    newRoom->creature = NULL;
    newRoom->up = newRoom->down = newRoom->left = newRoom->right = NULL;
    return newRoom;
}

void setupRooms(Room **currentRoom) {
    Room *rooms[20];

    
    rooms[0] = createRoom("You are in a dark room with damp walls.");
    rooms[1] = createRoom("A torch-lit corridor with ancient inscriptions on the walls.");
    rooms[2] = createRoom("A mysterious library filled with old books and cobwebs.");
    rooms[3] = createRoom("A spacious hall with a high ceiling and a large chandelier.");
    rooms[4] = createRoom("A room filled with strange glowing crystals.");
    rooms[5] = createRoom("A cave-like chamber with an underground river.");
    rooms[6] = createRoom("A laboratory with alchemical tools scattered everywhere.");
    rooms[7] = createRoom("A garden with overgrown plants and eerie silence.");
    rooms[8] = createRoom("A treasury with chests of gold and jewels.");
    rooms[9] = createRoom("A dining hall with a long wooden table covered in dust.");
    rooms[10] = createRoom("A dungeon cell with rusted chains on the walls.");
    rooms[11] = createRoom("A hidden passageway with a faint breeze coming from the end.");
    rooms[12] = createRoom("A throne room with a massive, empty chair.");
    rooms[13] = createRoom("A workshop with broken tools and scattered parts.");
    rooms[14] = createRoom("A watchtower with windows overlooking the vast forest.");
    rooms[15] = createRoom("A room with a large map of the kingdom on the wall.");
    rooms[16] = createRoom("A chamber with a pool of clear, shimmering water.");
    rooms[17] = createRoom("A narrow staircase spiraling downwards into darkness.");
    rooms[18] = createRoom("A cavern with stalactites dripping water from above.");
    rooms[19] = createRoom("An ornate room with tapestries depicting legendary battles.");

    
    rooms[0]->right = rooms[1];
    rooms[1]->left = rooms[0];
    rooms[1]->up = rooms[2];
    rooms[2]->down = rooms[1];
    rooms[2]->right = rooms[3];
    rooms[3]->left = rooms[2];
    rooms[3]->down = rooms[4];
    rooms[4]->up = rooms[3];
    rooms[4]->right = rooms[5];
    rooms[5]->left = rooms[4];
    rooms[5]->down = rooms[6];
    rooms[6]->up = rooms[5];
    rooms[6]->right = rooms[7];
    rooms[7]->left = rooms[6];
    rooms[7]->down = rooms[8];
    rooms[8]->up = rooms[7];
    rooms[8]->left = rooms[9];
    rooms[9]->right = rooms[8];
    rooms[9]->up = rooms[10];
    rooms[10]->down = rooms[9];
    rooms[10]->right = rooms[11];
    rooms[11]->left = rooms[10];
    rooms[11]->up = rooms[12];
    rooms[12]->down = rooms[11];
    rooms[12]->right = rooms[13];
    rooms[13]->left = rooms[12];
    rooms[13]->up = rooms[14];
    rooms[14]->down = rooms[13];
    rooms[14]->right = rooms[15];
    rooms[15]->left = rooms[14];
    rooms[15]->up = rooms[16];
    rooms[16]->down = rooms[15];
    rooms[16]->right = rooms[17];
    rooms[17]->left = rooms[16];
    rooms[17]->up = rooms[18];
    rooms[18]->down = rooms[17];
    rooms[18]->right = rooms[19];
    rooms[19]->left = rooms[18];

    
    addItemToRoom(rooms[0], "Rusty Key");
    addItemToRoom(rooms[1], "Torch");
    addItemToRoom(rooms[2], "Ancient Book");
    addItemToRoom(rooms[3], "Golden Chalice");
    addItemToRoom(rooms[4], "Crystal Shard");
    addItemToRoom(rooms[5], "Fishing Rod");
    addItemToRoom(rooms[6], "Potion of Healing");
    addItemToRoom(rooms[7], "Mystic Flower");
    addItemToRoom(rooms[8], "Bag of Coins");
    addItemToRoom(rooms[9], "Dusty Plate");
    addItemToRoom(rooms[10], "Broken Chain");
    addItemToRoom(rooms[11], "Small Dagger");
    addItemToRoom(rooms[12], "Royal Crown");
    addItemToRoom(rooms[13], "Hammer");
    addItemToRoom(rooms[14], "Spyglass");
    addItemToRoom(rooms[15], "Quill and Ink");
    addItemToRoom(rooms[16], "Water Crystal");
    addItemToRoom(rooms[17], "Old Rope");
    addItemToRoom(rooms[18], "Carved Stone");
    addItemToRoom(rooms[19], "Tapestry Fragment");


    int zombieRooms[10];
    int zombieCount = 0;

    
    while (zombieCount < 10) {
        int roomIndex = rand() % 20; 

        
        int alreadyHasZombie = 0;
        for (int i = 0; i < zombieCount; ++i) {
            if (zombieRooms[i] == roomIndex) {
                alreadyHasZombie = 1;
                break;
            }
        }

        if (!alreadyHasZombie) {
            zombieRooms[zombieCount++] = roomIndex;
            addCreatureToRoom(rooms[roomIndex], "Zombie", 50, 5); 
        }
    }
    
    *currentRoom = rooms[0];
}

void addItemToRoom(Room *room, const char *itemName) {
    if (room->itemCount >= MAX_ITEMS) {
        printf("[INFO] This room can't hold more items.\n");
        return;
    }
    Item *item = (Item *)malloc(sizeof(Item));
    if (!item) {
        perror("Failed to create item");
        exit(EXIT_FAILURE);
    }
    strncpy(item->name, itemName, 50);
    room->items[room->itemCount++] = item;
}

void addCreatureToRoom(Room *room, const char *creatureName, int health, int strength) {
    if (room->creature != NULL) {
        printf("[INFO] This room already has a creature.\n");
        return;
    }
    Creature *creature = (Creature *)malloc(sizeof(Creature));
    if (!creature) {
        perror("Failed to create creature");
        exit(EXIT_FAILURE);
    }
    strncpy(creature->name, creatureName, 50);
    creature->health = health;
    creature->strength = strength;
    room->creature = creature;
}

void displayRoom(const Room *room, const Player *player) {
    printf("\n[ROOM DESCRIPTION]\n%s\n", room->description);

    if (room->itemCount > 0) {
        printf("\n[ITEMS IN ROOM]\n");
        for (int i = 0; i < room->itemCount; ++i) {
            printf("- %s\n", room->items[i]->name);
        }
    }

    if (room->creature) {
        printf("\n[ENEMY]\n%s (Health: %d, Strength: %d)\n", room->creature->name, room->creature->health, room->creature->strength);
    }

    // Show player's inventory
    if (player->inventoryCount > 0) {
        printf("\n[PLAYER INVENTORY]\n");
        for (int i = 0; i < player->inventoryCount; ++i) {
            printf("- %s\n", player->inventory[i]->name);
        }
    } else {
        printf("\n[PLAYER INVENTORY]\n(Empty)\n");
    }
}

void pickupItem(Player *player, Room *room, const char *itemName) {
    if (player->inventoryCount >= MAX_INVENTORY) {
        printf("[INFO] Inventory full! Please drop an item first.\n");
        return;
    }
    for (int i = 0; i < room->itemCount; ++i) {
        if (strcmp(room->items[i]->name, itemName) == 0) {
            player->inventory[player->inventoryCount++] = room->items[i];
            printf("[INFO] %s added to your inventory.\n", itemName);
            room->items[i] = room->items[--room->itemCount]; 
            return;
        }
    }
    printf("[INFO] This item is not in the room.\n");
}

void dropItem(Player *player, Room *room, const char *itemName) {
    if (room->itemCount >= MAX_ITEMS) {
        printf("[INFO] The room can't hold more items.\n");
        return;
    }
    for (int i = 0; i < player->inventoryCount; ++i) {
        if (strcmp(player->inventory[i]->name, itemName) == 0) {
            room->items[room->itemCount++] = player->inventory[i];
            printf("[INFO] %s dropped in the room.\n", itemName);
            player->inventory[i] = player->inventory[--player->inventoryCount]; 
            return;
        }
    }
    printf("[INFO] This item is not in your inventory.\n");
}

void attackCreature(Player *player, Room *room) {
    if (!room->creature) {
        printf("[INFO] There's nothing to attack in this room!\n");
        return;
    }
    while (player->health > 0 && room->creature->health > 0) {
        printf("[INFO] You attack...\n");
        room->creature->health -= player->strength;
        if (room->creature->health > 0) {
            printf("[INFO] %s attacks!\n", room->creature->name);
            player->health -= room->creature->strength;
        }
    }
    if (player->health <= 0) {
        printf("[INFO] You lost the fight! GAME OVER\n");
        exit(0);
    } else {
        printf("[INFO] %s has been defeated!\n", room->creature->name);
        free(room->creature);
        room->creature = NULL;
    }
}

void saveGame(const Player *player, const Room *currentRoom) {
    FILE *file = fopen(SAVE_FILE, "w");
    if (!file) {
        perror("Failed to open save file");
        return;
    }
    fprintf(file, "%d %d\n", player->health, player->strength);
    fprintf(file, "%d\n", player->inventoryCount);
    for (int i = 0; i < player->inventoryCount; ++i) {
        fprintf(file, "%s\n", player->inventory[i]->name);
    }
    fprintf(file, "%s\n", currentRoom->description);
    fclose(file);
    printf("[INFO] Game saved successfully to '%s'!\n", SAVE_FILE);
}

Room* loadGame(Player *player) {
    FILE *file = fopen(SAVE_FILE, "r");
    if (!file) {
        perror("Failed to open save file");
        return NULL;
    }
    fscanf(file, "%d %d\n", &player->health, &player->strength);
    fscanf(file, "%d\n", &player->inventoryCount);
    for (int i = 0; i < player->inventoryCount; ++i) {
        player->inventory[i] = (Item *)malloc(sizeof(Item));
        fgets(player->inventory[i]->name, 50, file);
        player->inventory[i]->name[strcspn(player->inventory[i]->name, "\n")] = 0;
    }
    char roomDesc[MAX_DESC_LEN];
    fgets(roomDesc, MAX_DESC_LEN, file);
    roomDesc[strcspn(roomDesc, "\n")] = 0;
    Room *room = createRoom(roomDesc);
    fclose(file);
    printf("[INFO] Game loaded successfully from '%s'!\n", SAVE_FILE);
    return room;
}

void processCommand(const char *command, Player *player, Room **currentRoom) {
    if (strcmp(command, "look") == 0) {
        displayRoom(*currentRoom, player);
    } else if (strncmp(command, "move ", 5) == 0) {
        char direction = command[5];
        Room *nextRoom = NULL;
        if (direction == 'u') nextRoom = (*currentRoom)->up;
        else if (direction == 'd') nextRoom = (*currentRoom)->down;
        else if (direction == 'l') nextRoom = (*currentRoom)->left;
        else if (direction == 'r') nextRoom = (*currentRoom)->right;

        if (nextRoom) {
            *currentRoom = nextRoom;
            printf("[INFO] You moved to a new room: %s\n", (*currentRoom)->description);
        } else {
            printf("[INFO] You can't go in that direction.\n");
        }
    } else if (strncmp(command, "pickup ", 7) == 0) {
        pickupItem(player, *currentRoom, command + 7);
    } else if (strncmp(command, "drop ", 5) == 0) {
        dropItem(player, *currentRoom, command + 5);
    } else if (strcmp(command, "attack") == 0) {
        attackCreature(player, *currentRoom);
    } else if (strcmp(command, "save") == 0) {
        saveGame(player, *currentRoom);
    } else if (strcmp(command, "load") == 0) {
        *currentRoom = loadGame(player);
    } else if (strcmp(command, "stats") == 0) {
        printf("[STATS] Health: %d, Strength: %d\n", player->health, player->strength);
    } else if (strcmp(command, "exit") == 0) {
        printf("[INFO] Exiting the game...\n");
        exit(0);
    } else {
        printf("[ERROR] Unknown command: %s\n", command);
    }
}


void showMainMenu() {
    printf("\n[INFO] Dungeon Adventure Game\n");
    printf("[1] Start a New Game\n");
    printf("[2] Load Saved Game\n");
    printf("[3] Exit\n");
    printf("Your choice: ");
}

int main() {
    printf("\n[INFO] Welcome to Dungeon Adventure Game!\n");

    int choice = 0;
    Player player;
    Room *currentRoom = NULL;

    while (choice != 3) {
        showMainMenu();
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1) {
            printf("[INFO] Starting a new game...\n");
            printf("[INFO] Commands: look, stats, move <direction>, pickup <item>, drop <item>, attack, save, exit\n");
            printf("[INFO] Directions: u = up, d = down, l = left, r = right\n");
            initializePlayer(&player);
            setupRooms(&currentRoom);
            break;
        } else if (choice == 2) {
            printf("[INFO] Loading saved game...\n");
            currentRoom = loadGame(&player);
            if (currentRoom == NULL) {
                printf("[INFO] No saved game found. Starting a new game...\n");
                initializePlayer(&player);
                setupRooms(&currentRoom);
            }
            break;
        } else if (choice == 3) {
            printf("[INFO] Exiting the game. Goodbye!\n");
            exit(0);
        } else {
            printf("[ERROR] Invalid choice. Please try again.\n");
        }
    }


    char command[MAX_COMMAND_LEN];
    while (1) {
        printf("\n> ");
        fgets(command, MAX_COMMAND_LEN, stdin);
        command[strcspn(command, "\n")] = 0;
        processCommand(command, &player, &currentRoom);
    }

    return 0;
}
