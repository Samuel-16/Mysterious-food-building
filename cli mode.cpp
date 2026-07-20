#include <iostream> // For outputting to, and inputting from the terminal.
#include <string> // For the C++ specific dynamic string.
#include <chrono> // For making the program wait.
#include <thread> // For making the program wait.
#include <cstdlib> // For random number generation.
#include <cctype> // For upper/lower case conversion.
#include <cstdint> // For better practice int types.
#include <charconv> // To convert numbers to string.
#include <cassert> // To alert if any program states intended to be impossible are reached.

#include "enums.h"
#include "core_game_structs.hpp"
#include "Textarr.hpp"
#include "descript_decls.h"
#include "core_game_logic.hpp"

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

static inline std::ostream& operator<<(std::ostream& inp, const Textarr outp){
  for(ibyte i=0;i<outp.end;++i){
    inp << outp.arr[i];
    #ifdef NDEBUG
    std::this_thread::sleep_for(std::chrono::milliseconds((outp.sleeps[i]<<8)+(1<<6)));
    #endif
  }
  return inp;}

game_state game;

;int main() {
    ;std::cout<<"You are on an adventure to find a source of nourishment, and have entered a strange building you have found in the forest.\n"
    << "Available commands are: GET, DROP, GO, FIGHT, MEET, EAT, SWING, QUIT, RESET, and HELP.\n\n"
    << game.describe()
    << "What will you do?\n"
    ;char input_buffer[256]
    
    ;parse_result action
    ;while (action.com<QUIT){
        ;char hpBuff[7];
        ;std::cout<<"HP: "
        << game.get_player_hp(hpBuff)
        << " >"
        <<std::flush
        ;std::cin.getline(input_buffer,255)
        ;action=parse(input_buffer)
        ;Textarr text = game.do_action(action)
        ;std::cout<<text
        ;game.clearOutBuff()
        ;if(action.com==HUMAN_CONVERSATION){
          ;bool check=true
          ;std::cout<<human_speech[0]<<"[Y/n] "
          ;std::cin.getline(input_buffer,255)
          ;for(ibyte i=0;input_buffer[i]!='\0'&&i<255;++i){
            if((input_buffer[i] &223)=='N'){
              check=false;
              break;}}
          if(check){
            ;char outBuff[64]={0};
            ;text=game.FreeHuman(outBuff)
            ;std::cout << text
          ;}
        action.com=0;}
    ;}
    if(action.com==WIN_STATE)
      std::cout<<"YOU WIN!!!";
;}