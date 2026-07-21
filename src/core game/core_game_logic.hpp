#include <cstdint> // For better practice int types.
#include <cassert> // To alert if any program states intended to be impossible are reached.

class game_state{
  private:
    char outBuff[64]={0};
    #include "core_game_data.hpp"

    Textarr counter(Npc* npc,const char* npc_name, Textarr cout);

    [[nodiscard]]
    inline Textarr check_orc(Textarr cout);

    inline byte check_speech(byte npc_no);

    [[nodiscard]]
    Textarr describe(const Location location, Textarr cout);

    [[nodiscard]]
    inline Textarr pull_lever(Textarr cout,bool eats);

    [[nodiscard]]
    Textarr CakeRoom(Textarr cout,byte& cakelife,const byte cakemax);

  public:
    //Global output string buffer:
    void clearOutBuff();

    Textarr describe(const Location location);

    Textarr describe();

    Textarr do_action(parse_result &action);

    [[nodiscard]]
    Textarr FreeHuman(char buff[]);

    char* get_player_hp(char outBuff[6]);

};