import sys
from time import sleep
from random import random as ran
import descript_consts

#Item enum
WOOD_SWORD,APPLE,APPLES,HEALTH_POTION,TWO_HEALTH_POTIONS,CHAIR,STAIRCASE,KNIFE,RESTAURANT,BONE,RUSTED_SWORD,NORMAL_SWORD,STEEL_SWORD,COIN,BRUSH,LEVER=1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768
item_enum={1:"wood sword",2:"apple",4:"Apples",8:"health potion",16:"Health Potionx2",32:"chair",64:"staircase",128:"knife",256:"restaurant",512:"bone",1024:"rusted sword",2048:"normal sword",4096:"steel sword",8192:"coin",16384:"brush",32768:"lever"}
jp_item_enum={1:"林の刀",2:"りんご",4:"Apples",8:"治癒薬",16:"Health Potionx2",32:"椅子",64:"階段",128:"包丁",256:"食堂",512:"骨",1024:"錆びた剣",2048:"普通の剣",4096:"鋼の剣",8192:"硬貨",16384:"刷子",32768:"レバー"}
jp_item_enum_2={1:"林の剣",2:"林檎",4:"Apples",8:"体力ポーシ",16:"Health Potionx2",32:"チェア",64:"段々",128:"ナイフ",256:"レストラン",512:"ボーン",1024:"錆びた刀",2048:"普通の刀",4096:"鋼の刀",8192:"コイン",16384:"ブラシ",32768:"てこ"}
#npc enum
MAID,GUARD,VISCOUNT,ORC,CHEF,HUMAN,TREE,FAMILY_MEMBER=1,2,4,8,16,32,64,128
npc_enum={1:"maid",2:"guard",4:"viscount",8:"orc",16:"chef",32:"human",64:"tree",128:"family member"}
jp_npc_enum={1:"メイド",2:"守衛",4:"子爵",8:"鬼",16:"コック",32:"人間",64:"木",128:"家の人"}
#npc/item enum
NORTH,EAST,SOUTH,WEST,UP,DOWN,LEFT,RIGHT=8,9,10,11,12,13,14,15
full_enum=tuple(npc_enum.values())+("north","east","south","west","up","down","left","right")+tuple(item_enum.values())+\
tuple(jp_npc_enum.values())+("北","東","南","西","上","下","左","右")+tuple(jp_item_enum.values())+tuple(jp_item_enum_2.values())
hp_enum=(48,6,12,4,40,52,-48,2)+(0,)*8+(\
-64,3,0,12,0,1,0,-64,0,-2,-96,-128,0,0,-1,0)

#Type enum
ROOM,CLEARING,CORRIDOR,PRISON,BEDROOM,COURTROOM,FOREST,VILLAGE,BASEMENT,TREASURY,DINETTE,ART_ROOM,CAVE,HALL=0,1,2,3,4,5,6,7,8,9,10,11,12,13
type_enum=("room","clearing","corridor","prison","bedroom","courtroom","forest","village","basement","treasury","dinette","art room","cave","hall")
jp_type_enum=("部屋","開墾",   "廊下",    "刑務所", "寝室",    "公判廷",    "森",    "村",      "地下室",   "金庫",    "食堂",    "美術室",   "空洞", "会館")
#Action enum
GO,GET,DROP,FIGHT,MEET,EAT,SWING,QUIT,RESET,HELP=0,1,2,3,4,5,6,7,8,9
command_enum=("GO","GET", "DROP", "FIGHT", "MEET", "EAT", "SWING", "QUIT", "RESET", "HELP",\
           "VISIT","LIFT","THROW","HIT",  "CHECK", "SWALL","USE",  "EXIT", "RESTA", "HINT",\
              "行","取",   "落",   "戦",     "合",   "食",   "振",    "辞",   "リ",    "助",\
              "訪","拾",   "投",   "当",     "見",   "飲",   "使",    "出",   "再",    "仄",\
"SAVE","セ")

class parse_result():
  obj=-1
  com=-1
  err=2

class Location():
  north=0
  east=0
  west=0
  south=0
  up=0
  down=0
  type_=0
  npcs=0
  items=0
  description=""
  jp_description=""
  
  def __init__(s,north=0,east=0,west=0,south=0,up=0,down=0,items=0,type_=0,npcs=0,description="",jp_description=""):
    s.north=int(north)
    s.east=int(east)
    s.west=int(west)
    s.south=int(south)
    s.up=int(up)
    s.down=int(down)
    s.items=int(items)
    s.type_=int(type_)
    s.npcs=int(npcs)
    s.description=str(description)
    s.jp_description=str(jp_description)

