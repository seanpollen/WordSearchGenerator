#include "jumble_17smp3.h"
using namespace std;

JumblePuzzle::JumblePuzzle(const string& hiddenWord, const string& difficulty)
{
	string temp = hiddenWord;
	//check if the word length is valid
	length = hiddenWord.length();
	if (length < 3)
		throw BadJumbleException("Your word must be between 3 and 10 letters, it's too short");
	if (length > 10)
		throw BadJumbleException("Your word must be between 3 and 10 letters, it's too long");

	//the size of the matrix depends on the original word length and difficulty
	if (difficulty == "easy")
		length = length * 2;
	else if (difficulty == "medium")
		length = length * 3;
	else if (difficulty == "hard")
		length = length * 4;
	else
		throw BadJumbleException("Please enter either easy, medium, or hard");

	//initialize the matrix to store all characters
	matrix = new char* [length];

	for (int i = 0; i < length; i++) 
		matrix[i] = new char[length];

	const char* letters = "abcdefghujklmnopqrstuvwxyz"; //initialize a bank of all letters used to fill jumble puzzle

	srand(time(NULL)); //initialize the random function with a seed from the internal clock

	//fill the array with random letters
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			matrix[i][j] = (char)letters[rand() % 25];

	//generate a starting position (row and column)
	row = rand() % length; 
	column = rand() % length;

	matrix[row][column] = hiddenWord.at(0); //place the first letter of the word at the designated position
	const char* orientation = "nesw"; //a bank of all directions (north, east, south, west)
	bool placed = false; //is the letter placed? (Y/N)

	while (!placed) {
		direction = orientation[rand() % 4]; //generate which direction the word is to be placed (index between 0-3)

		//north case, the algorithm used is the one given on the assignment 3 page
		if (direction == 'n') {
			for (int i = 1; i < hiddenWord.length(); i++)
			{
				if ((row - i) < 0)
					break;
				else if (i == (hiddenWord.length() - 1)) { // last letter
					matrix[row - i][column] = hiddenWord.at(i);
					placed = 1;
				}
				else
					matrix[row - i][column] = hiddenWord.at(i);
			}
		}
		
		//east case
		else if (direction == 'e') {
			for (int i = 1; i < hiddenWord.length(); i++) 
			{
				if ((column + hiddenWord.length() > this->getSize() - 1))
					break;
				else if (i == (hiddenWord.length() - 1)) {
					matrix[row][column + i] = hiddenWord.at(i);
					placed = 1;
				}
				else
					matrix[row][column + i] = hiddenWord.at(i);
			}
		}

		//south case
		else if (direction == 's') {
			for (int i = 1; i < hiddenWord.length(); i++) {
				if ((row + hiddenWord.length()) > this->getSize() - 1)
					break;
				else if (i == (hiddenWord.length() - 1)) {
					matrix[row + i][column] = hiddenWord.at(i);
					placed = 1;
				}
				else
					matrix[row + i][column] = hiddenWord.at(i);
			}
		}

		//west case
		else if (direction == 'w') {
			for (int i = 1; i < hiddenWord.length(); i++) {
				if ((column - i) < 0)
					break;
				else if (i == (hiddenWord.length() - 1)) {
					matrix[row][column - i] = hiddenWord.at(i);
					placed = 1;
				}
				else
					matrix[row][column - i] = hiddenWord.at(i);
			}
		}

		//unlikely this will ever be used but hey that's the way life goes sometimes
		else
			throw BadJumbleException("Error to initialize jumble puzzle");
		
	}
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& temp)
{
	//copy constructor function
	length = temp.getSize();
	row = temp.getRowPos();
	column = temp.getColPos();
	direction = temp.getDirection();
	matrix = new char* [length];

	for (int i = 0; i < length; i++)
		matrix[i] = new char[length];

	charArrayPtr* tempMatrix = temp.getJumble();

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++)
			matrix[i][j] = tempMatrix[i][j];
	}
}

JumblePuzzle::~JumblePuzzle()
{
	for (int i = 0; i < length; i++)
		delete matrix[i];
	delete[] matrix;
}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& temp)
{
	if (this != &temp)
	{
		row = temp.getRowPos();
		column = temp.getColPos();
		direction = temp.getDirection();
		length = temp.getSize();

		for (int i = 0; i < length; i++)
			delete[] matrix[i];
		delete[] matrix;
		matrix = new char* [length];
		for (int i = 0; i < length; i++)
			matrix[i] = new char[length];

		charArrayPtr* tempJumble = temp.getJumble();

		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++)
				matrix[i][j] = tempJumble[i][j];
		}
	}
	return *this;
}

charArrayPtr* JumblePuzzle::getJumble() const
{
	charArrayPtr* newMatrix = new char* [length];
	//make a enw matrix, copy everything in
	for (int i = 0; i < length; i++)
		newMatrix[i] = new char[length];

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++)
			newMatrix[i][j] = matrix[i][j];
	}
	return newMatrix;
}

int JumblePuzzle::getSize() const
{
	return length;
}

int JumblePuzzle::getRowPos() const
{
	return row;
}

int JumblePuzzle::getColPos() const
{
	return column;
}

char JumblePuzzle::getDirection() const
{
	return direction;
}

BadJumbleException::BadJumbleException(const string& e) : message(e)
{
}

string BadJumbleException::what() const
{
	return message;
}