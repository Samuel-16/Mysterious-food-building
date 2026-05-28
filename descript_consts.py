item_info=("It looks like a toy sword, but you probably have the strength to use it to kill.",
"Though many bad apples rest on the floor, this one looks edible.\nIt must have recently fallen.",
"Yay! Many apples!",
"A common magic potion for healing.",
"Multiple health potions!",
"A cushioned wooden chair.",
"A loose staircase that looks like it previously led up to the broken door.\nMaybe you could DROP it somewhere else?",
"A kitchen knife.\nYou could easily use this as a simple weapon.",
"This is it!\nYou're not quite sure how to open it, but maybe someone back at your village might know.\nIf you could JUST take this resturant back... surely you would be able to feed not just your family, but your whole village!",
"The remains of a body.\nYou don't think it would be a good idea to eat this.",
"A rusty sword.",
"A sword.\nIt looks sharp.",
"This sword looks stronger and sharper than anything you've ever seen.",
"This thing seems like it represents a value far greater than what your village is used to seeing.",
"A maid's brush.",
"You think you can pull this lever.")

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

npc_speech=(("The maid is cleaning the corridor.\n\"Can I help you?\"",
"The maid isn't cleaning the corridor anymore.\n\"Owch!\nDid you just eat my %2A%2A%2A%2A?\nWhy?\"",
"The maid isn't cleaning the corridor anymore.\n\"Owowowowowowowowowowwwwwwwww!\nOk ok okokokokok.\nPlease... please just kill me...\nI can't live like this.\"",
"The maid has gone back to cleaning the corridor.\n\"It still hurts...\nWhat was all that for?\"",
"The maid isn't cleaning the corridor anymore.\n\"Owch!\nYou win ok!\nStop eating me!\"",
"The maid is crying now.\n\"Owowowowowowowowowowwwwwwwww!\nOk ok. Just finish me off.\"\nThe maid tries to smile through the tears.\n\"...I'm ... glad you liked me...\"",
"The maid is cleaning the corridor.\n\"Is that a restaurant in your pocket?\n♡ Or are you just happy to see me? ♡\"",
"The maid is fast asleep.",
"\"Oh. Was that my boss?\""),
("It's an armed guard.\n\"Hey there, not sure who you are, but the way up is out of action.\nYou'll have to go round the other way.\"",
"It's a half-eaten traumatised guard.\n\"AAAGGAGG! Get away! GET AWAY!\"",
"The guard isn't conscious anymore.\nIt's bleeding out.",
"It's a defeated guard.\n\"Ok! Ok! I admit defeat!\"",
"It's a half-eaten traumatised guard.\n\"AAAGGAGG! OW! OW OW OW! I'm done! I'm done! Please just go.\"",
"The guard isn't conscious anymore.\nIt's bleeding out.",
"It's an armed guard.\n\"Hey there, not sure who you are, but you need to put that staircase down.\"",
"It's an armed guard.\n\"Hey there, not sure who you are, but you need to put that staircase back.\"",
"It's an armed guard.\nThe guard regards you with a confusing look."),
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
"\"Incredible! No one has ever been able to stomach my body before!\"",
"\"Wow! ...you're... almost at my vitals now!\nIt's... been an honour...\"",
"An orc stands down.\nIt seems you have won.",
"\"Incredible! No one has ever been able to best me in combat before, let alone consume my flesh!\nIt's been an honour to be your meal.\"",
"\"You ... are at my vitals.\nYou're amazing!\nIt's an honour to perish as your meal.\"",
"The orc stands down.\n\"I am grateful for your gift!\"",
"The orc is eating the human.\n\"Thank you so much! This thing is delicious!\"",
"The orc is sitting down."),
("","","",
"The chef's body does not seem to show signs of life or agression anymore.",
"The chef's half-eaten body does not seem to show signs of life or agression anymore.",
"The chef's lifeless body does not seem to show signs of agression anymore.",
"\"Who are you? How did you get here?\"",
"The chef attacks you.",
""),
("\"Am I free? Are you letting me go?\"",
"The human was scraming loudly for a moment, but it has already lost consiousness from being eaten.",
"The human's body is almost gone.",
"The human is quivering in the corner.",
"The human was scraming loudly for a moment, but it has already lost consiousness from being eaten.",
"The human's body is almost gone.",
"\"THANK YOU SO MUCH!!!\"\n\"I thought I was going to DIE!\nI won't forget this!\"\nThe human bows and moves towards the exit.",
"The human carefully moves away.",
"\"So... I tried digging a tunnel to the easten room while I was trapped. There didn't seem too be a way out, but there's some kind of resturant there. Be careful, it's guarded by a powerful chef. You'll die if you go in unprepared.\nGood luck!\""),
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
"An unconscious defeated guard is bleeding out in the corner."),
("There is a viscount working a desk at the far end of the room.\n\"Y<Can I help you?>\"",
"",
"",
"The viscount is unconscious.",
"The half-eaten viscount is still unconscious.",
"The mostly-eaten viscount is still unconscious.",
"",
"",
""),
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
"There is a mostly-eaten chef's lifeless body.","","",""),
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
"There is a damaged stump where there was once a tree.","","",""),
("A beloved family member looks at you expectantly.",
"A beloved family member looks at you with fear, confusion, and horror.",
"The remains of a beloved family member lies solemnly on the ground.",
"A beloved family member lies injured on the floor.",
"A beloved family member lies injured on the floor; looking at you with fear, confusion, and horror.",
"The grotesque remains of a beloved family member lies solemnly on the ground.",))

