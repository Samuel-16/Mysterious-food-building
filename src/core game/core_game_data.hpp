byte flags=0;
byte loc=4;
word inventory=HEALTH_POTION;
signed int player_hp=12;
word eaten_items=0;
word eaten_npcs=0;
const byte cakemax[2]={74,47};
byte cakelife[2]={74,47};
byte maidSleep=1;
Npc* fighting=nullptr;

Npc npcs[8]={
{.inventory=BRUSH}, // Maid
{.inventory=NORMAL_SWORD|COIN,.hp=18,.maxhp=18,.avo=0.125,.threshold=1}, // Guard
{.inventory=STEEL_SWORD|KNIFE|COIN|TWO_HEALTH_POTIONS,.hp=128,.maxhp=128,.avo=0.25,.threshold=0}, // Viscount
{.inventory=NORMAL_SWORD|HEALTH_POTION,.hp=30,.maxhp=30,.avo=0.0625}, // Orc
{.inventory=NORMAL_SWORD|APPLE|APPLES|HEALTH_POTION,.hp=52,.maxhp=52,.avo=0.1875,.threshold=0}, // Chef
{.inventory=0,.avo=0.25}, // Human
{.inventory=APPLES|APPLE,.hp=24,.maxhp=24,.avo=0.03125,.threshold=1}, // Tree
Npc() // Family Member
};

Location locs[32]={{0},
  {.type=ROOM,.south=4,.west=6,.items=CHAIR,.description=
    R"(It's a conservatory.
There is a nice view of the lanscape and forest.)"},
  {.type=CLEARING,.north=6,.east=4,.npcs=TREE,.items=APPLE,.description=
    R"(It's surrounded by a wooden fence.)"},
  {.type=CORRIDOR,.east=5,.west=4,.npcs=MAID,.description=
    R"(It's a dark, moist, stone corridor.)"},
  {.type=ROOM,.north=1,.east=3,.west=2,.items=WOOD_SWORD,.description=
    R"(It's a small wooden room.)"},
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
    R"(You stand at the entrance to your village.)"}};