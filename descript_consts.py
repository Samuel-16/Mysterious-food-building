NORTH,EAST,SOUTH,WEST,UP,DOWN,LEFT,RIGHT=8,9,10,11,12,13,14,15
ROOM,CLEARING,CORRIDOR,PRISON,BEDROOM,COURTROOM,FOREST,VILLAGE,BASEMENT,TREASURY,DINETTE,ART_ROOM,CAVE,HALL=0,1,2,3,4,5,6,7,8,9,10,11,12,13

room_tra={(ROOM,ROOM,NORTH):"There is a wooden door to the **north**.",
(ROOM,ROOM,SOUTH):"There is a wooden door to the **south**.",
(CLEARING,CLEARING,NORTH):"There is a wooden gate to the **north**.",
(CLEARING,CLEARING,SOUTH):"There is a wooden gate to the **south**.",
(CLEARING,ROOM,EAST):"There is an open window to the **east**, which you could climb in through.",
(ROOM,CLEARING,WEST):"There is an open window to the **west**, which you could climb out through.",
(ROOM,CORRIDOR,EAST):"There is a stone door to the **east**.",
(CORRIDOR,ROOM,WEST):"There is a stone door to the **west**.",
(CORRIDOR,ROOM,EAST):"There is a wooden double door to the **east** which seems reinforced with metal.",
(ROOM,CORRIDOR,WEST):"There is a wooden double door to the **west** which seems reinforced with metal.",
(ROOM,BASEMENT,DOWN):"The staircase leads **down** into a basement.",
(BASEMENT,ROOM,UP):"You could take the starcase back **up**stairs.",
(BASEMENT,ROOM,EAST):"A rotton and soggy door leads to the **east**.",
(ROOM,BASEMENT,WEST):"A rotton and soggy door leads to the **west**.",
(ROOM,CAVE,SOUTH):"There is a dark tunnel leading **south**.",
(CAVE,ROOM,NORTH):"There is a dim glow from the **north**.",
(CAVE,CAVE,EAST):"There is a dark tunnel leading **east**.",
(CAVE,CAVE,WEST):"There is still a tunnel letting you return **west**.",
(CAVE,FOREST,WEST):"There is a dim glow from the **west**.",
(FOREST,CAVE,EAST):"You could still return to the cave by going **east**.",
(FOREST,CLEARING,NORTH):"You can see the building where you entered in the distant **north**.",
(ROOM,TREASURY,EAST):"There is a gilded door to the **east**.",
(TREASURY,ROOM,WEST):"The gilded door to the **west** is still there.",
(ROOM,PRISON,NORTH):"The cell to the **north** is open.",
(PRISON,ROOM,SOUTH):"The cell's exit is **south**.",
(PRISON,HALL,EAST):"There is a *hidden* tunnel to the **east**.",
(HALL,ROOM,UP):"There is a spiral staircase leading **up**.",
(ROOM,HALL,DOWN):"There is a spiral staircase leading **down**.",
(ROOM,HALL,SOUTH):"There is a grand double door leading **south**.",
(ROOM,BEDROOM,EAST):"There is a wooden door to the **east**.",
(BEDROOM,ROOM,WEST):"There is a wooden door to the **west**.",
(HALL,ROOM,NORTH):"There is a grand double door leading **north**.",
(HALL,DINETTE,EAST):"To the **east**, there is some kind of curtained doorway.",
(HALL,TREASURY,WEST):"There is a gilded door to the **west**.",
(TREASURY,HALL,EAST):"There is a gilded door to the **east**.",
(TREASURY,ART_ROOM,UP):"A ladder leads **up** through a trapdoor.",
(ART_ROOM,TREASURY,DOWN):"There is a trapdoor you could use to go back **down**.",
(ART_ROOM,ROOM,SOUTH):"There is a wooden door to the **south**.",
(ROOM,ART_ROOM,NORTH):"There is a wooden door to the **north**.",
(ROOM,BEDROOM,DOWN):"You could jump **down**.",
(ART_ROOM,COURTROOM,NORTH):"There is a grand wooden door to the **north**.",
(COURTROOM,ART_ROOM,SOUTH):"There is an exit to the **south**.",
(COURTROOM,ROOM,EAST):"There is a hole in **east** annex of the room that you could jump into.",
(DINETTE,ROOM,SOUTH):"There is a wooden door to the **south**.",
(ROOM,DINETTE,NORTH):"There is a wooden door to the **north**.",
(DINETTE,BEDROOM,NORTH):"There is a wooden door to the **north**.",
(BEDROOM,DINETTE,SOUTH):"There is a wooden door to the **south**.",
(CORRIDOR,BEDROOM,WEST):"The only other door you could fit through is **west**.",
(BEDROOM,CORRIDOR,EAST):"There is a wooden door to the **east**.",
(BEDROOM,HALL,WEST):"There is a wooden door to the **west**.",
(HALL,BEDROOM,EAST):"There is a wooden door to the **east**.",
(HALL,ART_ROOM,NORTH):"There is a wooden door to the **north**.",
(ART_ROOM,HALL,SOUTH):"There is a wooden door to the **south**.",
(ART_ROOM,ROOM,DOWN):"There is a pole that you could slide **down**.",
}

