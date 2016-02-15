#ifndef PLAYER_H
#define PLAYER_H

#include "items.h"

#include <stdbool.h>

#define INVENTORY_SIZE 5

struct player;

typedef struct player {
    char* name;
    int health;
    int mana;
    struct item* items[INVENTORY_SIZE];
} player;

player* make_player(char* name);
//char* info(player* player);
//
void delete_player(player* player);
bool give_item(player* player, struct item** item);

struct item* get_item_from_player(player* player, char* item_name);
#endif
