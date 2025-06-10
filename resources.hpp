#include <map>
#include <cstring>

enum status
{
    burn,
    paralyze,
    poison,
    freeze,
};

enum stats
{
    hp,
    attack,
    defense,
    special,
    speed
};

enum matchup
{
    super_effective,
    normal_effective,
    not_very_effective
};

struct type
{
    char *name;

    std::map<type, matchup> type_matchups;

    bool operator==(type &other)
    {
        return std::strcmp(name, other.name) == 0;
    }
};

struct move
{
    int power;
    int accuracy;
    int currPP;
    int powerPoints;
    char *name;
    char *description;
    type type;
    bool attacking; // false == status move
    bool physical;  // false == special move
};

class pokemon
{
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
};

class trainer
{
};

int damage_calculation(pokemon &attacker, pokemon &defender, move &mv) // weird formatting here is due to my formatter hating really complex math equations
{
    bool crit = (rand() % 256) < (attacker.baseStats[speed] / 2);
    int damage = ((((2 * attacker.level * (crit ? 2 : 1) / 5) + 2) *
                   mv.power *
                   (mv.physical ? attacker.stats[attack] : attacker.stats[special] / mv.physical ? defender.stats[defense]
                                                                                                 : defender.stats[special]) /
                   50) +
                  2) *
                 (mv.type == attacker.type1 || mv.type == attacker.type2 ? 1.5 : 1) * ((defender.type1.type_matchups[mv.type] == super_effective) ? 2 : (defender.type1.type_matchups[mv.type] == not_very_effective ? 0.5 : 1)) *
                 ((defender.type2.type_matchups[mv.type] == super_effective) ? 2 : (defender.type2.type_matchups[mv.type] == not_very_effective ? 0.5 : 1)) * ((rand() % (255 - 217)) / 255);
    return damage < 1 ? 1 : damage;
}