item_info=("It looks like a toy sword, but you probably have the strength to use it to kill.",
"Though many bad apples rest on the floor, this one looks edible.\nIt must have recently fallen.",
"Yay! Many apples!",
"A common magic potion for healing.",
"Multiple health potions!",
"A cushioned wooden chair.",
"A loose staircase that looks like it previously led up to the broken door.\nMaybe you could *DROP* it somewhere else?",
"A kitchen knife.\nYou could easily use this as a simple weapon.",
"This is it!\nYou're not quite sure how to open it, but maybe someone back at your village might know.\nIf you could JUST take this resturant back... surely you would be able to feed not just your family, but your whole village!",
"The remains of a body.\nYou don't think it would be a good idea to eat this.",
"A rusty sword.",
"A sword.\nIt looks sharp.",
"This sword looks stronger and sharper than anything you've ever seen.",
"This thing seems like it represents a value far greater than what your village is used to seeing.",
"A maid's brush.",
"You think you can pull this lever.")

item_food=(
(("You ate the wood sword?",2),("Why?",4),("You now have a wooden sword protruding out the back of your neck...",4),("What did you think was going to happen?",3)),
(("You swallowed the apple.",3),("You immediately healed 3HP.",3),("Finally having somthing to eat feels amazing!",2)),
(),
(("You ate *(%2Adrank)* the health potion.",4),("You healed 12HP.",2)),
(),
(("You swallowed the chair.",1),("Your oesophagus is unnaturally contorted to fit it.",6),("The chair is stuck in your throat!",4),("You feel the chair compress and break inside you as you struggle for air!",10),("You don't feel well…",24),("But that cushion was nice!",1),("You healed 1HP!",1)),
(),
(("You swallowed the knife.",6),("You feel yourself bleeding inside.",4)),
(),
(("You managed to eat the bone…",4),("You felt it's shards cut your flesh as it went down.",4),("You didn't think it was a good idea to eat that…",4)),
(("You forced the old, rusty sword into your throat.",20),("It tastes disgusting.",8),("You shudder at the thought of what might of touched this.",8),("You feel sick.",42)),
(("You swallow the sword.",3),("It cuts through your throat like paper.",12),("The sword is protruding out of the back of your neck.",16),("Breathing and speaking is more difficult now.",16)),
(),
(),
(("You ate the brush.",3),("Its bristles prickle your stomach.",3),("You immediately regret eating that.",6)))

