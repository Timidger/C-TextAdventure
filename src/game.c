#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "display.h"
#include "player.h"
#include "items.h"
#include "utils.h"


void test(void) {
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


int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        test();
        return 0;
    }
    reset_format();
    printf(  "You awaken in a room. A very familiar room. This is your room. It has been your room for as"
            " long as you can remember. Unfortunately it will not be your room for very long. Your "
            // We should add a display function for points of interest, like parents. Make them bold or something
            ANSI_BOLD "PARENTS " ANSI_COLOR_RESET "have decided that your room will be taken by "
            "your new baby brother, " ANSI_BOLD "ALEX" ANSI_COLOR_RESET ", born just last week."
            " For the first week he was sleeping your parents, but they soon got tired of that. So they fixed the"
            " leaky pipe that had caused the basement to leak last year so that they could put the baby in your room"
            " while you would take the basement. They didn't ask you of course. Not their lovely first born."
            " Not their straight A, wonderful, positively angelic first child named . . .\n\n"
            " What is your name again" ANSI_BLINK " . . . ?" ANSI_COLOR_RESET);
    fflush(stdout);

    // Single key input grab
    raw_mode();
    hide_terminal_input();
    getchar();
    show_terminal_input();
    cooked_mode();

    // Actually get the name
    printf("\n\nName: ");
    char* name = malloc(32);
    name = get_input(32);
    // Make the player
    player* player = make_player(name);
    printf(". . . named" ANSI_COLOR_MAGENTA " %s" ANSI_COLOR_GRAY "!"
           " Of course. You know your own name."
           "  Though you have always thought it a stupid name"
          " for a " ANSI_BLINK ". . ." ANSI_COLOR_RESET "\n", name);
    // Get gender
    char* options[] = {"boy", "girl", "neither"};
    char* chosen = choose(options, ARRAY_SIZE(options));
    return 0;
}
