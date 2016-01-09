#ifndef Creature_h
#define Creature_h
#include <algorithm>
#include <array>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <unordered_map>
#include <vector>
class Creature {
public:
	int pos() const;

	void setPos(int position);

private:
	int pos_;
};
#endif
