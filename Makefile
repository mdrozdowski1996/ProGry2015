CXXFLAGS = -std=c++11
GRA: Main.o Game.o MapGenerator.o Level.o Creature.o
	g++ $(CXXFLAGS) Main.o Game.o MapGenerator.o Level.o Creature.o -o GRA -lncurses
Main.o: Main.cpp Player.h MapGenerator.h
	g++ $(CXXFLAGS) Main.cpp -c -o Main.o
Creature.o: Creature.h Creature.cpp
	g++ $(CXXFLAGS) Creature.cpp -c -o Creature.o
Game.o: Game.h Game.cpp
	g++ $(CXXFLAGS) Game.cpp -c -o Game.o
Level.o: Level.h Level.cpp
	g++ $(CXXFLAGS) Level.cpp -c -o Level.o
MapGenerator.o: MapGenerator.h MapGenerator.cpp
	g++ $(CXXFLAGS) MapGenerator.cpp -c -o MapGenerator.o
clean:
	rm -f *.o GRA