item_death=(
(("You try to remove the sword, but it only makes things worse…",6),("r<Blood> gushes out of your neck, and down your body.",6),("You collapse.",6),("You try to think of your family, but it only makes you dread the fact that they will be left to starve without you.",8),("You don't think you can survive this.",8),("You don't think ... anymore...",8)),
(),
(),
(),
(),
(),
(("You eat the staircase.",8),("You struggle to eat the staircase.",8),("Even after the first step; your mouth bleeds from being cut by broken bits of staircase.",6),("Debris fills your stomach. The pain is unbearable.",2),("All you can do to distract yourself from the pain is to continue to chew the staircase.",12),("You cough.",4),("Somthing gets stuck in your throat as you try to cough.",6),("You can't breath anymore.",8),("It seems your last breath is in your past now.",14),("You try to reminisce about when you were able to breath, but you fail to do so as your consciousness fades.",16)),
(("You choke; trying desprately to expel the knife.",4),("… but only blood comes out.",8),("You feel faint.",8),("This doesn't feel real.",8),("You miss your family.",8),("You collapse.",8)),
(("You eat the resturant.",8),("Your teeth break as you try to chew on brick.",3),("Your mouth and throat are cut as glass shatters inside of you.",8),("You are filed with regret.",4),("Someone could have used that resturant to feed your village, but now, you've ruined it!",20),("… and in doing so, you've ruined yourself.",8),("You bleed out.",3)),
(("You *really* didn't think it was a good idea to eat that...",7),("You feel sick and dizzy…",7),("You **KNOW** it was never a good idea to do that!",8),("You begin to choke.",6),("It **R<definitely** wasn't a good idea to eat that.",2),("You realise that dr<blood> is dripping from your mouth.",2),("You collapse on the floor...",2),("You begin to struggle for air.",2),("You can't think straight",2),("You continue to struggle for air.",2),("You can't think straight",2),("You suddenly realise you are struggling for air.",2),("You can't think straight",2),("You can't *see* anymore.",2),("You can't think straight",2),("Your consciousness fades.",2),("You can't think straight",2)),
(("The rust feels uncomfortable against your skin.",8),("You feel like you are going to vomit.",40),("Your body is trying to vomit, but the **rusted sword** is blocking it.",8),("It seems your last breath is in your past now.",14),("You regret not being able to help your village.",16),("You regret not being able to help your family.",16),("You thrash about in a panic as you struggle for air.",12)),
(("You feel like you are going to vomit.",48),("Your body is trying to vomit, but the **normal sword** is blocking it.",8),("It seems your last breath is in your past now.",14),("You regret not being able to help your village.",16),("You regret not being able to help your family.",16),("You thrash about in a panic as you struggle for air.",12)),
(("Uhh… ok?",4),("You decapitate yourself.",3)),
(("You draw your final breath and swallow the coin.",8),("You can't breath anymore.",24),("You miss being able to breath.",24)),
(("You feel faint.",8),("You feel sick.",8),("Your body tries to vomit.",2),("Only blood comes out.",2),("You try to steady your breathing.",2),("Your throat is blocked by blood.",2),("You try to clear your throat.",2),("Only blood comes out.",2),("You try to steady your breathing.",2),("Your throat is blocked by blood.",2),("You try to clear your throat.",2),("Only blood comes out.",2),("You try to steady your breathing.",2),("Your throat is blocked by blood.",2),("You try to clear your throat.",2),("Only blood comes out.",2),("You try to steady your breathing.",2),("Your throat is blocked by blood.",2),("You try to clear your throat.",2),("Only blood comes out.",2),("You try to steady your breathing.",2),("Your throat is blocked by blood.",2),("You faint.",2)),
)

item_dmg=(
  3,
  0.25,
  0.25,
  1/2+1/16,
  1/2+1/16,
  2,
  2,
  4.5,
  4,
  1.5,
  5+5/8,
  8.75,
  16,
  0.5,
  5/4,
  0)

