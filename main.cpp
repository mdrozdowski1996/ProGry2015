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

int main()
{
	Level level;

// 	level.readFromFile("lev.txt");

// 	std::ifstream input("lev.txt");
// 	input >> level;

	std::cin >> level;
	level.display();

//	std::cout << level.onlyOneHero() << "\n";

	return 0;
}
