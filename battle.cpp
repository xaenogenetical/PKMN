#include "resources.hpp"

bool useItem(bool, item *)
{
}

int damage_calculation(pokemon &attacker, pokemon &defender, move &mv) // weird formatting here is due to my formatter hating really lengthy equations
{
    bool crit = (rand() % 256) < (attacker.baseStats[speed] / 2);
    int damage = ((((2 * attacker.level * (crit ? 2 : 1) / 5) + 2) *
                   mv.power *
                   (mv.physical ? attacker.fetchReal(attack) : attacker.fetchReal(special) / mv.physical ? defender.fetchReal(defense)
                                                                                                         : defender.fetchReal(special)) /
                   50) +
                  2) *
                 (mv.type == attacker.type1 || mv.type == attacker.type2 ? 1.5 : 1) * ((defender.type1.type_matchup_incoming[mv.type] == super_effective) ? 2 : (defender.type1.type_matchup_incoming[mv.type] == not_very_effective ? 0.5 : 1)) *
                 ((defender.type2.type_matchup_incoming[mv.type] == super_effective) ? 2 : (defender.type2.type_matchup_incoming[mv.type] == not_very_effective ? 0.5 : 1)) * (((rand() % (38)) + 217) / 255);
    return damage < 1 ? 1 : damage;
}

int useMove(pokemon &attacker, pokemon &defender, move &mv)
{
    if (mv.currPP <= 0)
    {
        return NO_PP;
    }
    mv.currPP--;
    if (mv.type.type_matchup_outgoing.at(defender.type1) == immune || mv.type.type_matchup_outgoing.at(defender.type2) == immune)
    {
        return NOEFFECT;
    }
    if (mv.accuracy * ((double)modifiedStat((attacker.statChanges[accuracy])) / 100.0) * ((double)modifiedStat(defender.statChanges[evasion]) / 100.0) >= rand() % 255)
    {
        return MISS;
    }
    if (mv.attacking)
    {
        defender.currHP -= damage_calculation(attacker, defender, mv);
    }
    handle_effect(mv);
    return HIT;
}