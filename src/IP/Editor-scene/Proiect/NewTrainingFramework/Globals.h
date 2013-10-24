#pragma once

class Globals
{
public:
	static const int screenWidth = 960;
	static const int screenHeight = 720;
	static short int keypressed;
	static short int effectpressed;
	enum Move{moveF,moveB,moveL,moveR,moveU,moveD,rotU,rotD,rotL,rotR};
};