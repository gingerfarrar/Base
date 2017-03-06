#pragma once
#include "constdecl.h"

class Depart
{
	int font;
	float timer;
public:

	void init(int a_font);

	void draw();


	APP_STATE next();
};