#ifndef MapGenerator_h
#define MapGenerator_h
#include "Level.h"
#include "Game.h"
class MapGenerator{
public:
Level createLevel (int seed = -1);

private:
static const char Corridor = 'C' ;
char *canvas_;
int rows_;
int cols_;
void createRectangularRoom(int posCol, int posRow, int width, int height);
void createDoors();
void clearCorridors();
inline std::array<int, 8> directions();
inline std::array<int, 4> ortogonalDirections();
};

#endif
