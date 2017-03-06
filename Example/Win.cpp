#include "Win.h"
#include "sfwdraw.h"
#include <iostream>
using namespace sfw;

void Win::init(int a_font)
{
	font = a_font;
}

void Win::draw()
{
	char buffer[64];
	drawString(font, "WINNER!", 300, 400, 20, 20);
}

APP_STATE Win::next()
{
	return WIN;
}
