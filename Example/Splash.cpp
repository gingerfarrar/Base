#include "Splash.h"
#include "sfwdraw.h"
#include <iostream>
using namespace sfw;

void Splash::init(int a_font)
{
	font = a_font;
}

void Splash::play() { timer = 3.f; }

void Splash::draw()
{
	char buffer[64];
	sprintf_s(buffer, "Splash Time: %f", timer);
	drawString(font, "Splash State", 100, 100, 20, 20);
	drawLine(100, 80, 100 + 500 * (timer / 3.f), 80);
}

void Splash::step() { timer -= getDeltaTime(); }

APP_STATE Splash::next()
{
	if (timer < 0)
	{
		return ENTER_DEPART;
	}
	return SPLASH;
}