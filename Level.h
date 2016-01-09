#ifndef Level_h
#define Level_h
#include "Creature.h"
const char Hero = '@';
const char Wall = '#';
const char Floor = '.';
const char Door = '+';
class Level {
	friend class MapGenerator;
	friend std::istream & operator >>(std::istream &is, Level &level);
	friend std::ostream & operator <<(std::ostream &os, Level &level);

public:
	std::unordered_map<int, Creature *> creatures;

	int cols() const;
	int rows() const;
	int heroStartPos() const;
	void display() const;
	bool readFromFile(const std::string &fileName);

	char operator[](int index) const;

	std::vector<int> lineFromTo(int posA, int posB) const;
	bool canSee(int posA, int posB) const;
	int nextStepPos(int posA, int posB) const;

private:
	Level() = default;
	Level(char *data, int rows, int cols);

	int cols_;
	int rows_;
	int heroStartPos_;
	char *data_;
};

#endif