npc_speech=(("The maid is cleaning the corridor.\n\"m<Can I help you?>\"",
"The maid isn't cleaning the corridor anymore.\n\"m<Owch!\nDid you just eat my %2A%2A%2A%2A?\n*Why?*\"",
"The maid isn't cleaning the corridor anymore.\n\"m<Owowowowowowowowowowwwwwwwww!\nOk ok okokokokok.\nPlease... please just kill me...\nI can't live like this.>\"",
"The maid has gone back to cleaning the corridor.\n\"m<It still hurts...\nWhat was all that for?>\"",
"The maid isn't cleaning the corridor anymore.\n\"m<Owch!\nYou win ok!\nStop eating me!>\"",
"The maid is crying now.\n\"m<Owwww ow ow ow owwwwwwwww!\nOk ok. Just finish me off.>\"\nThe maid tries to smile through the tears.\n\"m<...I'm ... glad you liked me...>\"",
"The maid is cleaning the corridor.\n\"m<Is that a restaurant in your pocket?\n♡ Or are you just happy to see me? ♡>\"",
"The maid is fast asleep.",
"\"m<Oh. Was that my boss?>\""),
("It's an armed guard.\n\"Hey there, not sure who you are, but the way up is out of action.\nYou'll have to go round the other way.\"",
"It's a half-eaten traumatised guard.\n\"AAAGGAGG! Get away! GET AWAY!\"",
"The guard isn't conscious anymore.\nIt's bleeding out.",
"It's a defeated guard.\n\"Ok! Ok! I admit defeat!\"",
"It's a half-eaten traumatised guard.\n\"AAAGGAGG! OW! OW OW OW! I'm done! I'm done! Please just go.\"",
"The guard isn't conscious anymore.\nIt's bleeding out.",
"It's an armed guard.\n\"Hey there, not sure who you are, but you need to put that staircase down.\"",
"It's an armed guard.\n\"Hey there, not sure who you are, but you need to put that staircase back.\"",
"It's an armed guard.\nThe guard regards you with a confused look.\n\"Wait... what on earth is going on here?\""),
("It's a viscount working at a desk.\n\"What are you doing in my courtroom?\nGet out!\"",
"",
"",
"It's an unconscious viscount.",
"It's a half-eaten unconscious viscount.",
"It's a mostly-eaten unconscious viscount.",
"",
"",
""),
("The orc stands guard.\nIt grunts as a warning.",
"\"g<Incredible! No one has ever been able to stomach my body before!>\"",
"\"g<Wow! ...you're... almost at my vitals now!\nIt's... been an honour...>\"",
"An orc stands down.\nIt seems you have won.",
"\"g<Incredible! No one has ever been able to best me in combat before, let alone consume my flesh!\nIt's been an honour to be your meal.>\"",
"\"g<You ... are at my vitals.\nYou're amazing!\nIt's an honour to perish as your meal.>\"",
"The orc stands down.\n\"g<I am grateful for your gift!>\"",
"The orc is eating the human.\n\"g<Thank you so much! This thing is delicious!>\"",
"The orc is sitting down."),
("","","",
"The chef's body does not seem to show signs of life or agression anymore.",
"The chef's half-eaten body does not seem to show signs of life or agression anymore.",
"The chef's lifeless body does not seem to show signs of agression anymore.",
"\"Who are you? How did you get here?\"",
"The chef attacks you.",
""),
("The human stares at you with a confused nervousness.",
"The human was scraming loudly for a moment, but it has already lost consiousness from being eaten.",
"The human's body is almost gone.",
"The human is quivering in the corner.",
"The human was scraming loudly for a moment, but it has already lost consiousness from being eaten.",
"The human's body is almost gone.",
"The human is being eaten. It doesn't look like it will survive.",
"The human smiles at you."
),
("It's an apple tree.",
"It's an apple tree with bite marks in the bark.\n\"OI WHAT THE EFING FU%2AK DO YOU THINK YOU'ER DOING?\nI PUT AN APPLE ON THE FLOOR FA YA IV YA HUNGRY.\nMAYBE SEE IF THERE'S GRUB IN THAT BUILDING THERE.\nNOW LAY OFF.\"",
"It's a stump where there was once an apple tree. You feel sick...",
"It's an apple tree.\n\"OI WHAT THE EFING FU%2AK WAS DAT FOR?\nI PUT AN APPLE ON THE FLOOR FA YA IV YA HUNGRY.\nMAYBE SEE IF THERE'S GRUB IN THAT BUILDING THERE.\nNOW LAY OFF!\"",
"It's an apple tree with bite marks in the bark.\n\"OI WHAT THE EFING FU%2AK WAS DAT FOR?\nI PUT AN APPLE ON THE FLOOR FA YA IV YA HUNGRY.\nMAYBE SEE IF THERE'S GRUB IN THAT BUILDING THERE.\nNOW LAY OFF.\"",
"It's a defeated stump where there was once an apple tree. You feel sick...","","",""),
("It's one of your beloved family members. She looks at you expectantly.",
"It's one of your beloved family members.\nYou tried to eat her.\nShe looks at you with fear, confusion, and horror.\nYou're horrified.\nYou have no idea why you did that.\nYou need to make it up to her NOW!",
"It's the remains of your beloved family member.\nYou supress the urge to vomit.",
"It's one of your beloved family members.\nShe lies injured on the floor.\nShe looks at you with fear and confusion.\nYou're horrified.\nYou have no idea why you did that.\nYou need to make it up to her NOW!",
"It's one of your beloved family members.\nYou tried to eat her.\nShe lies injured on the floor.\nShe looks at you with fear, confusion, and horror.\nYou're horrified.\nYou have no idea why you did that.\nYou need to make it up to her NOW!",
"It's the remains of your beloved family member.\nYou don't feel ok.\nNothing is ok.\nYou hear incoherent voices from *within*.","","",""))

