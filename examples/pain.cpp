/*
 * Pain - Shut your mouth solo
 * It will create sound.asm file
 * To compile you can use NESasm
*/

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

#define FN 31
#define HN 15
#define QH 7
#define EN 3 

int main()
{
	std::vector<double> f = {A1, E2, A1, F2, E2, D2, E2, D2, E2, F2, F2, E2, D2, A1, E2, A1, F2, E2, D2, C2, D2, C2, B1, B1, C2, B1};
	std::vector<int> d = {FN, HN, HN, FN, HN, HN, FN, HN, HN, HN, HN, HN, HN, FN, HN, HN, FN, HN, HN, FN, HN, HN, HN, HN, HN, HN}; 

	nes_sound snd;

	std::string prog = snd.addAsmBasic(snd.makeCode(f, d, true, true), "start.asm");

	std::ofstream out;
	out.open("sound.asm");

	out << prog;
	out.close();
}