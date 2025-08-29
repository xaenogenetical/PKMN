#include "resources.hpp"
#include "battle.hpp"

bool trainer_battle;
pokemon player_active;
pokemon opponent_active;
trainer opp;

action player_move;
action opponent_move;

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

void battle()
{
    int outcome;
    bool player_first;
    int runAttempts;
battle_round:
    player_turn();
    // determine enemy move
    if (trainer_battle)
    {
        if (opp.hasGoodAI())
        {
            move **possibleMoves = (move **)calloc(sizeof(move *), 4);
            int c = 0;
            int ind = 100;
            for (int sel = 0; sel < 4; sel++)
            {
                if (opponent_active.knownMoves && isSuperEffectiveAgainst(opponent_active.knownMoves[sel]->type, player_active))
                {
                    possibleMoves[c++] = opponent_active.knownMoves[sel];
                }
                if (!possibleMoves[0])
                {
                    goto badAI;
                }
                while (!possibleMoves[ind] || ind == 100)
                {
                    ind = rand() % 4;
                }
                opponent_move = {MOVE, opponent_active.knownMoves[ind]};
            }
            free(possibleMoves);
        }
        else
        {
        badAI:
            opponent_move = {MOVE, opponent_active.knownMoves[rand() % 4]};
        }
    }
    // calc turn order
    player_first = player_active.fetchReal(speed) > opponent_active.fetchReal(speed) ? true : (player_active.fetchReal(speed) == opponent_active.fetchReal(speed) ? rand() % 2 : false);
    // execute moves
    runAttempts = 0;
    switch (player_move.selection)
    {
    case (SWITCH):
        clearScreen();
        break;
    case (ITEM):
        playerUseItem(std::get<item *>(player_move.subject));
        break;
    case (MOVE):
        if (player_first)
        {
            // use player move
            outcome = useMove(player_active, opponent_active, *std::get<move *>(player_move.subject));
            if (outcome == NO_PP)
            {
                std::cout << "NO PP" << std::endl;
            }
        }
        break;
    case (RUN):
        if (trainer_battle) // redundant
        {
            std::cout << "Cannot run away!" << std::endl;
            goto battle_round;
        }
        runAttempts++;
        if (player_active.fetchReal(speed) < opponent_active.fetchReal(speed))
        {
            int oddsEscape = ((player_active.fetchReal(speed) * 32) / ((opponent_active.fetchReal(speed) / 4) % 256)) + 30 * runAttempts;
            if (oddsEscape > 255 || oddsEscape > rand() % 256)
            {
                return; // battle ends
            }
        }
        else
        {
            return;
        }
        break;
    }

    switch (opponent_move.selection)
    {
    case (SWITCH):
        break;
    case (ITEM):
        opponentUseItem(std::get<item *>(player_move.subject));
        break;
    case (MOVE):
        // use opponent move
        outcome = useMove(opponent_active, player_active, *std::get<move *>(opponent_move.subject));
        break;
    }
    if (!player_first && player_move.selection == MOVE)
    {
        // use player move
        outcome = useMove(player_active, opponent_active, *std::get<move *>(player_move.subject));
    }
    goto battle_round;
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
        player_move = {MOVE, player_active.knownMoves[mv]};
    }
    if (choice == pkmn)
    {
        pokemon sel;
        // show_party_screen();
        // user select
        // load switch into their todo
        player_move = {SWITCH, &sel};
    }
    if (choice == battle_item)
    {
        item sel;
        // show bag
        // user select
        // lode move into their todo
        player_move = {ITEM, &sel};
    }
    if (choice == run)
    {
        if (trainer_battle)
        {
            std::cout << "Cannot run away!" << std::endl;
            goto turn_start;
        }
        std::cout << "You ran away!" << std::endl;
        player_move = {RUN, nullptr};
        return;
    }
}