#include "Level.h"
Level::Level(char *data, int rows, int cols)
	: cols_(cols), rows_(rows), data_(data)
{
}

char Level::operator[](int index) const
{
	if (creatures.find(index) != creatures.end())
		return Hero;
	else
		return data_[index];
}

int Level::cols() const
{
	return cols_;
}

int Level::rows() const
{
	return rows_;
}

int Level::heroStartPos() const
{
	return heroStartPos_;
}

void Level::display() const
{
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j)
			mvaddch(i, j, this->operator[](i * cols_ + j));
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

std::vector<int> Level::lineFromTo(int posA, int posB) const
{
	int aCol = posA % cols_;
	int aRow = posA / cols_;
	int bCol = posB % cols_;
	int bRow = posB / cols_;
	int deltaCol = bCol - aCol;
	int deltaRow = bRow - aRow;
	int deltaColSign = (deltaCol > 0) - (deltaCol < 0);
	int deltaRowSign = (deltaRow > 0) - (deltaRow < 0);
	std::vector<int> vec;

	if (deltaCol == 0)
		for (int row = aRow + deltaRowSign; row != bRow; row += deltaRowSign)
			vec.push_back((row * cols_) + aCol);
	else if (abs(deltaCol) >= abs(deltaRow))
		for (int col = deltaColSign; col + aCol != bCol; col += deltaColSign) {
			int calcRow = (2 * col * deltaRow + (deltaRowSign * deltaCol)) / (2 * deltaCol) + aRow;
			vec.push_back(calcRow * cols_ + aCol + col);
		}
	else
		for (int row = deltaRowSign; row + aRow != bRow; row += deltaRowSign) {
			int calcCol = (2 * row * deltaCol + (deltaColSign * deltaRow)) / (2 * deltaRow) + aCol;
			vec.push_back((row + aRow) * cols_ + calcCol);
		}

	return vec;
}

bool Level::canSee(int posA, int posB) const
{
	std::vector<int> vec = lineFromTo(posA, posB);
	for (int i : vec)
		if (data_[i] != Floor)
			return false;
	return true;
}

int Level::nextStepPos(int posA, int posB) const
{
	std::vector<int> vec = lineFromTo(posA, posB);
	if (vec.empty())
		if (posA == posB)
			return -1;
		else
			return posB;
	else
		return vec.front();
}

std::istream & operator >>(std::istream &is, Level &level)
{
	is >> level.rows_ >> level.cols_ >> level.heroStartPos_;

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

std::ostream & operator <<(std::ostream &os, Level &level)
{
	os << level.rows_ << " " << level.cols_ << " " << level.heroStartPos_ << '\n';
	for (int i = 0; i < level.rows_ ; ++i) {
		os.write(level.data_ + i * level.cols_, level.cols_);
		os << '\n';
	}

	return os;
}
