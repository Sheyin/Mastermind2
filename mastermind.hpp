// Mastermind.hpp: Class definition file
// written up by Sheyin - 3/27/15

#include <iostream>

class Mastermind {
	private:
	    int turn;
		std::string answer[4];
		std::string guessedCode[4];
		std::string results[4];

	public:
	    Mastermind();       // default constructor
		std::string validColors[6];
		std::string intToColor(int number);
		void guessPegs();
		bool inProgress();
		bool isInvalidColor(std::string color);
		void printArray(std::string printMe[]);
		void showRules();
		void resultsArray(std::string guessArray[]);
		std::string makeLower(std::string original);
        //std::string validColors[6] = {"red", "orange", "yellow", "green", "blue", "purple"};
};
