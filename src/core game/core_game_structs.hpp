#include <cstdint> // For better practice int types.

// Set datatype names. to avoid needing to type longer names repeatedly.
using byte=std::uint8_t;  // A byte will be a one byte positive integer.
using ibyte=std::uint_fast8_t;  // An ibyte will be at least a one-byte positive integer.
using word=std::uint_least16_t; // A word will be a two byte positive integer.
 
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
    const char* description="MISSING DESCRIPTION";
    const char* jp_description="エラー: 説明がありません";
}

;struct Npc{
    word inventory=0;
    byte hp=4;
    byte maxhp=4;
    float avo=0.05;
    byte threshold=4;
}

;struct Text{
  const char* string=nullptr;
  byte sleep=0;}

;struct Textarr{
  const char* arr[64]={ 0 };
  byte sleeps[64]={0};
  char* varStrEnd=nullptr;
  byte end=0;
  bool canApp=false;
}
;