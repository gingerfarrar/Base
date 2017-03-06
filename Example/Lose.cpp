#include "Lose.h"
#include "sfwdraw.h"
#include <iostream>
using namespace sfw;
void Lose::init(int a_font)
{
	font = a_font;
}

void Lose::play() { timer = 3.f; }

void Lose::draw()
{
	char buffer[64];
	sprintf_s(buffer, "Time: %f", timer);
	drawString(font, "LOSER! Try harder", 50, 500, 20, 20);
	drawLine(100, 80, 100 + 500 * (timer / 3.f), 80);
}

void Lose::step() { timer -= getDeltaTime(); }

APP_STATE Lose::next()
{
	if (timer < 0)
	{
		return ENTER_SPLASH;
	}
	return LOSE;
}