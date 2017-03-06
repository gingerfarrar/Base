
#include "sfwdraw.h"
#include "GameState.h"

#include "Splash.h"
#include "Lose.h"
#include "Depart.h"
#include "Win.h"

void main()
{
	sfw::initContext(800,600);
	unsigned font = sfw::loadTextureMap("../res/fontmap.png", 16, 16);
	
	GameState gs;

	Splash splash;
	
	Lose lose;
	Depart dep;
	Win win;

	splash.init(font);
	gs.init(); 
	gs.play(); 
	lose.init(font);
	dep.init(font);
	win.init(font);

	unsigned state = ENTER_SPLASH;
	while (sfw::stepContext())
	{
		
		switch (state)
		{
		case ENTER_SPLASH:
			splash.play();
		case SPLASH:
			splash.step();
			splash.draw();
			state = splash.next();
			break;
		case ENTER_DEPART:
		case DEPART:
			dep.draw();
			state = dep.next();
			break;
		case ENTER_GAAMESTATE:
			gs.play();
		case GAAMESTATE:
			gs.step();
			gs.draw();
			state = gs.next();
			break;
		case ENTER_WIN:
		case WIN:
			win.draw();
			state = win.next();
			break;
		case ENTER_LOSE:
			lose.play();
		case LOSE:
			lose.step();
			lose.draw();
			state = lose.next();
			break;
		}
	}

	gs.stop(); 
	gs.term(); 


	sfw::termContext();

}