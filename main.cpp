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

	fileStream >> rows_ >> cols_;

	fileStream >> std::noskipws;
	data_ = new char[rows_ * cols_];

	char c;
	while (std::isspace(fileStream.peek()))
		fileStream >> c;

	for (int i = 0; i < rows_; ++i) {
		fileStream.read(data_ + i * cols_, cols_);
		while (std::isspace(fileStream.peek()))
			fileStream >> c;
	}

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

int main()
{
	Level level;

// 	level.readFromFile("lev.txt");

// 	std::ifstream input("lev.txt");
// 	input >> level;

	std::cin >> level;
	level.display();


	return 0;
}
