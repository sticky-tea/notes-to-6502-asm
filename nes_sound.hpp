#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <fstream>

class nes_sound
{
	std::vector<double> nes_freq;
	bool ntsc = false;
public:
	std::string makeCode(std::vector<double> freq, std::vector<int> dur, bool ntsc, bool looped);
	std::string addAsmBasic(std::string code, std::string basic_filename);
private:
	void makeNesFreq(std::vector<double> freq);

	std::pair<std::string, std::string> make11bitWord(int num);
	std::string make8bitWord(std::string snum);

	bool is8bit(std::string snum);
};