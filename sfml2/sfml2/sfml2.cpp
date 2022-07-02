#include <iostream>
#include "Game.h"

int main()
{
	// Initialize srand
	srand(static_cast<unsigned>(time(0)));

	// Initialize game
	Game game;


	// Game loop
	while(game.Running() && !game.GetEndGame())
	{
		// Update
		game.Update();

		// Render
		game.Render();	
	}

	// End of application
	return 0;
}

