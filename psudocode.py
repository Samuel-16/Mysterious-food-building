from time import sleep
from random import random as ran

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
#Type enum
ROOM,CLEARING,CORRIDOR,PRISON,BEDROOM,COURTROOM,FOREST,VILLAGE=0,1,2,3,4,5,6,7
type_enum=("room","clearing","corridor","prison","bedroom","courtroom","forest","village")
jp_type_enum=("部屋","開墾","廊下","刑務所","寝室","公判廷","森","村")
#Action enum
GO,GET,DROP,FIGHT,MEET,EAT,SWING,QUIT,RESET,HELP=0,1,2,3,4,5,6,7,8,9
command_enum=("GO","GET", "DROP", "FIGHT", "MEET", "EAT", "SWING", "QUIT", "RESET", "HELP",\
           "VISIT","LIFT","THROW","HIT",  "CHECK", "SWALL","USE",  "EXIT", "RESTA", "HINT",\
              "行","取",   "落",   "戦",     "合",   "食",   "振",    "辞",   "リ",    "助",\
              "訪","拾",   "投",   "当",     "見",   "飲",   "使",    "出",   "再",    "仄",\
"SAVE","セーブ")

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
  avo=0.05
  def __init__(s,inv=0,hp=4,avo=0.05):
    s.inventory=int(inv)
    s.hp=int(hp)
    s.avo=float(avo)

loc=4
inventory=3
eaten_items=0
eaten_npcs=0

locs=[
  None,
  Location(type_=ROOM,south=4,west=6,description=\
    """It's a conservatory.
There is a nice view of the lanscape and forest."""),
  Location(type_=CLEARING,east=4,north=6,description=\
    """It's surrounded by a wooden fence."""),
  Location(type_=CORRIDOR,west=4,east=5,npcs=MAID,description=\
    """It's a dark, moist, stone corridor."""),
  Location(items=WOOD_SWORD+ROOM,north=1,west=2,east=3,south=0,up=0,down=0,type_=ROOM,npcs=0,description=\
    """It's a small wodden room."""),
  Location(type_=ROOM,west=3,npcs=GUARD,description=\
    """It's a stone, prison-like room."""),
  Location(type_=CLEARING,east=1,south=2,description=\
    """You stand on a patch of grass on a tiny hill in an open area.
The breeze feels nice."""),
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
  if i>=len(inp_str):return out # Line might be removed in other implementations.
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

def do_action(action:parse_result):
  global loc
  global inventory
  global eaten_npcs
  location=locs[loc]
  print(action.com,action.obj,action.err) # Debug line. Remove later.
  if action.err==2:
    print("Invalid command. Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, QUIT, RESET, and HELP.\n")
    return
  if action.err==1:
    if action.com>=QUIT:return
    print("Invalid object to %s" % command_enum[action.com])
    return
  
  obj_name=full_enum[action.obj]
  match action.com:
    case 0:#GO
      match action.obj:
        case 8:#NORTH
          if location.north==0:
            print("No way to go north.")
            return
          loc=location.north
          print("You went north.")
        case 9:#EAST
          if location.east==0:
            print("No way to go east.")
            return
          loc=location.east
          print("You went east.")
        case 10:#SOUTH
          if location.south==0:
            print("No way to go south.")
            return
          loc=location.south
          print("You went south.")
        case 11:#WEST
          if location.west==0:
            print("No way to go west.")
            return
          loc=location.west
          print("You went west.")
        case _:
          print("%s is an invalid direction." % obj_name)
          return
      print("You are in a %s." % type_enum[locs[loc].type_])
      print(locs[loc].description)
      return
    case 1:#GET
      if action.obj<16:
        print("%s is not an item." % obj_name)
        return
      item_bit=1<<(action.obj-16)
      if item_bit & location.items==0:
        print("There is no %s on the ground." % obj_name)
        return
      if bool(item_bit & inventory):
        print("%s is already in your inventory." % obj_name)
        return
      location.items=location.items ^ item_bit
      inventory=inventory ^ item_bit
      print("You picked up the %s" % obj_name)
    case 2:#Drop
      if action.obj<16:
        print("%s is not an item." % obj_name)
        return
      item_bit=1<<(action.obj-16)
      if bool(item_bit & location.items):
        print("%s is already on the floor." % obj_name)
        return
      if item_bit & inventory==0:
        print("You don't have any %s." % obj_name)
        return
      location.items=location.items ^ item_bit
      inventory=inventory ^ item_bit
      print("The %s landed on the floor." % obj_name)
    case 3:#FIGHT
      if action.obj>=8:
        print("Can't fight %s." % obj_name)
        return
      #TODO Implement fighting.
    case 4:#MEET
      # First check if it is somthing that is actually present.
      if action.obj<8:
        item_bit=1<<action.obj
        if location.npcs & item_bit==0:
          print("The %s is not in this room." % obj_name)
          return
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
          print("There is nothing %s." % obj_name)
          return
      else:
        item_bit=1<<(action.obj-16)
        if (location.items|inventory) & item_bit==0:
          print("There is no %s." % obj_name)
          return
      # Then display info about it.
      #TODO implement
    case 5:#EAT
      # First check if it is somthing that is actually present.
      if action.obj<8:
        item_bit=1<<action.obj
        if bool(item_bit & ((eaten_npcs>>8)&(eaten_npcs%256))):
          print("You have already eaten the %s." % obj_name)
          return
        if location.npcs & item_bit==0:
          print("The %s is not in this room." % obj_name)
          return
      elif action.obj<16:
        print("Ya can't eat a direction...")
        return
      else:
        item_bit=1<<(action.obj-16)
        if (location.items|inventory) & item_bit==0:
          print("There is no %s." % obj_name)
          return
      # Then resolve what happens when the object is eaten.
      #TODO implement
    case 6:#SWING
      if action.obj<16:
        print("%s is not an item." % obj_name)
        return
      item_bit=1<<(action.obj-16)
      if item_bit & inventory==0:
        print("You don't have any %s." % obj_name)
        return
      #TODO implement


if __name__=="__main__":
  print("You are on an adventure to find a source of nourishment, and have entered a strange building you have found in the forest.")
  print("Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, QUIT, RESET, and HELP.\n")

  type_str=type_enum[locs[loc].type_] # Maybe this would be `char *type_str=type_enum[locs[loc].type];`?
  print("You are in a %s" % type_str)
  print(locs[loc].description)
  command=input("What will you do? >")
  action=parse(command)
  while action.com!=QUIT:
    do_action(action)
    command=input(">")
    action=parse(command)