human_speech=(
"\"Am I free? Are you letting me go?\"\n",
"\"THANK YOU SO MUCH!!!\"\n\"I thought I was going to DIE!\nI won't forget this!\"\n",
"The human bows and moves towards the exit.\n",
"The human carefully moves away.\n",
"\"So... I tried digging a tunnel to the easten room while I was trapped. There didn't seem too be a way out, but there's some kind of resturant there. Be careful, it's guarded by a powerful chef. You'll die if you go in unprepared.\nGood luck!\"\n"
)

npc_info=(("A maid is cleaning the corridor.",
"A partially eaten maid gives you a confused look while tending to a wound.",
"A mostly eaten maid is screaming on the floor, begging to die.",
"The brused maid has gone back to cleaning the corridor.",
"A partially eaten maid gives you a terrified look while shouting at you to get back.",
"A mostly eaten maid is crying on the floor, begging to die.",
"The maid has taken a break from cleaning the corridor. You are given a pleasent smile.",
"The maid is sleeping.",
"The maid has woken up."),
("A guard stands guard.\nThe guard regards you with a sceptical look.",
"A half-eaten traumatised guard regards you with a terrified look.",
"An unconscious guard is bleeding out in the corner.",
"A defeated guard is tending to its wounds.",
"A half-eaten defeated guard regards you with a terrified look.",
"An unconscious defeated guard is bleeding out in the corner.",
"A guard stands guard.\nThe guard regards you with a sceptical look.",
"A guard stands guard.\nThe guard regards you with a sceptical look.",
"The guard is still standing guard.\nThe guard regards you with a confused look."),
("There is a viscount working a desk at the far end of the room.\n\"Y<Can I help you?>\"",
"",
"",
"The viscount is unconscious.",
"The half-eaten viscount is still unconscious.",
"The mostly-eaten viscount is still unconscious."),
("An orc stands guard at the east door.\nIt grunts as a warning.",
"The orc stands aside, taken aback by your constitution.",
"The orc is no longer mobile. It seems excited to die.",
"The orc stands aside while tending to its wounds.",
"The orc is taken aback by your constitution.",
"The orc is no longer mobile. It seems very excited to die.",
"The orc stand aside.",
"The orc is eating the human.",
"The orc is sitting down."),
("There is a ferocious chef.","","",
"There is a chef's body.",
"There is a half-eaten chef's body.",
"There is a mostly-eaten chef's lifeless body."),
("A human is shivering in the cell.",
"A half-eaten human is bleading out.",
"There is a mostly-eaten human body.",
"A brused human is quivering.",
"A half-eaten human is bleading out.",
"There is a mostly-eaten human body.",
"You see the human.\nThey are grateful.","",""),
("There is a tree.",
"There is a damaged tree.",
"There is a stump where there was once a tree.",
"There is a damaged tree.",
"There is a damaged tree.",
"There is a damaged stump where there was once a tree."),
("A beloved family member looks at you expectantly.",
"A beloved family member looks at you with fear, confusion, and horror.",
"The remains of a beloved family member lies solemnly on the ground.",
"A beloved family member lies injured on the floor.",
"A beloved family member lies injured on the floor; looking at you with fear, confusion, and horror.",
"The grotesque remains of a beloved family member lies solemnly on the ground.",))

