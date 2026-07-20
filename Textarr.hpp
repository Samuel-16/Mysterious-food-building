;static inline Textarr& operator<<(struct Textarr &inp, const char* string){
  assert(string!=nullptr);
  inp.arr[inp.end]=string;
  ++inp.end;
  inp.canApp=false;
  return inp;
}

;static inline Textarr& operator<<(struct Textarr &inp, const char string){
  if(inp.canApp) *(inp.varStrEnd++)=string;
  else {
    *(++inp.varStrEnd)=string;
    inp.arr[inp.end++]=inp.varStrEnd++;
  }
  inp.canApp=true;
  return inp;
}

;static inline Textarr& operator<<(struct Textarr &inp, const byte number){
  if(number<10)
    return inp << ((char) ('0'+number));
  if (!inp.canApp){
    inp.arr[inp.end++]=++inp.varStrEnd;
    inp.canApp=true;}
  if(number<100){
    *inp.varStrEnd =   ((char) ('0'+(number/10)));
    *(inp.varStrEnd+1)=((char) ('0'+(number%10)));
    inp.varStrEnd+=2;
    return inp;}
  *inp.varStrEnd  =  (number<200?'1':'2');
  *(inp.varStrEnd+1)=((char) ('0'+((number/10)%10)));
  *(inp.varStrEnd+2)=((char) ('0'+(number%10)));
  inp.end+=3;
  return inp;
}

;template <typename potentialNum> static inline Textarr& operator<<(struct Textarr &inp, const potentialNum number){
  if (!inp.canApp){
    inp.arr[inp.end++]=++inp.varStrEnd;
    inp.canApp=true;}
  auto result = std::to_chars(inp.varStrEnd, inp.varStrEnd + 36, number);
  assert(result.ec == std::errc{});
  inp.varStrEnd = result.ptr;
  return inp;
}

;static inline void operator-(struct Text &inp, const byte number){
  inp.sleep=number;
}

;static inline Textarr& operator-(struct Textarr &inp, const byte number){
  assert(inp.end>0);
  inp.sleeps[inp.end-1]=number;
  return inp;
}

;static inline void operator+(struct Text &inp, const byte number){
  inp.sleep+=number;
}

;static inline Textarr& operator+(struct Textarr &inp, const byte number){
  assert(inp.end>0);
  inp.sleeps[inp.end-1]+=number;
  return inp;
}

static inline Textarr& operator<<(struct Textarr &inp, const Text apen){
  assert(apen.string);
  return (inp << apen.string) - apen.sleep;
}

static inline Textarr& operator<<(struct Textarr &inp, const Textarr apen){
  for(std::size_t i=0;apen.arr[i]!=nullptr;++i){
    (inp << apen.arr[i]) - apen.sleeps[i];}
  return inp;
}
;