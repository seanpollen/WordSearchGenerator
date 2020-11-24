#pragma once
#include <string>
#include <time.h>
#include <iostream>
#include <ctime>

using namespace std;
typedef char* charArrayPtr;

class JumblePuzzle {
public:
	JumblePuzzle(const string& hiddenWord, const string& difficulty); //constructor
	JumblePuzzle(const JumblePuzzle& temp); //copy constructor
	~JumblePuzzle(); //destructor
	JumblePuzzle& operator=(const JumblePuzzle& temp); //operator overloaded
	charArrayPtr* getJumble() const;
	int getSize() const; //return side length of matrix
	int getRowPos() const; //return row
	int getColPos() const; //return column
	char getDirection() const; //return direction

private:
	int row; //store the row of the first letter in the hidden word
	int column; //store the column of the first letter in the hidden word
	int length; //initially the length of hidden word, later used as the length of the matrix
	char direction; //n, e, s, or w to store orientation of hidden word
	charArrayPtr* matrix;
};

class BadJumbleException { //standard exceoption class as used in other assignments
public:
	BadJumbleException(const string&);
	string what() const;
private:
	string message;
};