# A reverse ennumeration for index lookup at runtime.
rev_enum_str="""
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

;const char type_enum[28][11]=
{"room","clearing","corridor","prison","bedroom","courtroom","forest","village","basement","treasury","dinette","art room","cave","hall",
 "部屋", "開墾",     "廊下",    "刑務所", "寝室",    "公判廷",    "森",    "村",      "地下室",   "金庫",    "食堂",    "美術室",   "空洞", "会館"}

;const char command_enum[42][6]=
{  "GO","GET", "DROP", "FIGHT", "MEET", "EAT", "SWING", "HELP", "QUIT", "RESET",\
"VISIT","LIFT","THROW","HIT",  "CHECK", "SWALL","USE",  "EXIT", "RESTA", "HINT",\
  "行","取",   "落",   "戦",     "合",   "食",   "振",    "辞",   "リ",    "助",\
  "訪","拾",   "投",   "当",     "見",   "飲",   "使",    "出",   "再",    "仄",\
"SAVE","セ"}

;"""

def format_str(inp:str) -> str:
  "Highlight npc names so that the player knows they can type them as part of a valid command."
  for i in ('maid', 'viscount', 'orc', 'chef', 'human', 'tree', 'family member', 'メイド', '子爵', '鬼', 'コック', '人間', '木', '家の人', 'guard', '守衛'):
    if i in inp:
      inp=inp.replace(i,"\\033[1m"+i+"\\033[0m",1)
      break
  return inp

def parse_npc_objs(itera) -> tuple:
  "Highlight npc names in an iterable of strings so that the player knows they can type them as part of a valid command."
  if any(not isinstance(i,str)for i in itera):
    return *(parse_npc_objs(i)for i in itera),
  else: return *(format_str(i)for i in itera),

def parse_mkdown(itera) -> tuple:
  "Very basic custom markdown parsing, expects opening markdown to follow a space."
  if len(itera[0])==2 and all(isinstance(i[0],str)and isinstance(i[1],int)for i in itera):
    strs=parse_mkdown([i[0]for i in itera])
    return *((strs[i],itera[i][1])for i in range(len(strs))),
  if any(not isinstance(i,str)for i in itera):
    return *((parse_mkdown(i)if len(i)>0 else ())for i in itera),
  else:return *(i.\
    replace(" **"," \\033[1m").# Bold
    replace(" *"," \\033[3m").#  Italic
    replace("\n**","\n\\033[1m").# Bold
    replace("\n*","\n\\033[3m").#  Italic
    replace("**","\\033[0m").#   Close formatting
    replace("*","\\033[0m").#    Close formatting
    replace(">","\\033[0m").#    Close formatting
    replace("dr<","\\033[31;107m").# Dark red
    replace("r<","\\033[91;40m").#   Red
    replace("R<","\\033[30;101m").#  Red background
    replace("g<","\\033[92;40m").#   Green
    replace("G<","\\033[30;102m").#  Green background
    replace("y<","\\033[93;40m").#   Yellow
    replace("Y<","\\033[30;103m").#  Yellow background
    replace("b<","\\033[94;40m").#   Blue
    replace("B<","\\033[30;104m").#  Blue background
    replace("m<","\\033[95;40m").#   Magenta
    replace("M<","\\033[30;105m").#  Magenta background
    replace("c<","\\033[96;40m").#   Cyan
    replace("C<","\\033[30;106m").#   Cyan background
    replace("%2A","*") # Unescape literal *.
    for i in itera),

