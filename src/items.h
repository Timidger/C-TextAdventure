#ifndef ITEM_H
#define ITEM_H

#include "player.h"
#include <stdlib.h>

struct player;

typedef void (*effect)(struct player*);

enum _item_type;
struct item;
struct actionable;
struct weapon;
struct consumable;
struct potion;


typedef enum item_type {
    actionable_type,
    weapon_type,
    consumable_type,
    potion_type,
} item_type;

typedef struct item {
    char* name;
    item_type type;
    void* item;
} item;

typedef struct actionable {
} actionable;

typedef struct weapon {
    int damage;
} weapon;

typedef struct consumable {
    int health;
    int mana;
} consumable;

typedef struct potion {
    effect effect_function;

} potion;

item* new_item(char* name, item_type type, void* item);
actionable* new_actionable();
weapon* new_weapon(int damage);
consumable* new_consumable(int health, int mana);
potion* new_potion(effect effect_function);

item* get_item(item* items[], int item_size, char* name);

void print_item(item* item);
void delete_item(item* item);

#endif
