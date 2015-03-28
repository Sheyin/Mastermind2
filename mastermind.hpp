// Mastermind.hpp: Class definition file
// written up by Sheyin - 3/27/15

#include <iostream>

class Mastermind {
	private:
		std::string answer[4];
		int turn;
		std::string guessedCode[4];
		std::string results[4];

	public:
		static const std::string validColors[6];
		std::string intToColor(int number);
		void guessPegs();
		bool inProgress();
		bool isInvalidColor(std::string color);
		void printArray(std::string printMe[]);
		void resultsArray(std::string guessArray[]);
		std::string dropSymbols(std::string guess);
		std::string dropSymbols(std::string guess, int length);
		std::string lowerCase(std::string color);
		std::string lowerCase(std::string color, int toCheck);

};
