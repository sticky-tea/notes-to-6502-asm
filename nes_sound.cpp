#include "nes_sound.hpp"

std::string read_file(const std::string& fileName)
{
    std::string s;
    char temp;
    std::ifstream ifs;

    ifs.open(fileName, std::ios::in);
    
    ifs.unsetf(std::ios::skipws);
    while(ifs >> temp)
        s += temp;
    return s;
}

std::string nes_sound::makeCode(std::vector<double> freq, std::vector<int> dur, bool ntsc, bool looped) 
{
	std::string control_byte = "10011111";
	std::string ft_byte = "";
	std::string ct_byte = "";
	std::string extra3bites = "000";
	std::string cur_note = "00000000";
	std::string cur_dur = "11111";
	int k = 0;

	makeNesFreq(freq);

	std::string code = "music:\n\n\tPHA\n\n";

	for(auto i : nes_freq)
	{
		auto cur_byte = make11bitWord(i);
		cur_note = cur_byte.first;
		extra3bites = cur_byte.second;

		cur_dur = std::bitset<5>(dur[k]).to_string();

		ft_byte = cur_note;
		ct_byte = cur_dur + extra3bites;

		code += "; note: " + std::to_string(i) + " hz" + " = " + ft_byte + ", " + extra3bites + "\n";
		code += "note_"+std::to_string(k)+":\n";
		code += "\tLDA frames\n\tAND #%00000000\n\tSTA frames\n\n";
		code += "\tLDA #%00000001\n\tSTA $4015\n";
		code += "\tLDA #%" + control_byte + "\n\tSTA $4000\n";
		code += "\tLDA #%" + ft_byte + "\n\tSTA $4002\n";
		code += "\tLDA #%" + ct_byte + "\n\tSTA $4003\n\n";

		code += "loop_"+std::to_string(k)+":\n";
		code += "\tLDA frames\n\tCMP #%" + make8bitWord(cur_dur) + "\n";
		code += "\tBEQ note_"+std::to_string(k+1)+"\n";
		code += "\tJMP loop_"+std::to_string(k) + "\n\n";

		k += 1;
	}
	code += "note_"+std::to_string(k)+":\n";
	
	if(looped)
		code += "\tJMP music\n";

	code += "\tPLA\n";

	code += "RTS\n";

	return code;
}

void nes_sound::makeNesFreq(std::vector<double> freq) 
{
	int CPU = ntsc ? 1789773 : 1662607;

	for(auto i : freq)
		nes_freq.push_back(round(CPU/(16*i)-1));
}

std::pair<std::string, std::string> nes_sound::make11bitWord(int num)
{
	std::string snum = std::bitset<11>(num).to_string();
	return {snum.substr(3, snum.length()-3), snum.substr(0, 3)};
}

std::string nes_sound::make8bitWord(std::string snum)
{
	while(snum.length() < 8)
	{
		snum = "0" + snum;
	}

	return snum;
}

bool nes_sound::is8bit(std::string snum)
{
	return snum.length() == 8;
}

std::string nes_sound::addAsmBasic(std::string code, std::string basic_filename)
{
	std::string prog = "";

	prog += read_file(basic_filename);
	prog += "\n\n" + code + "\n";

	prog += "\n\
NMI:\n\
\tLDA #$00\n\
\tSTA $2003\n\
\tLDA #$02\n\
\tSTA $4014\n\
\tINC frames\n\
\n";

	prog += "End:\n\tRTI\n\n";

	prog += "\n\
  .bank 1\n\
  .org $FFFA\n\
  .dw NMI\n\
  .dw RESET\n\
  .dw 0\n\
\n\
  .bank 2\n\
  .org $0000\n\
";

	return prog;
}
