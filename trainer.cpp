#include "resources.hpp"

class trainer
{
    char *title = "Pokemon Trainer";
    char *name;
    bool goodAI;
    pokemon team[6];
    int payout;
    char *startMessage;
    char *defeatMessage;
    void *sprite;
};