class game_state{
  private:
    char outBuff[1024]={0};
    #include "core_game_data.hpp"

    Textarr counter(Npc* npc,const char* npc_name, Textarr cout){
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


    [[nodiscard]]
    inline Textarr check_orc(Textarr cout){
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
    };

    inline byte check_speech(byte npc_no){
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
    Textarr describe(const Location location, Textarr cout){
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
        cout
        << room_tra[location.type][locs[location.north].type][0]
        << '\n';
      else if ((locs[loc].type==CLEARING || locs[loc].type==FOREST)&& (inventory & RESTAURANT))
        cout << "There is a vast expance of forest to the \033[1mnorth\033[0m.\n";
      if (location.east>0){
        assert(room_tra[location.type][locs[location.east].type][1]!=nullptr);
        cout
        << room_tra[location.type][locs[location.east].type][1]
        << '\n';}
      else if ((locs[loc].type==CLEARING || locs[loc].type==FOREST)&& (inventory & RESTAURANT))
        cout << "There is a vast expance of forest to the \033[1meast\033[0m.\n";
      if (location.south>0)
        cout
        << room_tra[location.type][locs[location.south].type][2]
        << '\n';
      else if ((locs[loc].type==CLEARING || locs[loc].type==FOREST)&& (inventory & RESTAURANT))
        cout << "There is a vast expance of forest to the \033[1msouth\033[0m.\n";
      if (location.west>0)
        cout
        << room_tra[location.type][locs[location.west].type][3]
        << '\n';
      else if ((locs[loc].type==CLEARING || locs[loc].type==FOREST)&& (inventory & RESTAURANT))
        cout << "There is a vast expance of forest to the \033[1mwest\033[0m.\n";
      if (location.up>0)
        cout
        << room_tra[location.type][locs[location.up].type][4]
        << '\n';
      if (location.down>0)
        cout
        << room_tra[location.type][locs[location.down].type][5]
        << '\n';
      return cout;}

    [[nodiscard]]
    inline Textarr pull_lever(Textarr cout,bool eats){
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
      return cout;}
  public:
    //Global output string buffer:
    void clearOutBuff(){
    for(std::size_t i=0;i<sizeof(outBuff);++i)
        outBuff[i]='\0';};

    Textarr describe(const Location location){
      char buff[24]={0};
      Textarr cout=describe(location,{.varStrEnd=buff});
      return cout;
    }

    Textarr describe(){
      return describe(locs[loc]);
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
                  if(location.north==0 && (!(inventory & RESTAURANT) || !(location.type==CLEARING || location.type==FOREST))){
                    cout<<"No way to go north.\n";
                    return cout;}
                  loc=location.north;
                  cout<<"You went north.\n";
                  break;
                case EAST:
                  if(location.east==0 && (!(inventory & RESTAURANT) || !(location.type==CLEARING || location.type==FOREST))){
                    cout<<"No way to go east.\n";
                    return cout;}
                  loc=location.east;
                  cout<<"You went east.\n";
                  break;
                case SOUTH:
                  if(location.south==0 && (!(inventory & RESTAURANT) || !(location.type==CLEARING || location.type==FOREST))){
                    cout<<"No way to go south.\n";
                    return cout;}
                  loc=location.south;
                  cout<<"You went south.\n";
                  break;
                case WEST:
                  if(location.west==0 && (!(inventory & RESTAURANT) || !(location.type==CLEARING || location.type==FOREST))){
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

    char* get_player_hp(char outBuff[6]){
      outBuff[0]=('0'+(player_hp/10));
      outBuff[1]=('0'+(player_hp%10));
      outBuff[2]='/';
      outBuff[3]=('0'+(player_hp_max/10));
      outBuff[4]=('0'+(player_hp_max%10));
      outBuff[5]='\0';
      return outBuff;}

}