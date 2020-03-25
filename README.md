# Notes to NES assembler converter
This lib translates the set of frequencies and durations of notes into the 6502 assembler code

# How to use
To make code use:
```cpp
nes_sound snd;
snd.makeCode(f, d, n, l);
```
where:
f - vector of double of frequencies, 
d - vector of int of durations, 
n - bool, true if NTSC, 
l - bool, true if looped, 

Also you can make a whole program if you have a file:
```cpp
std::string code = snd.makeCode(f, d, n, l);
std::string prog = snd.addAsmBasic(code, basic_filename);
```
Example of basic_filename you can see in examples

# How to compile examples
```bash
$ cd examples
$ g++ examplename.cpp ../nes_sound.cpp
```

# How to test
You can compile .asm using [NESasm](https://github.com/camsaul/nesasm) and emulate using [FCEUX](http://www.fceux.com/web/home.html)
