#include <iostream> // For outputting to, and inputting from the terminal.
#include <string> // For the C++ specific dynamic string.
#include <chrono> // For making the program wait.
#include <thread> // For making the program wait.
#include <cstdlib> // For random number generation.
#include <cctype> // For upper/lower case conversion.
#include <cstdint> // For better practice int types.

// Set datatype names. to avoid needing to type longer names repeatedly.
using byte=std::uint8_t;      // A byte will be a one byte positive integer
using bytebyte=std::uint16_t; // A bytebyte will be a two byte positive integer.

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
    VILLAGE
}

;const char type_enum[8][10]=
{"room","clearing","corridor","prison","bedroom","courtroom","forest","village"}

// Ennumerations for player commands.
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

;const char command_enum[10][6]=
{"GO","GET", "DROP", "FIGHT", "MEET", "EAT", "SWING", "QUIT", "RESET", "HELP"}

// A structure to be returned from the parse meathod.
;struct parse_result{
    std::int_least8_t obj=-1;//Corrisponds with an item in the full_enum.
    std::int_least8_t com=-1;//Corrisponds with an item in the command_enum.
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

;std::int_least8_t parse_com_check(const char** arr,int arr_size){
    for (byte i=0;i<arr_size;i++){
        if (*arr[i]=='\0'){
            return i;
        }
    }
    return -1;
}

;parse_result parse(std::string inp_str){
    ;parse_result out={-1,-1,2}
    ;if (inp_str.length()>=255){ // Return if the string is too big. Should not be possible due to the input buffer size limit.
        std::cout<<"ERROR reading input!\n";
        std::cerr<<"Input length exceeded 255!\n"<<"This should not be possible.\n";
        return out;}

    ;const byte command_enum_length=sizeof(command_enum)/sizeof(command_enum[0])

    ;const char* commands[command_enum_length] // Mutable vaiable pointing to constant data.
    ;for (byte i=0;i<command_enum_length;i++) // Set the values in the commands array.
       {commands[i]=*command_enum+i*sizeof(command_enum[0]);} // Values are pointers to constant chars declared in global scope.

    ;byte i=0
    ;while (i < inp_str.length()){
        for (byte j=0;j<command_enum_length;j++){
            if (*commands[j]!='\0' && std::toupper(inp_str[i])==*commands[j]) {commands[j]++;}}
        i++;
        out.com=parse_com_check(commands,command_enum_length);
        if (out.com!=-1){break;}
    }
    if (i>=inp_str.length() && out.obj==-1){return out;} // If the while-loop didn't break, return with the error value left at 2.
    ;out.err=1 // Reduce the error value from 2 to 1, to show that the first step completed successfuly.

    ;const byte full_enum_length=sizeof(full_enum)/sizeof(full_enum[0])
    
    ;const char* objs[full_enum_length] // Mutable vaiable pointing to constant data.
    ;for (byte i=0;i<full_enum_length;i++) // Set the values in the objs array.
       {objs[i]=*full_enum+i*sizeof(full_enum[0]);} // Values are pointers to constant chars declared in global scope.

    ;i=0
    ;while (i < inp_str.length()){
        for (byte j=0;j<full_enum_length;j++){
            if (*objs[j]!='\0' && std::tolower(inp_str[i])==*objs[j]) {objs[j]++;}}
        i++;
        out.obj=parse_com_check(objs,full_enum_length);
        if (out.obj!=-1){break;}
    }
    if (i>=inp_str.length() && out.obj==-1){return out;} // If the while-loop didn't break, return with the error value left at 1.
    ;out.err=0 // Set the error value to 0, to show that the first step completed successfuly.

    ;return out
;}

;int main() {
    ;std::cout<<"You are on an adventure to find a source of nourishment, and have entered a strange building you have found in the forest.\n"
    << "Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, QUIT, RESET, and HELP.\n\n"
    << "You are in a " << type_enum[locs[loc].type] << ".\n"
    << locs[loc].discription << '\n'
    << "What will you do? >"
    ;char input_buffer[256]
    ;std::cin.getline(input_buffer,255)
    
    ;parse_result action=parse(input_buffer)
    ;while (action.com!=QUIT){
        /*Call do_action*/
        ;std::cout<< '{' <<(int) action.com << ',' <<(int) action.obj << ',' <<(int) action.err <<'}' //  Debug line. Remove later.
        ;std::cout<<'>'
        ;std::cin.getline(input_buffer,255)
        ;action=parse(input_buffer)
    ;}
;}