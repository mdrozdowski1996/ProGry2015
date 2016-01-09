#ifndef Game_h
#define Game_h
#include "Level.h"
#include "Player.h"
class Game {
public:
	static inline std::array<int, 8> directions(int rowsize)
	{
		return std::array<int, 8> {{-1, 1, rowsize, -rowsize, 1 - rowsize, 1 + rowsize, -1 - rowsize, -1 + rowsize}};
	}

	static inline std::array<int, 4> ortogonalDirections(int rowsize)
	{
		return std::array<int, 4> {{-1, 1, rowsize, -rowsize}};
	}

	Game(Level);

	void setLevel(Level &&);
	const Player & player() const;
	void displayLevel() const;

	bool moveCreature(const Creature &creature, int offset);

private:
	Player player_;
	Level level_;
	inline std::array<int, 8> directions();
	inline std::array<int, 4> ortogonalDirections();
};
#endif