class Npc():
  inventory=0
  hp=4
  maxhp=4
  avo=0.05
  threshold=4
  def __init__(s,inv=0,hp=4,avo=0.05,threshold=4):
    s.inventory=int(inv)
    s.hp=int(hp)
    s.maxhp=s.hp
    s.avo=float(avo)
    s.threshold=int(threshold)
  
  def get_name(self)->str:
    return full_enum[npcs.index(self)]

class out_stream():
  def __init__(s,target):
    if not callable(getattr(target,"write",None)):raise TypeError("Target is not writable.")
    s.target=target
  def write(s,out):
    s.target.write(out)
  def __lshift__(self,other):
    if isinstance(other,bytes):self.target.write(other)
    else:self.target.write(str(other))
    return self

cout=out_stream(sys.stdout)

loc=4
inventory=HEALTH_POTION
player_hp=12
eaten_items=0
eaten_npcs=0
fighting=None

item_uint2 = lambda n,loc: (((n)>>(loc))%4)
npc_uint2 = lambda n,loc: (1 if bool(((n)%256)&(1<<loc))else 0)+(2 if bool(((n)>>8)&(1<<loc))else 0)

npcs=[
  Npc(inv=BRUSH), # Maid
  Npc(inv=NORMAL_SWORD|COIN,hp=28,avo=0.125,threshold=1), # Guard
  Npc(inv=STEEL_SWORD|KNIFE|COIN|TWO_HEALTH_POTIONS,hp=128,avo=0.25,threshold=0), # Viscount
  Npc(inv=NORMAL_SWORD|HEALTH_POTION,hp=64,avo=0.0625), # Orc
  Npc(inv=NORMAL_SWORD|APPLE|APPLES|HEALTH_POTION,hp=72,avo=0.1875,threshold=0), # Chef
  Npc(avo=0.25), # Human
  Npc(inv=APPLES|APPLE,hp=24,avo=0.03125,threshold=2), # Tree
  Npc() # Family Member
]

locs=[
  None,
  Location(type_=ROOM,items=CHAIR,south=4,west=6,description=\
    """It's a conservatory.
There is a nice view of the landscape and forest."""), # 1
  Location(type_=CLEARING,items=APPLE,east=4,north=6,npcs=TREE,description=\
    """It's surrounded by a wooden fence."""), # 2
  Location(type_=CORRIDOR,west=4,east=5,npcs=MAID,description=\
    """It's a dark, moist, stone corridor."""), # 3
  Location(items=WOOD_SWORD,north=1,west=2,east=3,south=0,up=0,down=0,type_=ROOM,npcs=0,description=\
    """It's a small wooden room."""), # 4
  Location(type_=ROOM,items=STAIRCASE+KNIFE+COIN,west=3,npcs=GUARD,description=\
    """It's a stone, prison-like room.
There is an inaccessable broken door high up on the wall.
There is a metal pole that is connected to a room above through a hole in the wall.
You don't think you could climb the pole, but you might be able to slide down it to get back to this room from above."""), # 5
  Location(type_=CLEARING,items=APPLE,east=1,south=2,description=\
    """You stand on a patch of grass on a tiny hill in an open area.
The breeze feels nice."""), # 6
  Location(type_=BASEMENT,up=4,east=8,description=\
    """Sunlight creeps through between the floorboards above.
The stone floor seems to creak, and the sound of dripping water echoes from the east."""), # 7
  Location(type_=ROOM,south=9,west=7,npcs=ORC,description=\
    """The room feels oppressive."""), # 8
  Location(type_=CAVE,items=RUSTED_SWORD,north=8,west=10,description=\
    """Stone surrounds you."""), # 9
  Location(type_=FOREST,north=2,east=9,items=APPLES,description=\
    """You stand at the entrance to a cave.
The cave is concealed in a lush forest.
If you were to leave, you don't think you could find your way back here easily through the forest."""), # 10
  Location(type_=TREASURY,west=8,items=HEALTH_POTION+NORMAL_SWORD+CHAIR,description=\
    """Much of the room is foul.
There is a seemingly blocked toilet in the corner.
The rest of the place is lavish with plenty of tools that you can't identify."""), # 11
  Location(type_=PRISON,south=8,east=13,npcs=HUMAN,description=\
    """There are chains and bars."""), # 12
  Location(type_=HALL,npcs=CHEF,items=RESTAURANT+LEVER,description=\
    """The tension is high in this grand hall.
The torches on either wall crackle; adding to the atmosphere.
The entrance to the room is gone."""), # 13
  Location(type_=ROOM,south=15,east=20,down=13,description=\
    """A dusty, dilapidated wooden room.
There is a hole in both the ceiling and the floor."""), # 14
  Location(type_=HALL,north=14,west=16,east=21,description=\
    """A small, yet clearly well used meeting hall."""), # 15
  Location(type_=TREASURY,items=STEEL_SWORD,east=15,up=17,description=\
    """A soft amber glow barely illuminates the room.
There's stuff here that you can't see, let alone identify."""), # 16
  Location(type_=ART_ROOM,north=18,south=19,down=16,description=\
    """Stacks of both old and recently painted paintings sit in a well lit room."""), # 17
  Location(type_=COURTROOM,npcs=VISCOUNT,south=17,east=14,description=\
    """Soft sunlight shines into this grand courtroom."""), # 18
  Location(type_=ROOM,north=17,down=24,description=\
    """The room seems intended for fast access to the bedroom below."""), # 19
  Location(type_=BEDROOM,west=14,south=21,description=\
    """Light shines through a window onto a four poster bed."""), # 20
  Location(type_=DINETTE,north=20,south=22,description=\
    """A grand dining room.
There is an entrance from the west; covered by some kind of banner, which is too high to reach."""), # 21
  Location(type_=ROOM,items=HEALTH_POTION,north=21,west=23,description=\
    """It's a small storage room."""), # 22
  Location(type_=CORRIDOR,east=22,west=24,description=\
    """Light shines into this long corridor from the south."""), # 23
  Location(type_=BEDROOM,east=23,west=25,description=\
    """It's a lavish bedroom with an en suite to the south."""), # 24
  Location(type_=HALL,east=24,north=26,description=\
    """An inviting hall, clearly intended to welcome guests into this place which you now suspect to be some kind of manor."""), # 25
  Location(type_=ART_ROOM,items=LEVER,south=25,description=\
    """The room seems well used as an exit, but dusty paintings hang on dusty walls."""), # 26
]

