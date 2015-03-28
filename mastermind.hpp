class mastermind {
	private:
		string pegs[];
		
	public:
		std::string intToColor(int number);
		void guessPegs();
		bool inProgress();
		bool isInvalidColor(std::string color);
		
};
