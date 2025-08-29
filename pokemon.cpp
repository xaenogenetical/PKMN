#include "resources.hpp"

pokemon::pokemon()
{
}

pokemon::pokemon(int dexNum)
{
}

bool pokemon::isFainted()
{
    return currHP <= 0;
}

void pokemon::level_up()
{
    level++;
}

int pokemon::determineStat(stats stat)
{
}

int pokemon::fetchReal(stats stat)
{
}

void pokemon::heal()
{
    currHP = maxHP;
}

void pokemon::apply_status(status change)
{
    if (change <= freeze)
    {
        affliction = change;
        return;
    }
    else
    {
        int ind = change - freeze;
    }
}

pokemon::~pokemon()
{
}

void incrementCursor()
{
    if (++cursorTopLeftX > SCREEN_SIZE_X_BOX)
    {
        cursorTopLeftX = 0;
        if (++cursorTopLeftY > SCREEN_SIZE_Y_BOX)
        {
            cursorTopLeftX = 0;
            cursorTopLeftY = 0;
        }
    }
}

void setTileAtCursorTo(graphicsSquare tile)
{
    for (int row = 0; row < tile.size(); row++)
    {
        for (int col = 0; col < tile.at(row).size(); col++)
        {
            TheScreenTM[row + (cursorTopLeftX * 7)][col + (cursorTopLeftY * 7)] = tile.at(row).at(col);
        }
    }
}

void printText(char *msg)
{
    char holder[1];
    char *local_msg = msg;
    placeCursorAt(0, 0);
    printTextBoxBorder();

loop_top:
    if (!local_msg)
    {
        return;
    }
    holder[0] = *local_msg++;
    // move cursor to correct location
    setTileAtCursorTo(tile_list.at(holder));
    incrementCursor();
    while (cursorTopLeftX == 0 || cursorTopLeftX == 10)
    { // TODO: GET REAL
        incrementCursor();
    }
    if (cursorTopLeftX == SCREEN_SIZE_X_BOX - 1 && cursorTopLeftY == SCREEN_SIZE_Y_BOX - 1)
    {
        setTileAtCursorTo(tile_list.at("selector_arrow"));
        getchar();
        clearTextBox();
    }
    goto loop_top;
}