def check_can_hold_multiple(arr:int):
  return bool(arr&(APPLE|APPLES|HEALTH_POTION|TWO_HEALTH_POTIONS))

def parse_com_check(arr,enum=None) -> int:
  "return signed char; positive if a valid command was detected, otherwise -1."
  for i in range(len(arr)):
    if arr[i]=="" and ((not hasattr(enum, '__getitem__'))or enum[i]!=""): # This will become a check to see if a null character has been reached.
      return i
  return -1

def parse(inp_str) -> parse_result:
  "Parse user input."
  out=parse_result()
  
  commands=list(command_enum) # Coppying the array may require multiple commands
  
  i=0
  while i < len(inp_str):
    # <Return if null-turminator will go here>
    for j in range(len(commands)):
      if (commands[j]!="")and inp_str[i].upper()==commands[j][0]:commands[j]=commands[j][1:] # This will be pointer incrementation
    i+=1
    out.com=parse_com_check(commands)
    if out.com!=-1:break
  if i>=len(inp_str) and  out.com==-1:return out # Line might be removed in other implementations.
  out.err=1
  
  objs=list(full_enum) # Coppying the array may require multiple commands
  i=i if out.com<20 else 0
  out.com=(out.com%10)if out.com<40 else 10
  
  while i < len(inp_str):
    # <Return if null-turminator will go here>
    for j in range(len(objs)):
      if (objs[j]!="")and inp_str[i].lower()==objs[j][0]:objs[j]=objs[j][1:] # This will be pointer incrementation
    i+=1
    out.obj=parse_com_check(objs,full_enum)
    if out.obj!=-1:break
  if i>=len(inp_str) and out.obj==-1:return out # Line might be removed in other implementations.
  out.err=0

  out.obj=(out.obj-16 if out.obj>=64 else out.obj)%32
  return out

