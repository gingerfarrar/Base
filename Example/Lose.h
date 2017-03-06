#pragma once
#include "constdecl.h"
class Lose
{
	int font;
	float timer;
public:

	void init(int a_font);

	void play();

	void draw();

	void step();

	APP_STATE next();
};