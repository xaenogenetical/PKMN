#include "resources.hpp"

class pokemon
{
private:
public:
    static move learnSet[];
    static int baseStats[];
    void *sprite;
    type type1;
    type type2;

    char sex;
    move knownMoves[4];
    int level;
    int IVs[5];
    int EVs[5];

    char *species;

    int statChanges[6];

    status affliction;

    int currHP;
    int maxHP;

    int stats[5];

    pokemon(int dexNum)
    {
    }

    bool isFainted()
    {
        return currHP <= 0;
    }

    void level_up()
    {
        level++;
        /*increment stats*/
    }

    void heal()
    {
        currHP = maxHP;
    }

    void apply_status(status change)
    {
        if (change >= freeze)
        {
            affliction = change;
            return;
        }
        else
        {
            int ind = change - freeze;
        }
    }

    ~pokemon()
    {
    }
};
