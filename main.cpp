#include "resources.hpp"
#include <iostream>

#define fight 0
#define pkmn 1
#define battle_item 2
#define run 3

trainer player;

struct item
{
};

item bag[];

int main(int argc, char const *argv[])
{
    return 0;
}

bool trainer_battle;
pokemon player_active;
pokemon opponent_active;

void battle()
{
    player_turn();
    // determine enemy move
    // calc turn order
    // execute moves
    // loop
}

void player_turn()
{
turn_start:
    int choice = getchar();
    if (choice == fight)
    {
        int mv = 0;
        while (true)
        {
            char inp = getchar();
            if (inp == 'e') // enter
            {
                break;
            }
            // change mv
        }
        // load move into their todo
        void *todo = &player_active.knownMoves[mv];
    }
    if (choice == pkmn)
    {
        // show_party_screen();
        // user select
        // load switch into their todo
    }
    if (choice == battle_item)
    {
        // show bag
        // user select
        // lode move into their todo
    }
    if (choice == run)
    {
        if (trainer_battle)
        {
            std::cout << "Cannot run away!" << std::endl;
            goto turn_start;
        }
        std::cout << "You ran away!" << std::endl;
        return;
    }
}
// assumes input data is properly formatted, does no checking of its own
sprite decompress_sprite_data(bool *data)
{
    bool *sSpriteBuffer0 = (bool *)calloc(49, 8); // 49 tiles (7x7), each one takes up 8 bytes
    bool *sSpriteBuffer1 = (bool *)calloc(49, 8);
    bool *sSpriteBuffer2 = (bool *)calloc(49, 8);
    bool *reader = data;

    // parse 4 bits - sprite width
    char width = 0; // allocates space for 1 byte (8 bits)
    int i = 0;
    char height = 0;
    while (i < 5)
    {
        width <<= 1;
        width |= *reader++;
    }
    // parse 4 bits - sprite hight
    char height = 0;
    i = 0;
    while (i < 5)
    {
        height <<= 1;
        height |= *reader++;
    }
    int number_bits_per_plane = height * width;
    // parse 1 bit to determine decompress method
    bool bitplane_to_use_first = *reader++;
    // parse 1 bit to determine initial packet type
    bool first_bitplane_initial_packet = *reader++;
    // then parse the rest as graphics data
    // determine end point based on sprite size
    // then read 1-2 bits for encoding method: 0, 10, or 11
    bool encode1 = *reader++;
    bool encode2;
    if (encode1)
    {
        encode2 = *reader++;
    }
    // 1 bit for inital packet type for 2nd dataplane
    bool second_bitplane_initial_packet = *reader++;
    // then remainder of graphics data

    free(sSpriteBuffer0);
    free(sSpriteBuffer1);
    free(sSpriteBuffer2);
};