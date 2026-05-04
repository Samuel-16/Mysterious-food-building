#include <iostream> // For outputting to, and inputting from the terminal.
#include <string> // For the C++ specific dynamic string.
#include <chrono> // For making the program wait.
#include <thread> // For making the program wait.
#include <cstdlib> // For random number generation.
#include <cctype> // For upper/lower case conversion.
#include <cstdint> // For better practice int types.

// Set datatype names. to avoid needing to type longer names repeatedly.
// A byte will be a one byte positive integer; a bytebyte will be a two byte positive integer.
using byte=std::uint8_t;
using bytebyte=std::uint16_t

// Ennumerate by powers of two.
// Obtainable items.
;enum Item{
    WOOD_SWORD=1<<        0,
    APPLE=1<<             1,
    APPLES=1<<            2,
    HEALTH_POTION=1<<     3,
    TWO_HEALTH_POTIONS=1<<4,
    CHAIR=1<<             5,
    STAIRCASE=1<<         6,
    KNIFE=1<<             7,
    RESTURANT=1<<         8,
    BONE=1<<              9,
    RUSTED_SWORD=1<<      10,
    NORMAL_SWORD=1<<      11,
    STEEL_SWORD=1<<       12,
    COIN=1<<              13,
    BRUSH=1<<             14,
    LEVER=1<<             15
}

// Characters other than the player.
;enum NPC{
    MAID=1<<         0,
    GUARD=1<<        1,
    VISCOUNT=1<<     2,
    ORC=1<<          3,
    CHEF=1<<         4,
    HUMAN=1<<        5,
    TREE=1<<         6,
    FAMILY_MEMBER=1<<7
}

;enum Direction{
    NORTH=8,
    EAST=9,
    SOUTH=10,
    WEST=11,
    UP=12,
    DOWN=13,
    LEFT=14,
    RIGHT=15
}

// A reverse ennumeration for index lookup at runtime.
;const char full_enum[32][16]=
{"maid", "guard", "viscount", "orc", "chef", "human", "tree", "family member",
"north", "east", "south", "west", "up", "down", "left", "right",
"wood sword", "apple", "Apples", "health potion", "Health Potionx2", "chair", "staircase", "knife",
"resturant", "bone", "rusted sword", "normal sword", "steel sword", "coin", "brush", "lever"}

// Automatic ennumeration as increments of 1.
;enum Type{
    ROOM,
    CLEARING,
    CORRIDOR,
    PRISON,
    BEDROOM,
    COURTROOM,
    FOREST,
    VILLAGE
}

;const char type_enum[8][10]=
{"room","clearing","corridor","prison","bedroom","courtroom","forest","village"}

;enum Action{
    GO,
    GET,
    DROP,
    FIGHT,
    MEET,
    EAT,
    SWING,
    QUIT,
    RESET,
    HELP
}

;const char command_enum[][6]=
{"GO","GET", "DROP", "FIGHT", "MEET", "EAT", "SWING", "QUIT", "RESET", "HELP"}


;struct parse_result{
    std::int8_t obj=-1;
    std::int8_t com=-1;
    byte err=2;
}

;struct Location{
    byte type=0;
    byte north=0;
    byte east=0;
    byte south=0;
    byte west=0;
    byte up=0;
    byte down=0;
    byte npcs=0;
    bytebyte items=0;
    std::string discription="MISSING DISCRIPTION";
}

;struct Npc{
    bytebyte inventory=0;
    byte hp=4;
    float avo=0.05;
}

;byte loc=4
;bytebyte inventory=3
;bytebyte eaten_items=0
;byte eaten_npcs=0

;Location locs[]={{0},
  {.type=ROOM,.south=4,.west=6,.discription=
    R"(It's a conservatory.
There is a nice view of the lanscape and forest.)"},
  {.type=CLEARING,.north=6,.east=4,.discription=
    R"(It's surrounded by a wooden fence.)"},
  {.type=CORRIDOR,.east=5,.west=4,.npcs=MAID,.discription=
    R"(It's a dark, moist, stone corridor.)"},
  {.type=ROOM,.north=1,.east=3,.west=2,.items=WOOD_SWORD+ROOM,.discription=
    R"(It's a small wodden room.)"},
  {.type=ROOM,.west=3,.npcs=GUARD,.discription=
    R"(It's a stone, prison-like room.)"},
  {.type=CLEARING,.east=1,.south=2,.discription=
    R"(You stand on a patch of grass on a tiny hill in an open area.
The breeze feels nice.)"}}

;int main() {
    ;std::cout<<"You are on an adventure to find a source of nourishment, and have entered a strange building you have found in the forest.\n"
    ;std::cout<<"Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, QUIT, RESET, and HELP.\n\n"
;}