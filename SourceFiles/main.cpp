#include "Game.h"


int main()
{
	Game game("GPT", 1900, 1000);

	//MAIN LOOP

	while(!glfwWindowShouldClose(game.getWindow())) //as long as the window is not closed it will be running
	{
		game.update();
		game.render();
	}


	return 0;
}