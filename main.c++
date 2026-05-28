#include <iostream> // For outputting to, and inputting from the terminal.
#include <string> // For the C++ specific dynamic string.
#include <chrono> // For making the program wait.
#include <thread> // For making the program wait.
#include <cstdlib> // For random number generation.
#include <cctype> // For upper/lower case conversion.
#include <cstdint> // For better practice int types.
#include <cassert> // To alert if any program states intended to be impossible are reached.

// Set datatype names. to avoid needing to type longer names repeatedly.
using byte=std::uint8_t;  // A byte will be a one byte positive integer
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
-64,3,0,12,0,1,0,-64,0,-2,-96,-128,0,0,-1,0}
//;const char eat_text[64][4][128]

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
{"room","clearing","corridor","prison","bedroom","courtroom","forest","village","basement","treasury","dinette","art room","cave","hall"
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
    QUIT,
    RESET,
    HELP
}

;const char command_enum[42][6]=
{  "GO","GET", "DROP", "FIGHT", "MEET", "EAT", "SWING", "QUIT", "RESET", "HELP",\
"VISIT","LIFT","THROW","HIT",  "CHECK", "SWALL","USE",  "EXIT", "RESTA", "HINT",\
  "行","取",   "落",   "戦",     "合",   "食",   "振",    "辞",   "リ",    "助",\
  "訪","拾",   "投",   "当",     "見",   "飲",   "使",    "出",   "再",    "仄",\
"SAVE","セ"}

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
    word items=0;
    std::string description="MISSING DESCRIPTION";
    std::string jp_description="エラー: 説明がありません";
}

;struct Npc{
    word inventory=0;
    word hp=4;
    float avo=0.05;
    byte threshold=4;
}

;byte loc=4
;word inventory=HEALTH_POTION
;signed int player_hp=12
;word eaten_items=0
;word eaten_npcs=0
;Npc* fighting=nullptr

#define item_uint2(n,loc) (((n)>>(loc))%4) // Isolate 2 adjacent bits as a single integer.
#define npc_uint2(n,loc) (((((n)%256)&(1<<(loc)))?1:0)|((((n)>>8)&(1<<(loc)))?2:0)) // Isolate a bit in two adjacent bytes to make a 2-bit integer.
#define check_can_hold_multiple(arr) ((arr)&(APPLE|APPLES|HEALTH_POTION|TWO_HEALTH_POTIONS)) // Check if an item can be stacked.

