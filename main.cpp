#include "resources.hpp"
#include <iostream>

bool lame_graphics = 0;

trainer player;

void draw()
{
    std::cout << "\033[0;0H";
    renderScreen();
}

item bag[];
gameState state;
int main(int argc, char const *argv[])
{
    srand(NULL);
    // playIntroVid();
    while (true)
    { // doing it this way ensures that each game state returns before entering the next, switching between states inside of each one would eventually overflow the stack
        switch (state)
        {
        case overworld:
            break;
        case encounter:
            break;
        case trainer_spot:
            break;
        case battling:
            break;
        case exiting:
            return;
        }
    }
    return 1;
}

bool trainer_battle;
pokemon player_active;
pokemon opponent_active;
trainer opp;

action player_move;
action opponent_move;

int TheScreenTM[SCREEN_SIZE_X][SCREEN_SIZE_Y];

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