def describe(location:Location):
  (cout 
  << "You are in a " << type_enum[locs[loc].type_] << ".\n"
  << locs[loc].description << '\n')
  if location.items & ~LEVER!=0:
    cout << "\nOn the floor, there is:\n"
    for i in range(15):
      if location.items & 1<<i:(cout
      << "-"
      << full_enum[16+i]
      << '\n')
    cout << '\n'
  for i in range(8):
    if 1<<i & location.npcs:
      assert(npc_uint2(eaten_npcs,i)<3,"The NPC should have been removed after being eaten a third time.")
      print(descript_consts.npc_info[i][npc_uint2(eaten_npcs,i)+3*int(npcs[i].hp<=0)])
  if location.north>0:
    print("NORTH:",type_enum[location.type_],"->",type_enum[locs[location.north].type_])
  if location.east>0:
    print("EAST:",type_enum[location.type_],"->",type_enum[locs[location.east].type_])
  if location.south>0:
    print("SOUTH:",type_enum[location.type_],"->",type_enum[locs[location.south].type_])
  if location.west>0:
    print("WEST:",type_enum[location.type_],"->",type_enum[locs[location.west].type_])
  if location.up>0:
    print("UP:",type_enum[location.type_],"->",type_enum[locs[location.up].type_])
  if location.down>0:
    print("DOWN:",type_enum[location.type_],"->",type_enum[locs[location.down].type_])