def make_c_dirlist_arr(arr:dict,name:str)->str:
  out="const char* const "+name+"[14][14][6]={"
  for i in range(14):
    out+="{"
    for j in range(14):
      out+="{"
      for k in range(6):
        new=arr.get((i,j,k+8))
        if new==None:out+="{0},"
        else:out+='"'+new+'",'
      out+="},\n"
    out+="},"
  return out+"};"

def make_c_arr(arr:tuple,name:str)->str:
  if (any(isinstance(i,str)for i in arr)!=any(isinstance(i,str)for i in arr)):raise ValueError
  is_2d=not any(isinstance(i,str)for i in arr)
  out=("const char* const "+name+"["+str(len(arr))+"]["+str(len(arr[0]))+"] = "+"{{"+"\n")if is_2d else("const char* const "+name+"["+str(len(arr))+"] = {"+"\n")
  if is_2d:
    for i in arr:
      for j in i:
        out+=("\""+j.replace("\n","\\n").replace("\"","\\\"")+"\",\n")if len(j)>0 else("{0},")
      out+="},{"
    return out[:-3]+"}};"
  else:
    for i in arr:out+=("\""+i.replace("\n","\\n").replace("\"","\\\"")+"\",\n")if len(i)>0 else("{0},\n")
    return out[:-2]+"};"

def make_text_arr(arr:tuple,name:str)->str:
  is_2d=not any(isinstance(i[0][0],str)for i in arr)
  out=("const Textarr "+name+"["+str(len(arr))+"]["+str(len(arr[0]))+"] = {{\n")if is_2d else("const Textarr "+name+"["+str(len(arr))+"] = {\n")
  if is_2d:
    for i in arr:
      for j in i:
        out+=("{.arr={\""+"\",\"\\n".join((k[0])if not "…"in k[0] else(k[0].split("…",1)[0]+"\",\".\",\".\",\"."+(("\",\""+k[0].split("…",1)[1])if len(k[0].split("…",1)[1])>0 else""))for k in j)+"\\n\"}, .sleeps={"+",".join(str(k[1])if not "…"in k[0] else((str(k[1]//2)+",")*(4 if len(k[0].split("…",1)[1])>0 else 3)+str(k[1]))for k in j)+"}}")if len(j)>0 else("{0},")
      out+="},\n{"
    return out[:-2]+"};"
  else:
    for i in arr:out+=(("{.arr={\""+"\",\"\\n".join((k[0])if not "…"in k[0] else(k[0].split("…",1)[0]+"\",\".\",\".\",\"."+(("\",\""+k[0].split("…",1)[1])if len(k[0].split("…",1)[1])>0 else""))for k in i)+"\\n\"}, .sleeps={"+",".join(str(k[1])if not "…"in k[0] else((str(k[1]//2)+",")*(4 if len(k[0].split("…",1)[1])>0 else 3)+str(k[1]))for k in i)+"}},\n")if len(i)>0 else("{0},\n"))
    return out[:-2]+"};"

item_info=parse_mkdown(item_info)
item_food=parse_mkdown(item_food)
item_death=parse_mkdown(item_death)
npc_speech=parse_mkdown(npc_speech)
npc_info=parse_npc_objs(parse_mkdown(npc_info))

if __name__=="__main__":
  print(rev_enum_str)
  print("\n")
  print(make_c_dirlist_arr(dict(zip(tuple(room_tra.keys()),parse_mkdown(tuple(room_tra.values())))),"room_tra"))
  print("\n")
  print(make_c_arr(item_info,"item_info"))
  print("\n")
  print("const float item_dmg[16]={",*(str(i)+","for i in item_dmg),"};\n")
  print(make_text_arr(item_food,"item_food"))
  print("\n")
  print(make_text_arr(item_death,"item_death"))
  print("\n")
  print(make_c_arr(npc_speech,"npc_speech"))
  print("\n")
  print("extern",make_c_arr(human_speech,"human_speech"))
  print("\n")
  print(make_c_arr(npc_info,"npc_info"))