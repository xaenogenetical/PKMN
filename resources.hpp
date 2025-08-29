#include <map>
#include <cstring>
#include <vector>
#include <iostream>
#include <variant>
#pragma once

#define graphicsSquare std::vector<std::vector<int>>
#define SCREEN_SIZE_X 160
#define SCREEN_SIZE_Y 144
#define SCREEN_SIZE_X_BOX SCREEN_SIZE_X / 7
#define SCREEN_SIZE_Y_BOX SCREEN_SIZE_Y / 7
typedef bool bit;
typedef bit *bitstream;
#define modifiedStat(stage) statMods[stage + 6]
#define playerUseItem(it) useItem(0, it);
#define opponentUseItem(it) useItem(1, it);

#define matchup(source, dest) source.type_matchup_outgoing.at(dest)

#define isSuperEffectiveAgainst(t, pk) (matchup(t, pk.type1) == super_effective && matchup(t, pk.type2) != not_very_effective) || ((matchup(t, pk.type2) == super_effective && matchup(t, pk.type1) != not_very_effective))

int cursorTopLeftX;
int cursorTopLeftY;
extern int **TheScreenTM;

void renderScreen(); // reads the data stored in TheScreenTM and writes the appropriate tiles to the console (stdout)
void draw();         // resets the cursor then calls renderScreen();
void clearScreen();

struct map_tile
{
      std::string name;
      bool blocking;
      void *on_interact;
      void *on_stand;
};
enum stats
{
      hp,
      attack,
      defense,
      special,
      speed,
      accuracy,
      evasion
};

enum matchup
{
      super_effective,
      normal_effective,
      not_very_effective,
      immune
};

class sprite
{
};

struct type
{
      char *name;

      std::map<type, matchup> type_matchup_outgoing;
      std::map<type, matchup> type_matchup_incoming;

      bool operator==(type &other);
};

enum status
{
      burn,
      paralyze,
      poison,
      freeze,
      atk_up,
      def_up,
      speed_up,
      spec_up,
      acc_up,
      eva_up,
      atk_dwn,
      def_dwn,
      speed_dwn,
      spec_dwn,
      acc_dwn,
      eva_dwn,
};

struct move_effect
{
      int chance;
      status change;
      int severity; // for drastic stat changes and such
      bool target;
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
      move_effect effect;
};

int statMods[] = {25, 28, 33, 40, 50, 66, 100, 150, 200, 250, 300, 350, 400};

class pokemon
{
private:
      int IVs[5];
      int EVs[5];
      int determineStat(stats stat);

public:
      static move learnSet[];
      static int baseStats[];
      void *sprite;
      type type1;
      type type2;

      char sex;
      move *knownMoves[4];
      int level;

      char *name;
      char *species;

      int statChanges[7];

      status affliction;

      int currHP;
      int maxHP;

      int stat_vals[5];

      pokemon();

      pokemon(int dexNum);

      bool isFainted();

      void level_up();

      void heal();

      void apply_status(status change);

      int fetchReal(stats stat);

      ~pokemon();
};

class trainer
{
      pokemon team[6];
      bool goodAI;

public:
      bool hasGoodAI()
      {
            return goodAI;
      }
};
extern pokemon player_active;
extern pokemon opponent_active;

void handle_effect(move &mv);

int damage_calculation(pokemon &attacker, pokemon &defender, move &mv);

struct item
{
};

struct tile
{
      int graphicsData[7][7];
};

bool useItem(bool, item *);

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
      std::variant<pokemon *, move *, item *, std::nullptr_t> subject;
};

enum gameState
{
      overworld,
      encounter,
      trainer_spot,
      battling,
      exiting
};

enum moveOutcomes
{
      NO_PP,
      NOEFFECT,
      MISS,
      N_V_EFF = not_very_effective,
      HIT,
      S_EFF
};
int useMove(pokemon &attacker, pokemon &defender, move &mv);

void incrementCursor();

void setTileAtCursorTo(graphicsSquare tile);

#define placeCursorAt(x, y) \
      cursorTopLeftX = x;   \
      cursorTopLeftY = y;

void printTextBoxBorder();

void clearTextBox();

void printText(char *msg);

void battle();

// graphics data for every "tile", indexed with their corresponding name
extern std::map<char *, graphicsSquare> tile_list;
extern std::map<char *, int> move_ids;