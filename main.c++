#include <iostream> // For outputting to, and inputting from the terminal.
#include <string> // For the C++ specific dynamic string.
#include <chrono> // For making the program wait.
#include <thread> // For making the program wait.
#include <cstdlib> // For random number generation.
#include <cctype> // For upper/lower case conversion.
#include <cstdint> // For better practice int types.
#include <charconv> // To convert numbers to string.
#include <cassert> // To alert if any program states intended to be impossible are reached.

// Set datatype names. to avoid needing to type longer names repeatedly.
using byte=std::uint8_t;  // A byte will be a one byte positive integer.
using ibyte=std::uint_fast8_t;  // An ibyte will be at least a one-byte positive integer.
using word=std::uint_least16_t; // A word will be a two byte positive integer.

#include "core_game_structs.hpp"
#include "descript_consts.h"

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

// A reverse ennumeration for index lookup at runtime.
;const char full_enum[80][16]=
{"maid", "guard", "viscount", "orc", "chef", "human", "tree", "family member",
"north", "east", "south", "west", "up", "down", "left", "right",
"wood sword", "apple", "Apples", "health potion", "Health Potionx2", "chair", "staircase", "knife",
"restaurant", "bone", "rusted sword", "normal sword", "steel sword", "coin", "brush", "lever",
"メイド", "守衛", "子爵", "鬼", "コック", "人間", "木", "家の人",
"北", "東", "南", "西", "上", "下", "左", "右",
"林の刀", "りんご", "Apples", "治癒薬", "Health Potionx2", "椅子", "階段", "包丁",
"食堂", "骨", "錆びた剣", "普通の剣", "鋼の剣", "硬貨", "刷子", "レバー",
"林の剣", "林檎", "Apples", "体力ポーシ", "Health Potionx2", "チェア", "段々", "ナイフ",
"レストラン", "ボーン", "錆びた刀", "普通の刀", "鋼の刀", "コイン", "ブラシ", "てこ",}
;const char hp_enum[]={
48,6,12,4,40,52,-48,2,
0,0,0,0,0,0,0,0,
-56,3,0,16,0,1,0,-60,0,-2,-72,-96,0,0,-1,0}
//;const char eat_text[64][4][128]

