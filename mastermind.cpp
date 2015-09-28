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
#include <cstring>      // c_string funtions

bool chooseMode();

int main() {
	srand(time(0));
	std::cout << "Welcome to Mastermind!" << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
	Mastermind game = Mastermind(chooseMode());		// starting game, initializes values
	game.showRules();
	std::cout << "To show these rules again, enter 'rules' at any time." << std::endl;
	do {
		game.guessPegs();
	} while(game.inProgress());

	return 0;
}


// Default constructor: when board initially created, this generates a code
// of 4 pegs and populates the array.
Mastermind::Mastermind() {
	turn = 0;
	std::string guessedCode[4] = {"", "", "", ""};
	std::string results[4] = {"", "", "", ""};
	duplicateColors = true;

	// setting colors - maybe put back into header
	    validColors[0] = "red";
        validColors[1] = "orange";
        validColors[2] = "yellow";
        validColors[3] = "green";
        validColors[4] = "blue";
        validColors[5] = "purple";

	for(int i = 0; i < 4; i++){
		int randNum = rand() % 6;		// range: 0 - 5
		answer[i] = intToColor(randNum);
	}
}


// Alternate constructor: Like the default array but this prevents
//      duplicate colors from being used in the result.
Mastermind::Mastermind(bool allowDuplicates) {
	turn = 0;
	std::string guessedCode[4] = {"", "", "", ""};
	std::string results[4] = {"", "", "", ""};
	duplicateColors = allowDuplicates;

	// setting colors - maybe put back into header
	    validColors[0] = "red";
        validColors[1] = "orange";
        validColors[2] = "yellow";
        validColors[3] = "green";
        validColors[4] = "blue";
        validColors[5] = "purple";

	for(int i = 0; i < 4; i++){
		int randNum = rand() % 6;		// range: 0 - 5

		// if duplicates disallowed, check and reroll for valid color
		if (!duplicateColors && i > 0) {
		    //if duplicate found:
            while (checkDuplicate(intToColor(randNum))) {
                randNum++;
                    if (randNum > 6) {
                        randNum = 0;
                    }
            }
            answer[i] = intToColor(randNum);
        }

        //if not a duplicate:
        else {
            answer[i] = intToColor(randNum);
        }
	}
}

// guessPegs: this handles input from the user and processes a guess by the user
//  Populates guessedCode[] with user input.
void Mastermind::guessPegs() {
    turn++;
	std::string guess;
	std::cout << "\n--------------------------------------------------" << std::endl;
	std::cout << "Turn #" << turn << ": ";
	std::cout << "\n--------------------------------------------------" << std::endl;
	std::cout << "Please select four colors." << std::endl;

	for(int i = 0; i < 4; i++) {
		std::cout << "#" << i+1 << ": ";
		std::cin >> guess;
		std::cin.ignore();

		// show rules upon request
		if (guess == "rules") {

            showRules();

            // to continue semi-seamlessly:
            std::cout << "#" << i+1 << ": ";
            std::cin >> guess;
            std::cin.ignore();
		}

		// debug - cheat code
		if (guess == "justtellmealready") {
            std::cout << "You cheater.  Here: " << std::endl;
            printArray(answer);
            std::cout << std::endl;

            // to continue semi-seamlessly:
            std::cout << "#" << i+1 << ": ";
            std::cin >> guess;
            std::cin.ignore();
		}

        while (isInvalidColor(guess)) {
            std::cout << guess << " is an invalid option.  Please select again." << std::endl;
            std::cin >> guess;
            std::cin.ignore();
        }
        guessedCode[i] = makeLower(guess);     // add to guess array after validation
	}

    std::cout << std::endl;

	// now that guessed array is populated - compare guess with solution
	resultsArray(guessedCode);		// populating results

	// print feedback to user - contents of results array
	std::cout << "Your guess:" << std::endl;
	printArray(guessedCode);

	std::cout << "\nResults:" << std::endl;
	printArray(results);

	std::cout << std::endl;

	return;
}

