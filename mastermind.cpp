// Mastermind game: still in progress.
//  written up by Sheyin - 3/27/15
// 	Asks user for 4 colors, compares colors + provides feedback for next guess.
//	Player wins after guessing all 4 colors in the correct positions.

#include "mastermind.hpp"
#include <iostream>
#include <ctime>        // time()
#include <cstdlib>      // seeding / random functions
#include <string>       // string functions
#include <cctype>       // character manipulation functions
#include <iomanip>      // formatting options (setw, etc.)

int main() {
	srand(time(0));
	Mastermind game;		// starting game, initializes values
	do {
		game.guessPegs();
	} while(game.inProgress());

	return 0;
}


// this handles input from the user and processes a guess by the user
void Mastermind::guessPegs() {
	std::string guess;
	std::cout << "Please select four colors to guess the code." << std::endl;

	for(int i = 0; i < 4; i++) {
		std::cout << "#" << i << ": ";
		std::cin >> guess;
		std::cin.ignore();

		guess = Mastermind::dropSymbols(guess);		// gets rid of any non-alpha characters
		guess = Mastermind::lowerCase(guess);		// makes every character lower case

		while (isInvalidColor(guess)) {
			std::cout << guess << " is an invalid option.  Please select again." << std::endl;
			std::cin >> guess;
			std::cin.ignore();
		}
        guessedCode[i] = guess;     // add to guess array after validation
	}

	// now that guessed array is populated - compare guess with solution
	resultsArray(guessedCode);		// populating results

	// print feedback to user - contents of results array
	std::cout << "Your guess:" << std::endl;
	printArray(guessedCode);

	std::cout << "Results:" << std::endl;
	printArray(results);

	return;
}

// resultsArray: populates the results array
// 	black: correct color, correct position
//	white: correct color, incorrect position
//	results array should be generated fresh each time it is called
void Mastermind::resultsArray(std::string guessArray[]) {
	// erase old results and make copy of solution to alter safely
	std::string copyAnswer[4];
	for (int i = 0; i < 4; i++) {
		copyAnswer[i] = answer[i];
		results[i] = "";
	}

	// loop to check for black pegs first (right color, right spot)
	for (int i = 0; i < 4; i++) {
		if (guessArray[i] == copyAnswer[i]) {
			results[i] = "black";
			copyAnswer[i] = "";
		}
	}

	// loop to check for white pegs (right color, wrong spot)
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (guessArray[i] == copyAnswer[j]) {
				results[i] = "white";
				copyAnswer[j] = "";
			}
		}
	}
}

// printArray: Only prints array to screen, no changes.
void Mastermind::printArray(std::string printMe[]) {
	for(int i = 0; i < 4; i++) {
		std::cout << std::setw(10) << printMe[i];
	}
	return;
}


// inProgress: checks if the guess matches / if the code has been cracked
bool Mastermind::inProgress() {
	for (int i = 0; i < 4; i++){
		if (results[i] != "black") {
			return false;
		}
	}

	std::cout << "Congratulations!  You have cracked the code!" << std::endl;
	return true;	// returns true only if each peg in results is black - solved
}

// dropSymbols: helper function.
std::string Mastermind::dropSymbols(std::string guess) {
	return dropSymbols(guess, guess.length());
}

// dropSymbols: removing non-alpha characters from the string.  I think.
std::string Mastermind::dropSymbols(std::string guess, int length) {
	// base case
	if (length == 1) {
		if (!isalpha(guess.at(0))) {
			std::cout << "Debug: Invalid character found.  Dropping character." << std::endl;
			return "";
		}
		else {
			return guess.at(0);
		}
	}

	else {
		if (!isalpha(guess[length])) {
			std::cout << "Debug: Invalid character found.  Dropping character." << std::endl;
			return dropSymbols(guess, length - 1);
		}
		else {
			return dropSymbols(guess, length - 1) + guess.at(length);
		}
	}
}


// lowerCase: helper function for lowerCase function of the same name.
std::string Mastermind::lowerCase(std::string color) {
	return lowerCase(color, color.length());
}

// lowerCase: Inspects each character of a string and recursively returns the lower case variant.
//		Also checks if it is a letter, but that should be a separate function.
std::string Mastermind::lowerCase(std::string color, int toCheck) {
	char lowerCaseChar;
	if (toCheck == 0) {
		return tolower(color.at(0));
	}
	else {
		lowerCaseChar = tolower(color[toCheck]);
		return lowerCase(color, toCheck - 1) + lowerCaseChar;
	}
}


// isInvalidColor: checks to see if user input is a valid color.
//	returns true if invalid, returns false if valid.
//	input should already be clear of non-alpha characters.
bool Mastermind::isInvalidColor(std::string color) {
	for(int i = 0; i < 6; i++) {
		if (color == validColors[i]) {
			return true;
		}
	}
	return false;
}

// Default constructor: when board initially created, this generates a code
// of 4 pegs and populates the array.
Mastermind::Mastermind() {
	turn = 0;
	std::string guessedCode[4] = {"", "", "", ""};
	std::string results[4] = {"", "", "", ""};

    /*
	// setting colors - maybe put back into header
	    validColors[0] = "red";
        validColors[1] = "orange";
        validColors[2] = "yellow";
        validColors[3] = "green";
        validColors[4] = "blue";
        validColors[5] = "purple";
        */

	for(int i = 0; i < 4; i++){
		int randNum = rand() % 6;		// range: 0 - 5
		answer[i] = intToColor(randNum);
	}
}

// pretty much only used w/ constructor.
// intToColor: changes int value (0 - 5) to a color string
std::string Mastermind::intToColor(int number) {
	switch(number) {
		case 1: {
			return validColors[0];
			break;
		}
		case 2: {
			return validColors[1];
			break;
		}
		case 3: {
			return validColors[2];
			break;
		}
		case 4: {
			return validColors[3];
			break;
		}
		case 5: {
			return validColors[4];
			break;
		}
		case 6: {
			return validColors[5];
			break;
		}
		default: {	// shouldn't be used, ever, but just in case...
			std::cout << "Debug: Invalid number choice!  Using a default color." << std::endl;
			return validColors[0];
			break;
		}
	}
}