def do_action(action:parse_result):
  global loc
  global inventory
  global eaten_npcs
  global player_hp
  global fighting
  location=locs[loc]
  print(action.com,action.obj,action.err) # Debug line. Remove later.
  if action.err==2:
    cout << "Invalid command. Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, QUIT, RESET, and HELP.\n\n"
    return
  if action.err==1:
    if action.com>=QUIT:return
    cout << "Invalid object to " << command_enum[action.com] << "!\n"
    return
  
  obj_name=full_enum[action.obj]
  match action.com:
    case 0:#GO
      if not isinstance(fighting,type(None)):
        cout << "You can't leave while you are in a fight!\n"
        return
      match action.obj:
        case 8:#NORTH
          if location.north==0:
            cout << "No way to go north.\n"
            return
          loc=location.north
          cout << "You went north.\n"
        case 9:#EAST
          if location.east==0:
            cout << "No way to go east.\n"
            return
          loc=location.east
          cout << "You went east.\n"
        case 10:#SOUTH
          if location.south==0:
            cout << "No way to go south.\n"
            return
          loc=location.south
          cout << "You went south.\n"
        case 11:#WEST
          if location.west==0:
            cout << "No way to go west.\n"
            return
          loc=location.west
          cout << "You went west.\n"
        case 12:#UP
          if location.up==0:
            cout << "No way to go up.\n"
            return
          loc=location.up
          cout << "You went up.\n"
        case 13:#Down
          if location.down==0:
            cout << "No way to go down.\n"
            return
          loc=location.down
          cout << "You went down.\n"
        case _:
          cout << obj_name<< " is an invalid direction.\n"
          return
      describe(locs[loc])
      return
    case 1:#GET
      if action.obj<16:
        cout << obj_name << " is not an item.\n"
        return
      item_bit=1<<(action.obj-16)
      multi_item=check_can_hold_multiple(item_bit)
      if (item_bit | (item_bit<<1 if multi_item else 0)) & location.items==0:
        cout << "There is no "<<obj_name<<" on the ground.\n"
        return
      if multi_item:
        if item_uint2(inventory,action.obj-16)==3:
          cout << "Too many "<<obj_name<<"s are already in your inventory.\n"
          return
      else:
        if bool(item_bit & inventory):
          cout << obj_name <<" is already in your inventory.\n"
          return
      location.items=location.items ^ item_bit
      if location.items&item_bit!=0:
        location.items=location.items ^ (item_bit<<1)
        assert(multi_item)
        assert(item_uint2(location.items,action.obj-16)==1)
      inventory=inventory ^ item_bit
      if inventory&item_bit==0:
        inventory=inventory ^ (item_bit<<1)
        assert(multi_item)
        assert(item_uint2(inventory,action.obj-16)==2)
      cout << "You picked up the " << obj_name << ".\n"
      if not isinstance(fighting,type(None)):counter(fighting,fighting.get_name())
    case 2:#Drop
      if action.obj<16:
        cout << obj_name << " is not an item.\n"
        return
      item_bit=1<<(action.obj-16)
      multi_item=check_can_hold_multiple(item_bit)
      if multi_item:
        if item_uint2(location.items,action.obj-16)==3:
          cout << "The floor seems full...\n"
          return
      else:
        if bool(item_bit & location.items):
          cout << obj_name << " is already on the floor.\n"
          return
      if (item_bit | (item_bit<<1 if multi_item else 0)) & inventory==0:
        cout << "You don't have any "<< obj_name << ".\n"
        return
      if bool(item_bit & STAIRCASE)and loc==4:
        inventory=inventory ^ item_bit
        locs[4].down=7
        cout << "The staircase fell through the floor.\n"
        return
      location.items=location.items ^ item_bit
      if location.items&item_bit==0:
        location.items=location.items ^ (item_bit<<1)
        assert(multi_item)
        assert(item_uint2(location.items,action.obj-16)==2)
      inventory=inventory ^ item_bit
      if inventory&item_bit!=0:
        inventory=inventory ^ (item_bit<<1)
        assert(multi_item)
        assert(item_uint2(inventory,action.obj-16)==1)
      cout << "The "<<obj_name<<" landed on the floor.\n"
      if not isinstance(fighting,type(None)):counter(fighting,fighting.get_name())
    case 3:#FIGHT
      if action.obj>=8:
        cout << "Can't fight "<<obj_name<<".\n"
        return
      item_bit=1<<action.obj
      if location.npcs & item_bit==0:
        cout << "The "<<obj_name<<" is not in this room.\n"
        return
      if npcs[action.obj].hp<=0:
        cout << "You have already defeated the " << obj_name << ".\n"
        return
      if (action.obj==5 and npc_uint2(eaten_npcs,action.obj)>0) or npcs[action.obj].hp<=1:
        npcs[action.obj].hp=0
        cout << "You... WIN!\n"
        cout << "... yeah, it can't fight back...\n"
        cout << "You won.\n"
      fighting=npcs[action.obj]
      cout << "You are now fighting the " << obj_name << ".\n"
    case 4:#MEET
      # First check if it is somthing that is actually present.
      if action.obj<8:
        item_bit=1<<action.obj
        if location.npcs & item_bit==0:
          cout << "The "<<obj_name<<" is not in this room.\n"
          return
        if not isinstance(fighting,type(None)):
          if npcs[action.obj]!=fighting:
            cout << "Your focus is on " << fighting.get_name() << ".\n"
            return
          cout << "They have "<<fighting.hp<<" hp.\n"
        else:cout << descript_consts.npc_speech[action.obj][npc_uint2(eaten_npcs,action.obj)+3*int(npcs[action.obj].hp<=0)]
      elif action.obj<16:
        item_bit=0 # This variable will be used differently on this path.
        match action.obj:
          case 8:item_bit=int(not bool(location.north))
          case 9:item_bit=int(not bool(location.east))
          case 10:item_bit=int(not bool(location.south))
          case 11:item_bit=int(not bool(location.west))
          case 12:item_bit=int(not bool(location.up))
          case 13:item_bit=int(not (bool(location.down)or loc==4))
          case 14:item_bit=int(True)
          case 15:item_bit=int(True)
        if bool(item_bit):
          cout << "There is nothing "<<obj_name<<".\n"
          return
      else:
        item_bit=1<<(action.obj-16)
        if (location.items|inventory) & item_bit==0:
          cout << "There is no " << obj_name << ".\n"
          return
        cout << descript_consts.item_info[action.obj-16] # Then display info about it.
        return
      if not isinstance(fighting,type(None)):counter(fighting,fighting.get_name())
    case 5:#EAT
      # First check if it is somthing that is actually present.
      if action.obj<8:
        item_bit=1<<action.obj
        if bool(item_bit & ((eaten_npcs>>8)&(eaten_npcs%256))):
          cout << "You have already eaten the " << obj_name << ".\n"
          return
        if location.npcs & item_bit==0:
          cout << "The "<<obj_name<<" is not in this room.\n"
          return
        if npc_uint2(eaten_npcs,action.obj)!=npcs[action.obj].threshold or npcs[action.obj].hp<=1:
          player_hp+=hp_enum[action.obj]>>npc_uint2(eaten_npcs,action.obj)
          eaten_npcs=eaten_npcs^(item_bit|((item_bit & eaten_npcs)<<8))
          npcs[action.obj].hp=npcs[action.obj].hp>>1
          cout << "You ate the " << obj_name << ".\n"
        elif fighting!=npcs[action.obj]:
          cout << "The "<<obj_name<<" defended themselves!\n"
          fighting=npcs[action.obj]
          npc_name=fighting.get_name()
        
        if npc_uint2(eaten_npcs,action.obj)>=3:
          location.npcs=location.npcs^item_bit
          location.items=location.items | npcs[action.obj].inventory | (BONE if item_bit!=TREE else 0)
          if fighting==npcs[action.obj]:
            cout << "You win!!!\n"
            fighting=None
        if fighting==npcs[action.obj]:
          roll=ran()
          if roll*2>=fighting.avo:
            roll2=2+ran()*3
            atk=int(roll2)
            fighting.hp=fighting.hp-atk if fighting.hp-atk>=0 else 0
            if fighting.hp>1:cout << "You bit for "<<atk<<" damage!\n"
            player_hp+=int(roll2/2+ran())
          elif roll>=0.05 and fighting.hp>1:cout << "The "<<npc_name<<" dodged.\n"
          elif fighting.hp>1:cout << "The bite missed.\n"
          if fighting.hp<=1:
            fighting.hp=0
            cout << "You win!!!\n"
            fighting=None

      elif action.obj<16:
        cout << "Ya can't eat a direction...\n"
        return
      else:
        item_bit=1<<(action.obj-16)
        if (location.items|inventory) & (item_bit | (item_bit<<1 if check_can_hold_multiple(item_bit)else 0))==0:
          cout << "There is no "<< obj_name << ".\n"
          return
        on_floor=bool(location.items & item_bit)or(check_can_hold_multiple(item_bit)and item_uint2(location.items,action.obj-16))
        cout << "You ate the " << obj_name << ".\n"
        if hp_enum[action.obj]==0:
          player_hp=0
        elif player_hp+hp_enum[action.obj]<=max(64,player_hp):player_hp+=hp_enum[action.obj]
        elif player_hp<64:player_hp=64
        if (not check_can_hold_multiple(item_bit))or(item_uint2(location.items if on_floor else inventory,action.obj-16)%2):
          if on_floor:location.items=location.items^item_bit
          else:inventory=inventory^item_bit
        else:
          if on_floor:
            location.items=location.items^(item_bit | item_bit<<1)
            assert(not bool(location.items & (item_bit<<1)))
          else:
            inventory=inventory^(item_bit | item_bit<<1)
            assert(not bool(inventory & (item_bit<<1)),("1"if bool(inventory & (item_bit<<1))else"0")+("1"if bool(inventory & (item_bit))else"0"))
      if not isinstance(fighting,type(None)):counter(fighting,fighting.get_name())
    case 6:#SWING
      if action.obj<16:
        cout << obj_name <<" is not an item.\n"
        return
      item_bit=1<<(action.obj-16)
      if item_bit & inventory==0:
        cout << "You don't have any "<< obj_name << ".\n"
        return
      cout << "You swung the " << obj_name << ".\n"
      if isinstance(fighting,type(None)):
        if bool(item_bit & STAIRCASE)and loc==4:
          inventory=inventory ^ item_bit
          locs[4].down=7
          cout << "You lost your grip.\n"
          cout << "The staircase fell through the floor.\n"
          return
        cout << "... but nothing happened.\n"
        return
      npc_name=fighting.get_name() # This will be declared sooner in the C++ code.
      roll=ran()
      if roll>=fighting.avo:
        cout << "The attack connected!\n"
        atk=int(descript_consts.item_dmg[action.obj-16]+ran()+(descript_consts.item_dmg[action.obj-16]*ran()/2))
        fighting.hp=fighting.hp-atk if fighting.hp-atk>=0 else 0
        cout << "You delt "<<atk<<" damage!\n"
        if fighting.hp<=0:
          cout << "You win!!!\n"
          fighting=None
          return
      elif roll>=0.05:cout << "The "<<npc_name<<" dodged.\n"
      else:cout << "The attack missed.\n"
      counter(fighting,npc_name)
  if player_hp<=0:
    cout << "GAME OVER!!!\n"
    action.com=QUIT

def counter(npc,npc_name):
  global player_hp
  cout << "The "<<npc_name<<" attacks!\n"

  if ran()<0.125:dmg=0
  else:
    wpn=float()
    for i in range(15):
      if bool(1<<i & npc.inventory):wpn=max(descript_consts.item_dmg[i],wpn)
    dmg=max(int(wpn+ran()*5-2.5),0)
    player_hp-=dmg

  if dmg==0:cout << "The attack missed.\n"
  else:cout << "You were hit for " << dmg <<" damage!\n"


if __name__=="__main__":
  print("You are on an adventure to find a source of nourishment, and have entered a strange building you have found in the forest.")
  print("Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, QUIT, RESET, and HELP.\n")

  describe(locs[loc])
  command=input("What will you do? >")
  action=parse(command)
  while action.com!=QUIT:
    do_action(action)
    command=input("HP: "+str(player_hp)+"/64 >")
    action=parse(command)
