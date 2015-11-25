#include <fstream>
#include <iostream>
#include <string>

/*
@ - hero
# - wall
. - floor

##########
#........#
#........#

*/

// using namespace std;

const char Hero = '@';
const char Wall = '#';
const char Floor = '.';

//const-correctness!

class Level {
	friend std::istream & operator >>(std::istream &is, Level &level);
public:
	int cols() const;
	int rows() const;

	void display();
	bool readFromFile(const std::string &fileName);

	bool onlyOneHero() const;
	bool moveHero(int a, int b);
private:
	int cols_;
	int rows_;
	char *data_;
};

int Level::cols() const
{
	return cols_;
}

int Level::rows() const
{
	return rows_;
}

void Level::display()
{
	for (int i = 0; i < rows_; ++i) {
		std::cout.write(data_ + i * cols_, cols_);
		std::cout << '\n';
	}
}

bool Level::readFromFile(const std::string &fileName)
{
	std::ifstream fileStream(fileName);
	if (!fileStream.is_open()) {
		std::cerr << "Error opening file " << fileName << '\n';
		return false;
	}

	fileStream >> (*this);

	return true;
}

std::istream & operator >>(std::istream &is, Level &level)
{
	is >> level.rows_ >> level.cols_;

	is >> std::noskipws;
	level.data_ = new char[level.rows_ * level.cols_];

	char c;
	while (std::isspace(is.peek()))
		is >> c;

	for (int i = 0; i < level.rows_; ++i) {
		is.read(level.data_ + i * level.cols_, level.cols_);
		while (std::isspace(is.peek()))
			is >> c;
	}

	return is;
}

bool Level::onlyOneHero() const
{
	int countHeroes = 0;

	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			if (data_[cols_ * i + j] == Hero)
				countHeroes++;
		}
	}

	return countHeroes == 1;
}

bool Level::moveHero(int a, int b)
{
	if (data_[a] != Hero || data_[b] != Floor) //for now assuming walking on floor only
		return false;

	data_[a] = Floor;
	data_[b] = Hero;

	return true;
}

class Player {
public:
	int pos() const;

	void setPos(int position);

private:
	int pos_;
};

int Player::pos() const
{
	return pos_;
}

void Player::setPos(int position)
{
	pos_ = position;
}

int main()
{
	Level level;

	level.readFromFile("lev.txt");

	Player player;
	player.setPos(level.cols() + 1);//for now @ has to be top left in lev.txt

	std::cout << "Simple game loop, wsad - moving, q - quit\n";
	level.display();

	while (true) {
		char c;
		std::cin >> c;
		int posOffset = 0;
		switch (c) {
			case 'q': //TODO autosave on quit
				return 0;
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
		}
		if (posOffset != 0) {
			if (level.moveHero(player.pos(), player.pos() + posOffset))
				player.setPos(player.pos() + posOffset);
			else
			;	//TODO not valid move
		}
		level.display();
	}

	return 0;
}
