#include "MapGenerator.h"

Level MapGenerator:: createLevel(int seed)
	{
		if (seed == -1)
			srand(time(nullptr));
		else
			srand(seed);

		rows_ = 40;
		cols_ = 80;
		canvas_ = new char[rows_ * cols_];

		for(int i = 0; i < rows_; i++)
			for (int j = 0; j < cols_; j++)
				canvas_[i * cols_ + j] = Wall;

		int prevCol, prevRow, currRow, currCol;

		for (int i = 0; i < 10; i++) {
			prevRow = currRow;
			prevCol = currCol;

			currRow = rand() % (rows_ / 2 - 1);
			currRow = currRow * 2 + 1;
			currCol = rand() % (cols_ / 2 - 1);
			currCol = currRow * 2 + 1;
			int height = rand() % 7 + 3;
			int width = rand() % 7 + 3;
			createRectangularRoom(currRow, currCol, width, height);

			// Brutally add corridors

			int dir;
			if (i > 0) {
				dir = prevRow > currRow ? -1 : 1;

				// Horizontal
				while (prevRow != currRow) {
					prevRow += dir;
					int tmp = prevRow * cols_ + prevCol;
					if (canvas_[tmp] == Wall) {
						if (canvas_[tmp - 1] != Floor && canvas_[tmp + 1] != Floor)
							canvas_[tmp] = Corridor;
						else
							canvas_[tmp] = Floor;
					}
				}

				// Vertical
				dir = prevCol > currCol ? -1 : 1;
				while (prevCol != currCol) {
					prevCol += dir;
					int tmp = prevRow * cols_ + prevCol;
					if (canvas_[tmp] == Wall) {
						if (canvas_[tmp - cols_] != Floor && canvas_[tmp + cols_] != Floor)
							canvas_[tmp] = Corridor;
						else
							canvas_[tmp] = Floor;
					}
				}
			}
		}

		createDoors();

		clearCorridors();

		Level result(canvas_, rows_, cols_);
		result.heroStartPos_ = prevRow * cols_ + prevCol;
		return result;
	}
	void MapGenerator::createRectangularRoom(int posCol, int posRow, int width, int height)
	{
		width  = std::min(width, cols_ - posRow - 1);
		height = std::min(height, rows_ - posCol - 1);
		posCol = std::max(posCol, 1);
		posRow = std::max(posRow, 1);
		for (int i = posCol; i < posCol + height; ++i)
			for (int j = posRow; j < posRow + width; ++j)
				canvas_[i * cols_ + j] = Floor;
	}

	void MapGenerator::createDoors()
	{
		std::vector<int> doors;
		std::vector<int> clear;
		for (int i = 0; i < cols_ * rows_; ++i) {
			int adjacent = 0;
			for (auto direction : ortogonalDirections()) {
				if (i + direction >= 0 && i + direction <= cols_ * rows_ && canvas_[i + direction] == Corridor)
					adjacent++;
			}

			if (canvas_[i] == Corridor) {
				if (adjacent == 1)
					doors.push_back(i);
				else if (adjacent == 0)
					clear.push_back(i);
			}
		}

		for (auto i : clear) {
			// Adjacent rooms with really short corridor
			if (canvas_[i + 1] == canvas_[i - 1])
				doors.push_back(i);
			else
				canvas_[i] = Floor;
		}

		for (auto i : doors) {
			// Additional check for corridors crossing in a room
			int adjacent = 0;

			for (auto direction : ortogonalDirections()) {
				if (canvas_[direction + i] == Floor || canvas_[direction + i] == Corridor)
					adjacent++;
			}

			if (adjacent < 3)
				canvas_[i] = Door;
		}
	}

	void MapGenerator:: clearCorridors()
	{
		for (int i = 0; i < cols_* rows_; ++i)
			if (canvas_[i] == Corridor)
				canvas_[i] = Floor;
	}

	inline std::array<int, 8> MapGenerator::directions()
	{
		return Game::directions(cols_);
	}

	inline std::array<int, 4> MapGenerator::ortogonalDirections()
	{
		return Game::ortogonalDirections(cols_);
	}
	
