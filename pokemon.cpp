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

    int statChanges[6];

    status affliction;

    int currHP;

    int stats[5];

    pokemon()
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
};
