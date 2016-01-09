#include "Game.h"
Game::Game(Level level) : level_(level)
{
	player_.setPos(level.heroStartPos());
	level_.creatures[player_.pos()] = &player_;
}

inline std::array<int, 8> Game::directions()
{
	return directions(level_.cols());
}

inline std::array<int, 4> Game::ortogonalDirections()
{
	return ortogonalDirections(level_.cols());
}

void Game::setLevel(Level &&level)
{
	level_ = level;
}

void Game::displayLevel() const
{
	level_.display();
}

const Player & Game::player() const
{
	return player_;
}

bool Game::moveCreature(const Creature &creature, int offset)
{
	// For now movement allowance equals 1
	if (std::find(directions().begin(), directions().end(), offset) == directions().end())
		return false;

	int from = creature.pos();
	int to = from + offset;

	if (level_.creatures.find(from) == level_.creatures.end())
		return false;

	if (level_[to] == Wall)
		return false;

	level_.creatures[to] = level_.creatures[from];
	level_.creatures[to]->setPos(to);
	level_.creatures.erase(level_.creatures.find(from));
	return true;
}