Npc npcs[]={
  Npc(.inventory=BRUSH), // Maid
  Npc(.inventory=NORMAL_SWORD|COIN,.hp=48,.avo=0.125,.threshold=1), // Guard
  Npc(.inventory=STEEL_SWORD|KNIFE|COIN|TWO_HEALTH_POTIONS,.hp=128,.avo=0.25,.threshold=0), // Viscount
  Npc(.inventory=NORMAL_SWORD|HEALTH_POTION,.hp=64,.avo=0.0625), // Orc
  Npc(.inventory=NORMAL_SWORD|APPLE|APPLES|HEALTH_POTION,.hp=72,.avo=0.1875,.threshold=0), // Chef
  Npc(.avo=0.25), // Human
  Npc(.inventory=APPLES|APPLE,.hp=24,.avo=0.03125,.threshold=2), // Tree
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
    R"(The room feels oppressive.)"},
  {.type=CAVE,.north=8,.west=10,.items=RUSTED_SWORD,.description=
    R"(Stone surrounds you.)"},
  {.type=FOREST,.north=2,.east=9,.items=APPLES,.description=
    R"(You stand at the entrance to a cave.
The cave is concealed in a lush forest.
If you were to leave, you don't think you could find your way back here easily through the forest.)"},
  {.type=TREASURY,.west=8,.items=HEALTH_POTION+NORMAL_SWORD+CHAIR,.description=
    R"(Much of the room is foul.
There is a seemingly blocked toilet in the corner.
The rest of the place is lavish with plenty of tools that you can't identify.)"},
  {.type=PRISON,.east=13,.south=8,.npcs=HUMAN,.description=
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
    R"(The room seems intended for fast access to the bedroom below.)"},
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
    R"(It's a lavish bedroom with an en suite to the south.)"},
  {.type=HALL,.north=26,.east=24,.description=
    R"(An inviting hall, clearly intended to welcome guests into this place which you now suspect to be some kind of manor.)"},
  {.type=ART_ROOM,.south=25,.items=LEVER,.description=
    R"(The room seems well used as an exit, but dusty paintings hang on dusty walls.)"}}

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

    ;bool using_non_ascii=false; 
    ;const byte command_enum_length=sizeof(command_enum)/sizeof(command_enum[0])

    ;const char* commands[command_enum_length] // Mutable vaiable pointing to constant data.
    ;for (byte i=0;i<command_enum_length;i++) // Set the values in the commands array.
       {commands[i]=*command_enum+i*sizeof(command_enum[0]);} // Values are pointers to constant chars declared in global scope.

    ;byte i=0
    ;while (i < inp_str.length()){
        using_non_ascii=using_non_ascii||(128 & inp_str[i]); // Ensure case conversion can be disabled if non ascii is detected.
        for (byte j=0;j<command_enum_length;j++){
            if (*commands[j]!='\0' && (using_non_ascii?inp_str[i]:std::toupper(inp_str[i]))==*commands[j]) {commands[j]++;}}
        i++;
        out.com=parse_com_check(commands,command_enum_length);
        if (out.com!=-1){break;}
    }
    if (i>=inp_str.length() && out.com==-1){return out;} // If the while-loop didn't break, return with the error value left at 2.
    ;out.err=1 // Reduce the error value from 2 to 1, to show that the first step completed successfuly.

    ;const byte full_enum_length=sizeof(full_enum)/sizeof(full_enum[0])
    ;i=out.com<20? i : 0 // i if out.com<20 else 0
    ;out.com=out.com<40 ?(out.com%10): 10
    
    ;const char* objs[full_enum_length] // Mutable vaiable pointing to constant data.
    ;for (byte j=0;j<full_enum_length;j++) // Set the values in the objs array.
       {objs[j]=*full_enum+j*sizeof(full_enum[0]);} // Values are pointers to constant chars declared in global scope.

    ;while (i < inp_str.length()){
        for (byte j=0;j<full_enum_length;j++){
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

void describe(Location location){
  std::cout 
  << "You are in a " << type_enum[locs[loc].type] << ".\n"
  << locs[loc].description << '\n';
  if (location.items & ~LEVER){
    std::cout << "\nOn the floor, there is:\n";
    for (int i=0;i<15;i++)
      if (location.items & 1<<i)std::cout
      << "-"
      << full_enum[16+i]
      << '\n';}
  if (location.north>0)
    std::cout << "NORTH: ->"
    << type_enum[locs[location.north].type]
    << '\n';
  if (location.east>0)
    std::cout << "EAST: ->"
    << type_enum[locs[location.east].type]
    << '\n';
  if (location.south>0)
    std::cout << "SOUTH: ->"
    << type_enum[locs[location.south].type]
    << '\n';
  if (location.west>0)
    std::cout << "WEST: ->"
    << type_enum[locs[location.west].type]
    << '\n';
  if (location.up>0)
    std::cout << "UP: ->"
    << type_enum[locs[location.up].type]
    << '\n';
  if (location.down>0)
    std::cout << "DOWN: ->"
    << type_enum[locs[location.down].type]
    << '\n';}

;void do_action(parse_result action){
    ;Location &location=locs[loc]
    ;word item_bit // In event of undefined behaviour; initialise at zero.
    ;if(action.err==2){
        std::cout<<"Invalid command. Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, QUIT, RESET, and HELP.\n\n";
        return;}
    ;if(action.err==1){
        if(action.com>=QUIT){return;}
        std::cout<<"Invalid object to "<<command_enum[action.com]<<".\n";
        return;}

    ;const char* obj_name=full_enum[action.obj]
    ;const char* npc_name=nullptr
    ;bool multi_item
    ;if(fighting)for(int i=0;i<8;i++){if(&npcs[i]==fighting){npc_name=full_enum[i];break;}}
    ;switch(action.com){
        case GO:
          switch(action.obj){
            case NORTH:
              if(location.north==0){
                std::cout<<"No way to go north.\n";
                return;}
              loc=location.north;
              std::cout<<"You went north.\n";
              break;
            case EAST:
              if(location.east==0){
                std::cout<<"No way to go east.\n";
                return;}
              loc=location.east;
              std::cout<<"You went east.\n";
              break;
            case SOUTH:
              if(location.south==0){
                std::cout<<"No way to go south.\n";
                return;}
              loc=location.south;
              std::cout<<"You went south.\n";
              break;
            case WEST:
              if(location.west==0){
                std::cout<<"No way to go west.\n";
                return;}
              loc=location.west;
              std::cout<<"You went west.\n";
              break;
            case UP:
              if(location.up==0){
                std::cout<<"No way to go up.\n";
                return;}
              loc=location.up;
              std::cout<<"You went up.\n";
              break;
            case DOWN:
              if(location.down==0){
                std::cout<<"No way to go down.\n";
                return;}
              loc=location.down;
              std::cout<<"You went down.\n";
              break;
            default:
              std::cout<<obj_name<<" is an invalid direction.\n";
              return;
          }
          ;describe(locs[loc])
          ;break;
        case GET:
          if(action.obj<16){
            std::cout<<obj_name<<" is not an item.\n";
            return;}
          ;item_bit=1<<(action.obj-16)
          ;multi_item=check_can_hold_multiple(item_bit)
          ;if (((item_bit | (multi_item? item_bit<<1:0)) & location.items)==0){
            std::cout<<"There is no "<<obj_name<<" on the ground.\n";
            return;}
          if (multi_item){
            if (item_uint2(inventory,action.obj-16)==3){
              std::cout<<"Too many "<<obj_name<<"s are already in your inventory.";
              return;
            }}
          else{if(item_bit & inventory){
            std::cout<<obj_name<<" is already in your inventory.\n";
            return;}}
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
          ;std::cout<<"You picked up the "<<obj_name<<".\n"
          ;break;
        case DROP:
          if(action.obj<16){
            std::cout<<obj_name<<" is not an item.\n";
            return;}
          ;item_bit=1<<(action.obj-16)
          ;multi_item=check_can_hold_multiple(item_bit)
          ;if(multi_item){
            if(item_uint2(location.items,action.obj-16)==3){
              std::cout<<"The floor seems full...\n";
              return;}}
          else{
            if (item_bit & location.items){
              std::cout<<obj_name<<" is already on the floor.\n";
              return;}}
          if(((item_bit | (multi_item? item_bit<<1:0)) & inventory)==0){
            std::cout<<"You don't have any "<<obj_name<<".\n";
            return;}
          if(loc==4 && (item_bit & STAIRCASE)){
            ;inventory=inventory ^ item_bit
            ;locs[4].down=7
            ;std::cout
            << "The staircase fell through the floor.\n"
            ;return;}
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
          ;std::cout<<"The "<<obj_name<<" landed on the floor.\n"
          ;break;
        case FIGHT:
          if(action.obj>=8){
            std::cout<<"Can't fight "<<obj_name<<".\n";
            return;}
          // TODO Implement fighting.
          break;
        case MEET:
          // First check if it is somthing that is actually present.
          if(action.obj<8){
            item_bit=1<<action.obj;
            if((location.npcs & item_bit)==0){
              std::cout<<"The "<<obj_name<<" is not in this room.\n";
              return;}}
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
              std::cout<<"There is nothing "<<obj_name<<".\n";
              return;}}
          else{
            item_bit=1<<(action.obj-16);
            if (((location.items|inventory) & item_bit)==0){
              std::cout<<"There is no "<<obj_name<<".\n";
              return;
            }}
          // Then display info about it.
          //TODO implement.
          break;
        case EAT:
          // First check if it is somthing that is actually present.
          if(action.obj<8){
            item_bit=1<<action.obj;
            if(item_bit & ((eaten_npcs>>8)&(eaten_npcs%256))){ // & both bytes of eaten_npcs together before comparing it to item_bit.
              std::cout<<"You have already eaten the "<<obj_name<<".\n";
              return;}
            if((location.npcs & item_bit)==0){
              std::cout<<"The "<<obj_name<<" is not in this room.\n";
              return;}
            player_hp+=hp_enum[action.obj]>>npc_uint2(eaten_npcs,action.obj);
            eaten_npcs=eaten_npcs^(item_bit|((item_bit & eaten_npcs)<<8));}
          else if(action.obj<16){
            std::cout<<"Ya can't eat a direction...\n";
            return;}
          else{
            item_bit=1<<(action.obj-16);
            if (((location.items|inventory) & (item_bit| (check_can_hold_multiple(item_bit)? item_bit<<1:0)))==0){
              std::cout<<"There is no "<<obj_name<<".\n";
              return;}
            bool on_floor=(location.items & item_bit)||(check_can_hold_multiple(item_bit)&&item_uint2(location.items,action.obj-16));
            if(player_hp+hp_enum[action.obj]<=(64>=player_hp?64:player_hp))player_hp+=hp_enum[action.obj];
            else if(player_hp<64)player_hp=64;
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
          // Then resolve what happens when the object is eaten.
          //TODO implement
          break;
        case SWING:
          if(action.obj<16){
            std::cout<<obj_name<<" is not an item.\n";
            return;}
          item_bit=1<<(action.obj-16);
          if((item_bit & inventory)==0){
            std::cout<<"You don't have any "<<obj_name<<".\n";
            return;}
          // Then resolve what happens when the object is swung.
          //TODO implement
          break;
    }
;}

;int main() {
    ;std::cout<<"You are on an adventure to find a source of nourishment, and have entered a strange building you have found in the forest.\n"
    << "Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, QUIT, RESET, and HELP.\n\n"
    ;describe(locs[loc])
    ;std::cout << "What will you do? >"
    ;char input_buffer[256]
    ;std::cin.getline(input_buffer,255)
    
    ;parse_result action=parse(input_buffer)
    ;while (action.com!=QUIT){
        ;do_action(action)
        ;std::cout<< '{' <<(int) action.com << ',' <<(int) action.obj << ',' <<(int) action.err <<'}' //  Debug line. Remove later.
        ;std::cout<<"HP: "<<player_hp<<"/64 >"<<std::flush
        ;std::cin.getline(input_buffer,255)
        ;action=parse(input_buffer)
    ;}
;}