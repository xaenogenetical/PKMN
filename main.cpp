#include "resources.hpp"
#include <iostream>

#define fight 0
#define pkmn 1
#define battle_item 2
#define run 3

#define SCREEN_SIZE_X 160
#define SCREEN_SIZE_Y 144

#define bit bool
#define bitstream bit *

bool lame_graphics = 0;

trainer player;

enum mv_t
{
    MOVE,
    ITEM,
    SWITCH,
    RUN
};

struct action
{
    mv_t selection;
    void *subject;
};

item bag[];

int main(int argc, char const *argv[])
{
    srand(NULL);
    return 0;
}

bool trainer_battle;
pokemon player_active;
pokemon opponent_active;

action player_move;
action opponent_move;

struct tile
{
    int graphicsData[7][7];
};

int TheScreenTM[SCREEN_SIZE_X][SCREEN_SIZE_Y];

void battle()
{
    player_turn();
    // determine enemy move
    // calc turn order
    bool player_first = player_active.stats[speed] > opponent_active.stats[speed] ? true : (player_active.stats[speed] == opponent_active.stats[speed] ? rand() % 2 : false);
    // execute moves

    switch (player_move.selection)
    {
    case (SWITCH):
        break;
    case (ITEM):
        playerUseItem((item *)player_move.subject);
        break;
    case (MOVE):
        if (player_first)
        {
            // use player move
            useMove(player_active, opponent_active, *(move *)player_move.subject);
        }
        break;
    case (RUN):
        break;
    }

    switch (opponent_move.selection)
    {
    case (SWITCH):
        break;
    case (ITEM):
        playerUseItem((item *)player_move.subject);
        break;
    case (MOVE):
        // use opponent move
        useMove(opponent_active, player_active, *(move *)opponent_move.subject);
        break;
    }
    if (!player_first && player_move.selection == MOVE)
    {
        // use player move
        useMove(player_active, opponent_active, *(move *)player_move.subject);
    }
    battle();
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
sprite decompress_sprite_data(bitstream data)
{
    bit *sSpriteBuffer0 = (bit *)calloc(49, 8); // 49 tiles (7x7), each one takes up 8 bytes
    bit *sSpriteBuffer1 = (bit *)calloc(49, 8);
    bit *sSpriteBuffer2 = (bit *)calloc(49, 8);
    bitstream reader = data;

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
    bit bitplane_to_use_first = *reader++;
    // parse 1 bit to determine initial packet type
    bit first_bitplane_initial_packet = *reader++;
    // then parse the rest as graphics data
    i = 0;
    while (i < number_bits_per_plane)
    {
        int counter = 0;
        bit bitA = 0;
        bit bitB = 0;
    rle_packet:
        while (*reader++ != 0)
        {
            counter++;
        }

        goto literal_packet;
    literal_packet:
        bitA = *reader++;
        bitB = *reader++;
        if (!bitA & !bitB) // single & because they're bools aka single bits
        {
            goto rle_packet;
        }
        // writebits(bitA, bitB);
        i += 2;
    }
    // determine end point based on sprite size
    // then read 1-2 bits for encoding method: 0, 10, or 11
    bit encode1 = *reader++;
    bit encode2;
    if (encode1)
    {
        encode2 = *reader++;
    }
    // 1 bit for inital packet type for 2nd dataplane
    bit second_bitplane_initial_packet = *reader++;
    // then remainder of graphics data

    free(sSpriteBuffer0);
    free(sSpriteBuffer1);
    free(sSpriteBuffer2);
};

void render_screen()
{

    if (lame_graphics)
    {
        const char *graphic_tiles[] = {"▖", "▗", "▘", "▝", "▀", "▛", "▌", "▙", "▄", "▟", "▐", "▜", "▚", "▞", " ", "█"};
        // annoying ahh calculating
    }
    else
    {
        const char *graphic_tiles[] = {"█", "▒", "░", " "}; // only way I could get it to work as I wanted was to make two local variables
        int row = 0;
        int col = 0;
        for (; col < SCREEN_SIZE_X; col++)
        {
            for (; row < SCREEN_SIZE_Y; row++)
            {
                std::cout << graphic_tiles[TheScreenTM[row][col]];
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
}