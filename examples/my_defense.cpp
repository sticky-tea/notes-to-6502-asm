#include <iostream>
#include <fstream>

#include "../nes_sound.hpp"

#define A1 440.0
#define	B1 493.88
#define	C2 523.25
#define	D2 587.32
#define E2 659.26
#define	F2 698.46
#define G2 784.0
#define A2 880.0
#define B2 987.75
#define C3 1046.50
#define A3 1720.00

#define P 0.0

#define FN 31
#define HN 15
#define QH 7
#define EN 3 

int main()
{
	std::vector<double> f = {A1, A1, A1, A1, C2, A2, G2, A2, P, G2, G2, G2, G2, G2, G2, G2, E2, P,
							 A1, A1, A1, A1, C2, A2, G2, A2, P, G2, G2, G2, G2, G2, G2, G2, E2, P,
							 E2, G2, G2, G2, G2, G2, G2, A2, E2, E2, D2, D2, P,
							 C2, C3, P, C3, C3, C3, C3, C3, B2, P,
							 C3, C3, C3, C3, B2, A2, G2, A2, B2, C3, B2, P};
	std::vector<int> d = {HN,HN,HN,HN,FN,HN,HN,FN,FN,HN,HN,HN,HN,FN,HN,HN,FN, FN,
						  HN,HN,HN,HN,FN,HN,HN,FN,FN,HN,HN,HN,HN,FN,HN,HN,FN, FN,
						  HN, HN, HN, HN, FN, HN, HN, FN, HN, HN, FN, HN, FN,
						  FN, FN, HN, HN, HN, HN, HN, HN, FN, FN,
						  HN, HN, HN, FN, HN, HN, FN, HN, HN, FN, FN, FN}; 

	nes_sound snd;

	std::string prog = snd.addAsmBasic(snd.makeCode(f, d, true, true), "start.asm");

	std::ofstream out;
	out.open("sound.asm");

	out << prog;
	out.close();
}