// resultsArray: populates the results array
// 	black: correct color, correct position
//	white: correct color, incorrect position
//	results array should be generated fresh each time it is called
//  result pegs should not correlate to position in array
void Mastermind::resultsArray(std::string guessArray[]) {

	std::string copyAnswer[4];
	std::string copyGuess[4];
	int resultsNum = 0;  // this iterates results array - should not correspond to position in solution

    // erase old results and make copy of solution to alter safely
    for (int i = 0; i < 4; i++) {
        copyAnswer[i] = answer[i];
        copyGuess[i] = guessArray[i];
        results[i] = "";
    }

    // loop to check for black pegs first (right color, right spot)
    for (int i = 0; i < 4; i++) {
        if (copyGuess[i] == copyAnswer[i]) {
            results[resultsNum] = "black";
            resultsNum++;
            copyAnswer[i] = " ";    // these are to prevent counting
            copyGuess[i] = "-";    // colors twice in black and white
        }
    }

    // loop to check for white pegs (right color, wrong spot)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (copyGuess[i] == copyAnswer[j]) {
                results[resultsNum] = "white";
                resultsNum++;
                copyAnswer[j] = " ";    // these are to prevent counting
                copyGuess[i] = "-";    // colors twice in black and white
            }
        }
	}
}

// printArray: Only prints array to screen, no changes.
void Mastermind::printArray(std::string printMe[]) {
	for(int i = 0; i < 4; i++) {
		std::cout << std::setw(10) << printMe[i];
	}
	std::cout << std::endl;
	return;
}


// inProgress: checks if the guess matches / if the code has been cracked
bool Mastermind::inProgress() {
	for (int i = 0; i < 4; i++){
		if (results[i] != "black") {
			return true;
		}
	}

	std::cout << "Congratulations!  You have cracked the code in " << turn << " turns!" << std::endl;
	return false;	// returns true only if each peg in results is black - solved
}


// checkDuplicate: checks if a color already exists in solution.
bool Mastermind::checkDuplicate(std::string color) {
    for(int i = 0; i < 4; i++) {
        if (answer[i] == color) {
            return true;
        }
    }

    return false;
}


// isInvalidColor: checks to see if user input is a valid color.
//	returns true if invalid, returns false if valid.
//	input should already be clear of non-alpha characters.
bool Mastermind::isInvalidColor(std::string color) {
    // Check for invalid characters
    for(int i = 0; i < color.length(); i++) {
        if (!isalpha(color.at(i))) {
            return true;
        }
    }

    // Make lower case
    color = makeLower(color);


    // Check if it is an acceptable color
	for(int i = 0; i < 6; i++) {
		if (color == validColors[i]) {

			return false;
		}
    }
	return true;
}


// makeLower: Takes a string and returns it in all lower case.
std::string Mastermind::makeLower(std::string original) {
    char changed[original.length() + 1];
    strcpy(changed,original.c_str());

    for(int i = 0; i < original.length(); i++) {
            changed[i] = tolower(changed[i]);
        }
        original = changed;
    return original;
}

// showRules: Prints the rules of the game to the screen.
void Mastermind::showRules() {
    std::cout << std::endl;
    std::cout << "The goal is to guess the 4-color code." << std::endl;
    std::cout << "Enter the name of a color (red, orange, yellow, green, blue, purple)." << std::endl;
    std::cout << "Duplicate colors are permissible. " << std::endl;
    std::cout << "The program will give you feedback based on your guess." << std::endl;
    std::cout << "Black indicates that you have the right color and right position." << std::endl;
    std::cout << "White indicates that you have the right color, but it is in the wrong position." << std::endl;
    std::cout << "The order of the results you see does not correlate to the order listed." << std::endl;
    std::cout << "So if you see a black peg, it does not mean your first color is correct!" << std::endl;
    std::cout << std::endl;
    return;
}


// pretty much only used w/ constructor.
// intToColor: changes int value (0 - 5) to a color string
std::string Mastermind::intToColor(int number) {
	switch(number) {
		case 0: {
			return validColors[0];
			break;
		}
		case 1: {
			return validColors[1];
			break;
		}
		case 2: {
			return validColors[2];
			break;
		}
		case 3: {
			return validColors[3];
			break;
		}
		case 4: {
			return validColors[4];
			break;
		}
		case 5: {
			return validColors[5];
			break;
		}
		default: {	// shouldn't be used, ever, but just in case...
			return validColors[0];
			break;
		}
	}
}

// chooseMode: Allows switching between duplicates / no duplicates allowed.
bool chooseMode() {
	char allowDuplicate;
	std::cout << "Do you want to allow duplicate colors in this game?" << std::endl;
	do {
		std::cout << "Select (Y)es or (N)o: ";
		std::cin >> allowDuplicate;
	} while (allowDuplicate != 'Y' && allowDuplicate != 'y' && allowDuplicate != 'N' && allowDuplicate != 'n');

	if (allowDuplicate == 'Y' || allowDuplicate == 'y') {
		std::cout << "\nAllowing duplicate colors." << std::endl;
		return true;
	}

	else {
		std::cout << "\nDisallowing duplicate colors." << std::endl;
		return false;
	}
}