//Global output string buffer:
;char outBuff[1024]={0}
;static void clearOutBuff(){
  for(std::size_t i=0;i<sizeof(outBuff);++i)
    outBuff[i]='\0';
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

;const char type_enum[28][11]=
{"room","clearing","corridor","prison","bedroom","courtroom","forest","village","basement","treasury","dinette","art room","cave","hall",
 "部屋", "開墾",     "廊下",    "刑務所", "寝室",    "公判廷",    "森",    "村",      "地下室",   "金庫",    "食堂",    "美術室",   "空洞", "会館"}
#define type_enum_size ((sizeof(type_enum)/sizeof(type_enum[0]))/2)

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

;const char command_enum[42][6]=
{  "GO","GET", "DROP", "FIGHT", "MEET", "EAT", "SWING", "HELP", "QUIT", "RESET",\
"VISIT","LIFT","THROW","HIT",  "CHECK", "SWALL","USE",  "EXIT", "RESTA", "HINT",\
  "行","取",   "落",   "戦",     "合",   "食",   "振",    "辞",   "リ",    "助",\
  "訪","拾",   "投",   "当",     "見",   "飲",   "使",    "出",   "再",    "仄",\
"SAVE","セ"}

;static inline Textarr& operator<<(struct Textarr &inp, const char* string){
  inp.arr[inp.end]=string;
  ++inp.end;
  inp.canApp=false;
  return inp;
}

;static inline Textarr& operator<<(struct Textarr &inp, const char string){
  if(inp.canApp) *(inp.varStrEnd++)=string;
  else {
    *(++inp.varStrEnd)=string;
    inp.arr[inp.end++]=inp.varStrEnd++;
  }
  inp.canApp=true;
  return inp;
}

;static inline Textarr& operator<<(struct Textarr &inp, const byte number){
  if(number<10)
    return inp << ((char) ('0'+number));
  if (!inp.canApp){
    inp.arr[inp.end++]=++inp.varStrEnd;
    inp.canApp=true;}
  if(number<100){
    *inp.varStrEnd =   ((char) ('0'+(number/10)));
    *(inp.varStrEnd+1)=((char) ('0'+(number%10)));
    inp.varStrEnd+=2;
    return inp;}
  *inp.varStrEnd  =  (number<200?'1':'2');
  *(inp.varStrEnd+1)=((char) ('0'+((number/10)%10)));
  *(inp.varStrEnd+2)=((char) ('0'+(number%10)));
  inp.end+=3;
  return inp;
}

;template <typename potentialNum> static inline Textarr& operator<<(struct Textarr &inp, const potentialNum number){
  if (!inp.canApp){
    inp.arr[inp.end++]=++inp.varStrEnd;
    inp.canApp=true;}
  auto result = std::to_chars(inp.varStrEnd, inp.varStrEnd + 36, number);
  assert(result.ec == std::errc{});
  inp.varStrEnd = result.ptr;
  return inp;
}

;static inline void operator-(struct Text &inp, const byte number){
  inp.sleep=number;
}

;static inline Textarr& operator-(struct Textarr &inp, const byte number){
  assert(inp.end>0);
  inp.sleeps[inp.end-1]=number;
  return inp;
}

;static inline void operator+(struct Text &inp, const byte number){
  inp.sleep+=number;
}

;static inline Textarr& operator+(struct Textarr &inp, const byte number){
  assert(inp.end>0);
  inp.sleeps[inp.end-1]+=number;
  return inp;
}

static inline Textarr& operator<<(struct Textarr &inp, const Text apen){
  assert(apen.string);
  return (inp << apen.string) - apen.sleep;
}

static inline Textarr& operator<<(struct Textarr &inp, const Textarr apen){
  for(std::size_t i=0;apen.arr[i]!=nullptr;++i){
    (inp << apen.arr[i]) - apen.sleeps[i];}
  return inp;
}

;byte flags=0
;byte loc=4
;word inventory=HEALTH_POTION
;signed int player_hp=12
;word eaten_items=0
;word eaten_npcs=0
;const byte cakemax[]={74,47}
;byte cakelife[]={74,47}
;byte maidSleep=1
;Npc* fighting=nullptr
;static Textarr counter(Npc* npc,const char* npc_name,Textarr cout)

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

;Npc npcs[]={
  {.inventory=BRUSH}, // Maid
  {.inventory=NORMAL_SWORD|COIN,.hp=18,.maxhp=18,.avo=0.125,.threshold=1}, // Guard
  {.inventory=STEEL_SWORD|KNIFE|COIN|TWO_HEALTH_POTIONS,.hp=128,.maxhp=128,.avo=0.25,.threshold=0}, // Viscount
  {.inventory=NORMAL_SWORD|HEALTH_POTION,.hp=30,.maxhp=30,.avo=0.0625}, // Orc
  {.inventory=NORMAL_SWORD|APPLE|APPLES|HEALTH_POTION,.hp=52,.maxhp=52,.avo=0.1875,.threshold=0}, // Chef
  {.inventory=0,.avo=0.25}, // Human
  {.inventory=APPLES|APPLE,.hp=24,.maxhp=24,.avo=0.03125,.threshold=1}, // Tree
  Npc() // Family Member
}

;Location locs[]={{0},
  {.type=ROOM,.south=4,.west=6,.items=CHAIR,.description=
    R"(It's a conservatory.
There is a nice view of the lanscape and forest.)"},
  {.type=CLEARING,.north=6,.east=4,.npcs=TREE,.items=APPLE,.description=
    R"(It's surrounded by a wooden fence.)"},
  {.type=CORRIDOR,.east=5,.west=4,.npcs=MAID,.description=
    R"(It's a dark, moist, stone corridor.)"},
  {.type=ROOM,.north=1,.east=3,.west=2,.items=WOOD_SWORD,.description=
    R"(It's a small wodden room.)"},
  {.type=ROOM,.west=3,.npcs=GUARD,.items=STAIRCASE+KNIFE+COIN,.description=
    R"(It's a stone, prison-like room.
There is an inaccessable broken door high up on the wall.
There is a metal pole that is connected to a room above through a hole in the wall.
You don't think you could climb the pole, but you might be able to slide down it to get back to this room from above.)"},
  {.type=CLEARING,.east=1,.south=2,.items=APPLE,.description=
    R"(You stand on a patch of grass on a tiny hill in an open area.
The breeze feels nice.)"},
  {.type=BASEMENT,.east=8,.up=4,.description=
    R"(Sunlight creeps through between the floorboards above.
The stone floor seems to creak, and the sound of dripping water echoes from the east.)"},
  {.type=ROOM,.south=9,.west=7,.npcs=ORC,.description=
    R"(The room feels oppressive.
There is a human trapped in a cell to the north.)"},
  {.type=CAVE,.north=8,.east=27,.west=10,.items=RUSTED_SWORD,.description=
    R"(Stone surrounds you.)"},
  {.type=FOREST,.north=2,.east=9,.items=APPLES,.description=
    R"(You stand at the entrance to a cave.
The cave is concealed in a lush forest.
If you were to leave, you don't think you could find your way back here easily through the forest.)"},
  {.type=TREASURY,.west=8,.items=HEALTH_POTION+NORMAL_SWORD+CHAIR,.description=
    R"(Much of the room is foul.
There is a seemingly blocked toilet in the corner.
The rest of the place is lavish with plenty of tools that you can't identify.)"},
  {.type=PRISON,.east=13,.south=8,.npcs=HUMAN,.items=APPLE*3+HEALTH_POTION,.description=
    R"(There are chains and bars.)"},
  {.type=HALL,.npcs=CHEF,.items=RESTAURANT+LEVER,.description=
    R"(The tension is high in this grand hall.
The torches on either wall crackle; adding to the atmosphere.
The entrance to the room is gone.)"},
  {.type=ROOM,.east=20,.south=15,.down=13,.description=
    R"(A dusty, dilapidated wooden room.
There is a hole in both the ceiling and the floor.)"},
  {.type=HALL,.north=14,.east=21,.west=16,.description=
    R"(A small, yet clearly well used meeting hall.)"},
  {.type=TREASURY,.east=15,.up=17,.items=STEEL_SWORD,.description=
    R"(A soft amber glow barely illuminates the room.
There's stuff here that you can't see, let alone identify.)"},
  {.type=ART_ROOM,.north=18,.south=19,.down=16,.description=
    R"(Stacks of both old and recently painted paintings sit in a well lit room.)"},
  {.type=COURTROOM,.east=14,.south=17,.npcs=VISCOUNT,.description=
    R"(Soft sunlight shines into this grand courtroom.)"},
  {.type=ROOM,.north=17,.down=24,.description=
    R"(There is a hole in the floor.
The room seems intended for fast access to the bedroom below.)"},
  {.type=BEDROOM,.south=21,.west=14,.description=
    R"(Light shines through a window onto a four poster bed.)"},
  {.type=DINETTE,.north=20,.south=22,.description=
    R"(A grand dining room.
There is an entrance from the west; covered by some kind of banner, which is too high to reach.)"},
  {.type=ROOM,.north=21,.west=23,.items=HEALTH_POTION,.description=
    R"(It's a small storage room.)"},
  {.type=CORRIDOR,.east=22,.west=24,.description=
    R"(Light shines into this long corridor from the south.)"},
  {.type=BEDROOM,.east=23,.west=25,.description=
    R"(It's a lavish bedroom with an en suite to the south.
You would not be able to fit inside the en suite...)"},
  {.type=HALL,.north=26,.east=24,.description=
    R"(An inviting hall, clearly intended to welcome guests into this place which you now suspect to be some kind of manor.)"},
  {.type=ART_ROOM,.south=25,.items=LEVER,.description=
    R"(The room seems well used as an exit, but dusty paintings hang on dusty walls.)"},
  {.type=CAVE,.west=9,.description=
    R"(At the cave's end, there is a warm cake on a table-like ledge.)"},
  {.type=FOREST,.description=
    R"(You are already deep in the forest.
You don't think you could ever find your way back to that building again.)"},
  {.type=FOREST,.description=
    R"(You have picked up the scent of your village.
You are beginning to find your way home.)"},
  {.type=FOREST,.description=
    R"(You recognise this place!
At long last, you are finally almost home!)"},
  {.type=VILLAGE,.npcs=FAMILY_MEMBER,.description=
    R"(You stand at the entrance to your village.)"}}

;static std::int_least8_t parse_com_check(const char** arr,int arr_size){
    for (ibyte i=0;i<arr_size;i++){
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

    ;bool using_non_ascii=false; 
    ;const ibyte command_enum_length=sizeof(command_enum)/sizeof(command_enum[0])

    ;const char* commands[command_enum_length] // Mutable vaiable pointing to constant data.
    ;for (ibyte i=0;i<command_enum_length;i++) // Set the values in the commands array.
       {commands[i]=*command_enum+i*sizeof(command_enum[0]);} // Values are pointers to constant chars declared in global scope.

    ;ibyte i=0
    ;while (i < inp_str.length()){
        using_non_ascii=using_non_ascii||(128 & inp_str[i]); // Ensure case conversion can be disabled if non ascii is detected.
        for (ibyte j=0;j<command_enum_length;j++){
            if (*commands[j]!='\0' && (using_non_ascii?inp_str[i]:std::toupper(inp_str[i]))==*commands[j]) {commands[j]++;}}
        i++;
        out.com=parse_com_check(commands,command_enum_length);
        if (out.com!=-1){break;}
    }
    if (i>=inp_str.length() && out.com==-1){return out;} // If the while-loop didn't break, return with the error value left at 2.
    ;out.err=1 // Reduce the error value from 2 to 1, to show that the first step completed successfuly.

    ;const ibyte full_enum_length=sizeof(full_enum)/sizeof(full_enum[0])
    ;i=out.com<20? i : 0 // i if out.com<20 else 0
    ;out.com=out.com<40 ?(out.com%10): 10
    
    ;const char* objs[full_enum_length] // Mutable vaiable pointing to constant data.
    ;for (ibyte j=0;j<full_enum_length;j++) // Set the values in the objs array.
       {objs[j]=*full_enum+j*sizeof(full_enum[0]);} // Values are pointers to constant chars declared in global scope.

    ;while (i < inp_str.length()){
        for (ibyte j=0;j<full_enum_length;j++){
            if (*objs[j]!='\0' && (using_non_ascii?inp_str[i]:std::tolower(inp_str[i]))==*objs[j]) {objs[j]++;}}
        i++;
        out.obj=parse_com_check(objs,full_enum_length);
        if (out.obj!=-1){break;}
    }
    if (i>=inp_str.length() && out.obj==-1){return out;} // If the while-loop didn't break, return with the error value left at 1.
    ;out.err=0 // Set the error value to 0, to show that the first step completed successfuly.

    ;out.obj=(out.obj>=64? out.obj-16 : out.obj)%32
    ;return out
;}

;[[nodiscard]]
static inline Textarr check_orc(Textarr cout){
  if(npc_uint2(eaten_npcs,3)==0){
    if(locs[8].items & CHAIR && !(npcs[3].inventory & CHAIR)){
      npcs[3].inventory=npcs[3].inventory^CHAIR;
      locs[8].items=locs[8].items^CHAIR;
      (cout << "\"\033[92;40mOohhh a chair!\033[0m\"\n")-5;
      (cout << "The orc sat down.\n")-2;
      (cout << "\"\033[92;40mThanks man!\033[0m\"\n")-5;
    }
    if(locs[8].items & COIN && !(npcs[3].inventory & COIN)){
      npcs[3].inventory=npcs[3].inventory^COIN;
      locs[8].items=locs[8].items^COIN;
      (cout << "\"\033[92;40mOohhh a coin!\033[0m\"\n")-5;
      (cout << "The orc took the coin.\n")-2;
      (cout << "\"\033[92;40mThanks man!\033[0m\"\n")-5;
  }}
  if((npc_uint2(eaten_npcs,3)>0 || npcs[3].hp<=0 || npcs[3].inventory & (CHAIR | COIN))&& locs[8].east==0){
    locs[8].east=11;
    cout << "The \033[1meastern\033[0m room is now open.\n";
  }
  if((npc_uint2(eaten_npcs,3)>=3)&& locs[8].north==0){
    (((cout
    << "There is a key in the viscera.\n") - 5)
    << "You pick up the key.\n") - 6;
    goto unlock;
  }
  if((npcs[3].hp<=0)&& locs[8].north==0){
    (((cout
    << "The orc dropped a key.\n") - 5)
    << "You pick up the key.\n") - 6;
    goto unlock;
  }
  if(((npcs[3].inventory & (CHAIR | COIN))==(CHAIR | COIN))&& locs[8].north==0){
    ((cout
    << "The orc gave you a key.\n") - 5);
    goto unlock;
  }
  return cout;

  unlock:
  (((((cout
  << "You used the key to unlock the prison cell in the north.\n") -6)
  << "The door opened. The \033[1mhuman\033[0m is free!\n") -6)
  << "The key disapeared.\n")-6
  ;locs[8].north=12
  ;locs[8].description="The room feels slightly less oppressive now."
  ;return cout;
}

static inline byte check_speech(byte npc_no){
  if(npc_uint2(eaten_npcs,npc_no)!=0 || npc_no==2 || npc_no==4 || npc_no==6 || npc_no==7)
    return 0;
  switch(npc_no){
    case 0:
      if(locs[13].up==0)
        return 0;
      if(VISCOUNT_MOVED && npcs[2].hp<=0)
        return 8;
      if(inventory & STAIRCASE)
        return 6;
      return 7;
    case 1:
      if(inventory & STAIRCASE)
        return 6;
      if(locs[13].up!=0)
        return 8;
      if((locs[5].items & STAIRCASE)==0)
        return 7;
      return 0;
    case 3:
      if(HUMAN_EATEN_BY_ORC)
        return 7;
      if(npcs[3].inventory & CHAIR)
        return 8;
      if(npcs[3].inventory & COIN)
        return 6;
      return 0;
    case 5:
      if(loc!=12){
        if(HUMAN_EATEN_BY_ORC)
          return 6;
        return 7;}
      return 0;
  }
  return 0;
}

[[nodiscard]]
static Textarr describe(const Location location, Textarr cout){
  cout 
  << "You are in a " << type_enum[locs[loc].type]
  << '.' << '\n'
  << locs[loc].description << '\n'
  ;if (location.items & ~LEVER){
    cout << "\nOn the floor, there is:\n";
    for (int i=0;i<15;i++)
      if (location.items & 1<<i)cout
      << "-"
      << full_enum[16+i]
      << '\n';}
  for(ibyte i=0;i<8;i++)
    if(1<<i & location.npcs)
      cout
      << npc_info[i][check_speech(i) && npc_info[i][check_speech(i)]!=nullptr? check_speech(i):
         npc_uint2(eaten_npcs,i)+3*int(npcs[i].hp<=0)]
      << '\n'
  ;if (location.north>0)
    cout << "NORTH: ->"
    << type_enum[locs[location.north].type]
    << '\n';
  else if ((locs[loc].type==CLEARING || locs[loc].type==FOREST)&& (inventory & RESTAURANT))
    cout << "There is a vast expance of forest to the \033[1mnorth\033[0m.\n";
  if (location.east>0)
    cout << "EAST: ->"
    << type_enum[locs[location.east].type]
    << '\n';
  else if ((locs[loc].type==CLEARING || locs[loc].type==FOREST)&& (inventory & RESTAURANT))
    cout << "There is a vast expance of forest to the \033[1meast\033[0m.\n";
  if (location.south>0)
    cout << "SOUTH: ->"
    << type_enum[locs[location.south].type]
    << '\n';
  else if ((locs[loc].type==CLEARING || locs[loc].type==FOREST)&& (inventory & RESTAURANT))
    cout << "There is a vast expance of forest to the \033[1msouth\033[0m.\n";
  if (location.west>0)
    cout << "WEST: ->"
    << type_enum[locs[location.west].type]
    << '\n';
  else if ((locs[loc].type==CLEARING || locs[loc].type==FOREST)&& (inventory & RESTAURANT))
    cout << "There is a vast expance of forest to the \033[1mwest\033[0m.\n";
  if (location.up>0)
    cout << "UP: ->"
    << type_enum[locs[location.up].type]
    << '\n';
  if (location.down>0)
    cout << "DOWN: ->"
    << type_enum[locs[location.down].type]
    << '\n';
  return cout;}

static inline std::ostream& operator<<(std::ostream& inp, const Textarr outp);

// Version of the main `describe` function that creates a new `Textarr` and immediately prints it.
static void describe(const Location location){
  char buff[24]={0};
  Textarr cout=describe(location,{.varStrEnd=buff});
  std::cout << cout;
}

[[nodiscard]]
static inline Textarr pull_lever(Textarr cout,bool eats){
  if ((loc!=13 && loc!=26)|| !(locs[loc].items & LEVER))
    return cout;
  locs[loc].items=locs[loc].items ^ LEVER;
  (cout << (eats
    ? "You bit the lever, and pulled it with your mouth.\n" 
    : "You pulled the lever.\n"))
    - 4;
  if(loc==13){
    locs[loc].up=14;
    (cout << "A spiral staircase is lowered from the ceiling.\nYou can now go \033[1mup\033[0m.\n")-6;
  }else{
    locs[loc].down=5;
    (((cout << "A trapdoor opens up.")-4
    << "\nThere's a pole going through that you could ride \033[1mdown\033[0m.") -3
    << "\nYou don't think you'll be able to climb back up though...\n") -2;
  }
  (cout << "The lever disappears.\n") -2;
  return cout;
}

;[[nodiscard]]
Textarr CakeRoom(Textarr cout,byte& cakelife,const byte cakemax){
  if (cakelife==0){return cout;}
  if (player_hp>=player_hp_max){return cout<<"You don't need any cake right now.\n";}
  cout << "You started eating the cake.\n";
  player_hp+=cakelife;
  if(player_hp>player_hp_max){
    cakelife=player_hp-player_hp_max;
    player_hp=player_hp_max;
    cout<<"You are fully healed!\n"
    <<(byte)((cakelife*100+cakemax)/cakemax)<<'%'<<" of the cake remains.\n";}
  else{
    cakelife=0;
    cout<<"You finished eating the cake.\n"
    <<"The cake is gone.\n";
    if(cakemax==74)
      locs[27].description="The cake is gone.";
    }
  return cout;
}

;Textarr do_action(parse_result &action){
    ;Location &location=locs[loc]
    ;word item_bit // In event of undefined behaviour; initialise at zero.
    ;Textarr cout={.varStrEnd=outBuff}
    ;if(action.err==2){
        cout<<"Invalid command. Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, QUIT, RESET, and HELP.\n\n";
        return cout;}
    ;if(action.err==1){
        if(action.com>=QUIT){return cout;}
        cout<<"Invalid object to "<<command_enum[action.com]<<"!\n";
        return cout;}

    ;const char* obj_name=full_enum[action.obj]
    ;const char* npc_name=nullptr
    ;bool multi_item
    ;if(fighting)for(ibyte i=0;i<8;i++){if(&npcs[i]==fighting){npc_name=full_enum[i];break;}}
    ;switch(action.com){
        case GO:
          if(fighting!=nullptr){
            cout << "You can't leave while you are in a fight!\n";
            return cout;}
          switch(action.obj){
            case NORTH:
              if(location.north==0 && !(inventory & RESTAURANT) && !(location.type==CLEARING || location.type==FOREST)){
                cout<<"No way to go north.\n";
                return cout;}
              loc=location.north;
              cout<<"You went north.\n";
              break;
            case EAST:
              if(location.east==0 && !(inventory & RESTAURANT) && !(location.type==CLEARING || location.type==FOREST)){
                cout<<"No way to go east.\n";
                return cout;}
              loc=location.east;
              cout<<"You went east.\n";
              break;
            case SOUTH:
              if(location.south==0 && !(inventory & RESTAURANT) && !(location.type==CLEARING || location.type==FOREST)){
                cout<<"No way to go south.\n";
                return cout;}
              loc=location.south;
              cout<<"You went south.\n";
              break;
            case WEST:
              if(location.west==0 && !(inventory & RESTAURANT) && !(location.type==CLEARING || location.type==FOREST)){
                cout<<"No way to go west.\n";
                return cout;}
              loc=location.west;
              cout<<"You went west.\n";
              break;
            case UP:
              if(location.up==0){
                cout<<"No way to go up.\n";
                return cout;}
              loc=location.up;
              cout<<"You went up.\n";
              break;
            case DOWN:
              if(location.down==0){
                cout<<"No way to go down.\n";
                return cout;}
              loc=location.down;
              cout<<"You went down.\n";
              break;
            default:
              cout<<obj_name<<" is an invalid direction.\n";
              return cout;
          }
          // `loc` should only be 0 if the player has the restaurant, and is in a clearing or forest, in which case it MUST be changed to a non-zero value.
          if(loc==0){
            if(&locs[30]==&location)
              loc=31;
            else if(&locs[29]==&location)
              loc=30;
            else if(&locs[28]==&location)
              loc=29;
            else
              loc=28;}
          ;cout=describe(locs[loc],cout)
          ;if(loc==5 && !GUARD_ROOM_VISIT){
            flags=flags|16; // Effectively `GUARD_ROOM_VISIT=true;`
            cout<<"Use MEET GUARD or CHECK GUARD to speak with the guard\nUse GET or LIFT to pick up an item.\n";}
          ;if(loc==4 && (inventory&STAIRCASE)){cout<<"You sense there may be somthing more to this room.\n";}
          ;if(loc==12 && !HUMAN_CHECKED){
            flags=flags|4; // Effectively `HUMAN_CHECKED=true;`
            action.com=HUMAN_CONVERSATION;
            return cout;}
          ;if(loc==13 && (CHEF & locs[13].npcs) && npcs[4].hp>0){
            cout << "The \033[1mchef\033[0m attacks.\n";
            fighting=&npcs[4];}
          ;if(loc==27)
            cout=CakeRoom(cout,cakelife[0],cakemax[0]);
          ;if(loc==21 && cakelife[1]>0){
            cout<<"There is cake.\n";
            cout=CakeRoom(cout,cakelife[1],cakemax[1]);}
          ;if(loc==26 && !ART_ROOM_VISIT)
            flags=flags|32; // Effectively `GUARD_ROOM_VISIT=true;`
           else if(loc==26 && locs[26].down==0)
            cout<<"You notice a \033[1mlever\033[0m behind a painting!\n";
          ;if(loc==3 && (inventory & RESTAURANT) && npcs[2].hp>0){
            (((((((((((((((cout
            << "A viscount approaches from behind.\n") - 4)
            << "\"YOU!!!\"\n") - 6)
            << "\"That was my \033[1mdaughter's\033[0m restaurant!\"\n") - 3)
            << "\"And you \033[1mtook\033[0m it!\"\n") - 5)
            << "\"YOU") -2)
            << " WILL") -2)
            << " \033[1mPAY!\033[0m\"\n") -4)
            << "The \033[1mviscount\033[0m attacks.\n") -2
            ;if(!(locs[3].npcs & VISCOUNT)){
              locs[18].npcs=0;
              locs[3].npcs=locs[3].npcs | VISCOUNT;
              flags=flags|2 /*Effectively `VISCOUNT_MOVED=true*/;}
            ;fighting=&npcs[2]
            ;cout=counter(fighting,full_enum[2],cout);}
          ;break;
        case GET:
          if(action.obj<16){
            cout<<obj_name<<" is not an item.\n";
            return cout;}
          ;item_bit=1<<(action.obj-16)
          ;multi_item=check_can_hold_multiple(item_bit)
          ;if (((item_bit | (multi_item? item_bit<<1:0)) & location.items)==0){
            cout<<"There is no "<<obj_name<<" on the ground.\n";
            return cout;}
          if(item_bit==LEVER)
            return pull_lever(cout,false);
          if (multi_item){
            if (item_uint2(inventory,action.obj-16)==3){
              cout<<"Too many "<<obj_name<<"s are already in your inventory.";
              return cout;
            }}
          else{if(item_bit & inventory){
            cout<<obj_name<<" is already in your inventory.\n";
            return cout;}}
          ;location.items=location.items ^ item_bit
          ;if(location.items&item_bit){
            location.items=location.items ^ (item_bit<<1);
            assert(multi_item);
            assert(item_uint2(location.items,action.obj-16)==1);}
          ;inventory=inventory ^ item_bit
          ;if ((inventory&item_bit)==0){
            inventory=inventory ^ (item_bit<<1);
            assert(multi_item);
            assert(item_uint2(inventory,action.obj-16)==2);}
          ;cout<<"You picked up the "<<obj_name<<'.' << '\n'
          ;if(item_bit==STAIRCASE){cout<<"Maybe you could put this somewhere else?\n";}
          ;if(item_bit==RESTAURANT && locs[13].up==0){cout<<"???\nThere was a \033[1mlever\033[0m under the restarunt.\n";}
          ;if(fighting) cout=counter(fighting,npc_name,cout);
          break;
        case DROP:
          if(action.obj<16){
            cout<<obj_name<<" is not an item.\n";
            return cout;}
          ;item_bit=1<<(action.obj-16)
          ;multi_item=check_can_hold_multiple(item_bit)
          ;if(multi_item){
            if(item_uint2(location.items,action.obj-16)==3){
              cout<<"The floor seems full...\n";
              return cout;}}
          else{
            if (item_bit & location.items){
              cout<<obj_name<<" is already on the floor.\n";
              return cout;}}
          if(((item_bit | (multi_item? item_bit<<1:0)) & inventory)==0){
            cout<<"You don't have any "<<obj_name<<'.' << '\n';
            return cout;}
          if(loc==4 && (item_bit & STAIRCASE)){
            ;inventory=inventory ^ item_bit
            ;locs[4].down=7
            ;cout
            << "The staircase fell through the floor.\n"
            ;return cout;}
          if(loc==31 && (item_bit & RESTAURANT)){
            action.com=WIN_STATE;
            return cout;}
          ;location.items=location.items ^ item_bit
          ;if((location.items&item_bit)==0){
            location.items=location.items ^ (item_bit<<1);
            assert(multi_item);
            assert(item_uint2(location.items,action.obj-16)==2);}
          ;inventory=inventory ^ item_bit
          ;if(inventory&item_bit){
            inventory=inventory ^ (item_bit<<1);
            assert(multi_item);
            assert(item_uint2(inventory,action.obj-16)==1);}
          ;cout<<"The "<<obj_name<<" landed on the floor.\n"
          ;if(fighting) cout=counter(fighting,npc_name,cout);
          else if(loc==8) cout=check_orc(cout);
          break;
        case FIGHT:
          if(action.obj>=8){
            cout<<"Can't fight "<<obj_name<<'.' << '\n';
            return cout;}
          item_bit=1<<action.obj;
          if((location.npcs & item_bit)==0){
            cout << "The "<<obj_name<<" is not in this room.\n";
            return cout;}
          if(npcs[action.obj].hp<=0){
            cout << "You have already defeated the " << obj_name << '.' << '\n';
            return cout;}
          if((action.obj==5 and npc_uint2(eaten_npcs,action.obj)>0) or npcs[action.obj].hp<=1){
            npcs[action.obj].hp=0
            ;cout << "You... WIN!\n"
            << "... yeah, it can't fight back...\n"
            << "You won.\n";
            return cout;}
          fighting=&npcs[action.obj];
          cout << "You are now fighting the " << obj_name << '.' << '\n';
          break;
        case MEET:
          // First check if it is somthing that is actually present.
          if(action.obj<8){
            item_bit=1<<action.obj;
            if((location.npcs & item_bit)==0){
              cout<<"The "<<obj_name<<" is not in this room.\n";
              return cout;}
            if(fighting){
              if(fighting!=&npcs[action.obj]){
                cout << "Your focus is on " << npc_name << '.' << '\n';
                return cout;}
              cout << "They have "<<fighting->hp<<" hp.\n";}
            else
              cout
              << npc_speech[action.obj][check_speech(action.obj)? check_speech(action.obj):
                 npc_uint2(eaten_npcs,action.obj)+3*int(npcs[action.obj].hp<=0)]
              << '\n';}
          else if(action.obj<16){
            item_bit=0; // This variable will be used differently on this path. It will be treated like a bool.
            switch(action.obj){
              case NORTH:
                item_bit=location.north;
                break;
              case EAST:
                item_bit=location.east;
                break;
              case SOUTH:
                item_bit=location.south;
                break;
              case WEST:
                item_bit=location.west;
                break;
              case UP:
                item_bit=location.up;
                break;
              case DOWN:
                item_bit=location.down;
                break;
              case LEFT:
                item_bit=1;//location.left;
                break;
              case RIGHT:
                item_bit=1;//location.right;
                break;}
            if(item_bit!=0){
              cout<<"There is nothing "<<obj_name<<'.' << '\n';
              return cout;}}
          else{
            item_bit=1<<(action.obj-16);
            if (((location.items|inventory) & item_bit)==0){
              cout<<"There is no "<<obj_name<<'.' << '\n';
              return cout;}
            cout << item_info[action.obj-16] << '\n';// Then display info about it.
            return cout;}
          if(fighting) cout=counter(fighting,npc_name,cout);
          break;
        case EAT:
          // First check if it is somthing that is actually present.
          if(action.obj<8){
            item_bit=1<<action.obj;
            if(item_bit & ((eaten_npcs>>8)&(eaten_npcs%256))){ // & both bytes of eaten_npcs together before comparing it to item_bit.
              cout<<"You have already eaten the "<<obj_name<<'.' << '\n';
              return cout;}
            if((location.npcs & item_bit)==0){
              cout<<"The "<<obj_name<<" is not in this room.\n";
              return cout;}
            if(npc_uint2(eaten_npcs,action.obj)!=npcs[action.obj].threshold or npcs[action.obj].hp<=1){
              ;player_hp+=hp_enum[action.obj]>>npc_uint2(eaten_npcs,action.obj)
              ;eaten_npcs=eaten_npcs^(item_bit|((item_bit & eaten_npcs)<<8))
              ;npcs[action.obj].hp=npcs[action.obj].hp>>1
              ;cout << "You ate the " << obj_name << '.' << '\n'
              ;if(fighting==&npcs[3])
                cout=check_orc(cout);
            ;}else if(fighting!=&npcs[action.obj]){
              ;cout << "The "<<obj_name<<" defended themselves!\n"
              ;fighting=&npcs[action.obj]
              ;npc_name=obj_name
            ;}

            if(npc_uint2(eaten_npcs,action.obj)>=3){
              location.npcs=location.npcs^item_bit;
              location.items=location.items | npcs[action.obj].inventory | (item_bit!=TREE? BONE:0);
              if(fighting==&npcs[action.obj]){
                cout << "You win!!!\n";
                if(fighting==&npcs[3])
                  cout=check_orc(cout);
                fighting=nullptr;}}
            if(fighting==&npcs[action.obj]){
              double roll=ran();
              if(roll*2>=fighting -> avo){
                double roll2=2+((double)rand())/((double)RAND_MAX/3);
                word atk=(word)roll2;
                fighting->hp=fighting->hp-atk>0?fighting->hp-atk:0;
                if(fighting->hp>1)cout << "You bit for "<<atk<<" damage!\n";
                player_hp+=int(roll2/2+ran());}
              else if(roll>=0.05 and fighting->hp>1)cout << "The "<<npc_name<<" dodged.\n";
              else if(fighting->hp>1)cout << "The bite missed.\n";
              if(fighting->hp<=1){
                fighting->hp=0;
                cout << "You win!!!\n";
                if(fighting==&npcs[3])
                  cout=check_orc(cout);
                fighting=nullptr;}}
            }
          else if(action.obj<16){
            cout<<"Ya can't eat a direction...\n";
            return cout;}
          else{
            item_bit=1<<(action.obj-16);
            if (((location.items|inventory) & (item_bit| (check_can_hold_multiple(item_bit)? item_bit<<1:0)))==0){
              cout<<"There is no "<<obj_name<<'.' << '\n';
              return cout;}
            if(action.obj-16==15)
              return pull_lever(cout,true);
            bool on_floor=(location.items & item_bit)||(check_can_hold_multiple(item_bit)&&item_uint2(location.items,action.obj-16));
            if(hp_enum[action.obj]==0)
              player_hp=0;
            else
              cout << item_food[action.obj-16];
            if(player_hp+hp_enum[action.obj]<=(player_hp_max>=player_hp?player_hp_max:player_hp))player_hp+=hp_enum[action.obj];
            else if(player_hp<player_hp_max)player_hp=player_hp_max;
            if(player_hp<=0)cout << item_death[action.obj-16];
            if((not check_can_hold_multiple(item_bit))||(item_uint2(on_floor? location.items:inventory,action.obj-16)%2)){
              if(on_floor){location.items=location.items^item_bit;}
              else{inventory=inventory^item_bit;}}
            else{
              if(on_floor){
                location.items=location.items^(item_bit | item_bit<<1);
                assert(!(location.items & (item_bit<<1)));}
              else{
                inventory=inventory^(item_bit | item_bit<<1);
                assert(!(inventory & (item_bit<<1)));}}
            }
          if(fighting)cout=counter(fighting,npc_name,cout);
          break;
        case SWING:
          if(action.obj<16){
            cout<<obj_name<<" is not an item.\n";
            return cout;}
          item_bit=1<<(action.obj-16);
          if(item_bit==LEVER && (item_bit & location.items))
            return pull_lever(cout,false);
          if((item_bit & inventory)==0){
            cout<<"You don't have any "<<obj_name<<'.' << '\n';
            return cout;}
          cout << "You swung the " << obj_name << '.' << '\n';
          if(fighting==nullptr){
            if((item_bit & STAIRCASE)&& loc==4){
              inventory=inventory ^ item_bit;
              locs[4].down=7;
              cout << "You lost your grip.\n";
              cout << "The staircase fell through the floor.\n";
              return cout;}
            cout << "... but nothing happened.\n";
            return cout;}
          double roll=ran();
          if(roll>=fighting->avo){
            ;cout << "The attack connected!\n"
            ;word atk=item_dmg[action.obj-16]+ran()+(item_dmg[action.obj-16]*ran()/2)
            ;fighting->hp=fighting->hp-atk>=0?fighting->hp-atk:0
            ;cout << "You delt "<<atk<<" damage!\n"
            ;if(fighting->hp<=0){
              cout << "You win!!!\n";
              if(fighting==&npcs[3])
                cout=check_orc(cout);
              fighting=nullptr;
              return cout;}}
          else if(roll>=0.05)cout << "The "<<npc_name<<" dodged.\n";
          else cout << "The attack missed.\n";
          cout=counter(fighting,npc_name,cout);
          break;
    }
  if(loc==8)
    cout=check_orc(cout);
  if(player_hp<=0){
    cout << "GAME OVER!!!\n";
    action.com=GAME_OVER;}
  return cout;}

[[nodiscard]]
Textarr FreeHuman(char buff[]){
  Textarr cout={.varStrEnd=buff}
  ;(((((
  cout << human_speech[1])-16)
  << human_speech[4])-32)
  << human_speech[2])-3
  ;locs[12].npcs=0
  ;if(npcs[3].inventory & CHAIR || eaten_npcs & (ORC | ORC<<8))
    flags=flags|8;
  else
    flags=flags|1;
  return cout;
}

static Textarr counter(Npc* npc,const char* npc_name, Textarr cout){
  assert(npc_name!=nullptr);
  cout << "The "<<npc_name<<" attacks!\n";
  word dmg;

  if(std::rand()<(double)RAND_MAX/8)dmg=0;
  else{
    float wpn=0;
    for(ibyte i=0;i<15;i++){
      if(1<<i & npc -> inventory && item_dmg[i]>wpn)wpn=item_dmg[i];}
    float fdmg=wpn+((float)std::rand()/((float)RAND_MAX/5))-2.5;
    dmg=fdmg>0?(word)fdmg:0;
    player_hp-=dmg;}
  
  if(dmg)cout << "You were hit for " << dmg <<" damage!\n";
  else cout << "The attack missed.\n";

  if(npc==&npcs[2] && loc==3 && VISCOUNT_MOVED && npcs[0].hp>0 && !((eaten_npcs & 0401)==0401) && !(maidSleep & 0200)){
    if(eaten_npcs & 0400 && maidSleep &0100){
      maidSleep<<=1;
      cout<<"The maid woke up!\n\"\033[1mOWWwwww\033[0mwwwwwwwww!\"\n\"What the **** was that for?\"\n";}
    else if(eaten_npcs & 1 && maidSleep &076 && player_hp<=28 && npc->hp<=72){
        maidSleep=0100;
        cout<<"The maid is still sleeping.\n\"\033[3;95m ... do it ... again.\033[0m\"\n";}
    else if(!(eaten_npcs & 0401)){
      if(maidSleep &020 && player_hp<=24 && npc->hp<=80){
        maidSleep<<=1;
        cout<<"The maid is still sleep talking.\n\"""\033[3;95m ... please ... eat me...\033[0m\"\n";}
      else if(maidSleep &8 && player_hp<=32 && player_hp > 0 && npc->hp<=88){
        maidSleep<<=1;
        cout<<"The maid is sleep talking.\nYou can kind of make out some of the words.\n\"\033[3;95muhh ... eat ... ... me ...\033[0m\"\n";}
      else if(maidSleep &4 && player_hp<=48 && player_hp > 0 && npc->hp<=96){
        maidSleep<<=1;
        cout<<"The sleeping maid is murmuring.\nJust what is the maid dreaming about?\n";}
      else if(maidSleep &2 && player_hp<=64 && npc->hp<=112){
        maidSleep<<=1;
        cout<<"The sleeping maid is mumbling.\n";}
      else if(maidSleep &1 && npc->hp<=120){
        maidSleep<<=1;
        cout<<"The sleeping maid rolled over.\n";}}}

  return cout;
}

static inline std::ostream& operator<<(std::ostream& inp, const Textarr outp){
  for(ibyte i=0;i<outp.end;++i)
    inp << outp.arr[i];
  return inp;}

;int main() {
    ;std::cout<<"You are on an adventure to find a source of nourishment, and have entered a strange building you have found in the forest.\n"
    << "Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, SWING, QUIT, RESET, and HELP.\n\n"
    ;describe(locs[loc])
    ;std::cout << "What will you do?\n"
    ;char input_buffer[256]
    
    ;parse_result action
    ;while (action.com<QUIT){
        ;std::cout<<"HP: "<<player_hp<<"/"<<player_hp_max<<" >"<<std::flush
        ;std::cin.getline(input_buffer,255)
        ;action=parse(input_buffer)
        ;Textarr text = do_action(action)
        ;std::cout<<text
        ;clearOutBuff()
        ;if(action.com==HUMAN_CONVERSATION){
          ;bool check=true
          ;std::cout<<human_speech[0]<<"[Y/n] "
          ;std::cin.getline(input_buffer,255)
          ;for(ibyte i=0;input_buffer[i]!='\0'&&i<255;++i){
            if((input_buffer[i] &223)=='N'){
              check=false;
              break;}}
          if(check){
            ;text=FreeHuman(outBuff)
            ;std::cout << text
            ;clearOutBuff()
          ;}  
        action.com=0;}
    ;}
    if(action.com==WIN_STATE)
      std::cout<<"YOU WIN!!!";
;}