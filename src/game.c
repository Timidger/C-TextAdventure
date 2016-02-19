#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "player.h"
#include "items.h"
#include "utils.h"


int main(void) {
    player* player = make_player("Timidger");
    item* compass = new_item("Compass", actionable_type, (void*) new_actionable());
    item* sword = new_item("Sword", weapon_type, (void*) new_weapon(5));
    item* health_potion = new_item("Healing Potion", consumable_type, (void*) new_consumable(25, 0));
    // Item is set to null here and freed
    // The memory is copied and given to the player
    reset_format();
    char*  player_info;
    player_info = info(player);
    printf(player_info);
    free(player_info);
    give_item(player, &compass);
    give_item(player, &sword);
    give_item(player, &health_potion);

    player_info = info(player);
    printf(player_info);
    free(player_info);
    // This deletes the items he owns
    delete_player(player);
    // Should print nothing now that he is deleted
    player_info = info(player);
    free(player_info);
    printf(player_info);
    // This does nothing, but if we remove the give item to player, this will actually free the item
    // Because we gave it to player though, the item has already been freed and set to null
    delete_item(compass);
}
