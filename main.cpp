#include "ShootingGame.h"

int main(void){
	nori::ShootingTutorial* shooting = new nori::ShootingTutorial("STG",DEFAULT_WINDOW_WIDTH,DEFAULT_WINDOW_HEIGHT);

	shooting->start();
	
	delete shooting;
	return 0;
}
