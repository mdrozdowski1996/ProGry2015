#include "Player.h"
#include "MapGenerator.h"

int main()
{
	initscr();
	noecho();
	MapGenerator gen;
	Level level = gen.createLevel();

	Game game(level);

	std::cout << "Simple game loop, wsad - moving, q - quit\n";
	game.displayLevel();

	const Player &player = game.player();

	while (true) {
		char c;
		c = getch();
		int posOffset = 0;
		switch (c) {
			case 'q': {
				std::ofstream save("save.txt");
				save << level;
				endwin();
				return 0;
			}
			case 'w':
				posOffset = -level.cols();
				break;
			case 's':
				posOffset = +level.cols();
				break;
			case 'a':
				posOffset = -1;
				break;
			case 'd':
				posOffset = +1;
				break;
			case 't': //canSee test
				move(level.rows(), 0);
				refresh();
				if (level.canSee(level.heroStartPos(), player.pos()))
					printf("widać ze startu    \n");
				else
					printf("nie widać ze startu\n");
				break;
		}
		if (posOffset != 0) {
			if (!game.moveCreature(player, posOffset))
			;	//TODO not valid move
		}
		game.displayLevel();
	}
	endwin();
	return 0;
}
