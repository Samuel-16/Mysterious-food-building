#ifndef type_enum_size


// Set datatype names. to avoid needing to type longer names repeatedly.
using byte=std::uint8_t;  // A byte will be a one byte positive integer.
using ibyte=std::uint_fast8_t;  // An ibyte will be at least a one-byte positive integer.
using word=std::uint_least16_t; // A word will be a two byte positive integer.

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
    RESTAURANT=1<<        8,
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

// Ennumerations for types of rooms.
// Automatic ennumeration as increments of 1.
;enum Type{
    ROOM,
    CLEARING,
    CORRIDOR,
    PRISON,
    BEDROOM,
    COURTROOM,
    FOREST,
    VILLAGE,
    BASEMENT,
    TREASURY,
    DINETTE,
    ART_ROOM,
    CAVE,
    HALL
}

// Ennumerations for player commands.
;enum Action{
    GO,
    GET,
    DROP,
    FIGHT,
    MEET,
    EAT,
    SWING,
    HELP,
    QUIT,
    RESET,
    GAME_OVER,
    HUMAN_CONVERSATION,
    WIN_STATE,
}

#define type_enum_size ((sizeof(type_enum)/sizeof(type_enum[0]))/2)
#define player_hp_max 72
#define item_uint2(n,loc) (((n)>>(loc))%4) // Isolate 2 adjacent bits as a single integer.
#define npc_uint2(n,loc) (((((n)%256)&(1<<(loc)))?1:0)|((((n)>>8)&(1<<(loc)))?2:0)) // Isolate a bit in two adjacent bytes to make a 2-bit integer.
#define check_can_hold_multiple(arr) ((arr)&(APPLE|APPLES|HEALTH_POTION|TWO_HEALTH_POTIONS)) // Check if an item can be stacked.
#define ran() ((double)rand())/((double)RAND_MAX) // Generate a random float.
#define HUMAN_EATEN_BY_ORC (flags & 1)
#define VISCOUNT_MOVED     (flags & 2)
#define HUMAN_CHECKED      (flags & 4)
#define HUMAN_FREE         (flags & 8)
#define GUARD_ROOM_VISIT   (flags & 16)
#define ART_ROOM_VISIT     (flags & 32)
#define GUI                (flags & 64)
#define JP                 (flags & 128)

#endif