def format_str(inp:str) -> str:
  "Highlight npc names so that the player knows they can type them as part of a valid command."
  for i in ('maid', 'guard', 'viscount', 'orc', 'chef', 'human', 'tree', 'family member', 'メイド', '守衛', '子爵', '鬼', 'コック', '人間', '木', '家の人'):
    inp=inp.replace(i,"\033[1;30;107m"+i+"\033[0m")
  return inp

def parse_npc_objs(itera) -> tuple:
  "Highlight npc names in an iterable of strings so that the player knows they can type them as part of a valid command."
  if any(not isinstance(i,str)for i in itera):
    return *(parse_npc_objs(i)for i in itera),
  else: return *(format_str(i)for i in itera),

def parse_mkdown(itera) -> tuple:
  "Very basic custom markdown parsing, expects opening markdown to follow a space."
  if any(not isinstance(i,str)for i in itera):
    return *(parse_mkdown(i)for i in itera),
  else:return *(i.\
    replace(" **"," \033[1m").# Bold
    replace(" *"," \033[3m").#  Italic
    replace("**","\033[0m").#   Close formatting
    replace("*","\033[0m").#    Close formatting
    replace(">","\033[0m").#    Close formatting
    replace("dr<","\033[31;107m").# Dark red
    replace("r<","\033[91;40m").#   Red
    replace("R<","\033[30;101m").#  Red background
    replace("g<","\033[92;40m").#   Green
    replace("G<","\033[30;102m").#  Green background
    replace("y<","\033[93;40m").#   Yellow
    replace("Y<","\033[30;103m").#  Yellow background
    replace("b<","\033[94;40m").#   Blue
    replace("B<","\033[30;104m").#  Blue background
    replace("m<","\033[95;40m").#   Magenta
    replace("M<","\033[30;105m").#  Magenta background
    replace("c<","\033[96;40m").#   Cyan
    replace("C<","\033[30;106m").#   Cyan background
    replace("%2A","*") # Unescape literal *.
    for i in itera),

def make_c_arr(arr:tuple,name:str)->str:
  if (any(isinstance(i,str)for i in arr)!=any(isinstance(i,str)for i in arr)):raise ValueError
  is_2d=not any(isinstance(i,str)for i in arr)
  out=("const char* const "+name+"["+str(len(arr))+"]["+str(len(arr[0]))+"] = "+"{{"+"\n")if is_2d else("const char* const "+name+"["+str(len(arr))+"] = {"+"\n")
  if is_2d:
    for i in arr:
      for j in i:
        out+=("\""+j.replace("\n","\\n").replace("\"","\\\"")+"\",\n").replace("\033","\\033")if len(j)>0 else("{0},")
      out+="},{"
    return out[:-3]+"}};"
  else:
    for i in arr:out+=("\""+i.replace("\n","\\n").replace("\"","\\\"").replace("\033","\\033")+"\",\n")if len(i)>0 else("{0},\n")
    return out[:-2]+"};"


item_info=parse_mkdown(item_info)
npc_speech=parse_mkdown(npc_speech)
npc_info=parse_npc_objs(parse_mkdown(npc_info))

if __name__=="__main__":
  print(make_c_arr(item_info,"item_info"))
  print("\n")
  print("const float item_dmg[16]={",*(str(i)+","for i in item_dmg),"};\n")
  print(make_c_arr(npc_speech,"npc_speech"))
  print("\n")
  print(make_c_arr(npc_info,"npc_info"))