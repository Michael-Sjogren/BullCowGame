/* This is the Console executable that makes use of The BullCow class
this acts as the view in a MVC pattern , and is responsible for all 
user int32eractions. for game logic see FBullCowGame class	
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax fit unreal engine convention
using FText = std::string;
using int32 = int;

// instantiate a new game, which we reuse across plays
FbullCowGame BCGame;

// func prototypes as outside a class
void gameintro();
void playGame();
void printBackGuess(FText guess);
void PrintGameSummay();
void isGuessValid();
bool playAgain();
bool playAgain();
FText toLowerCase(FText str);

// main
int main() {
	bool playing = true;
	do {
		gameintro();
		playGame();
		PrintGameSummay();
	    playing = playAgain();
	} while (playing);

	std ::cout << std ::endl;
	return 0;
}

// game intro
void gameintro() {
	
	std ::cout << std ::endl;
	std ::cout << "Welcome to Bulls and Cows!" << std ::endl;
	std ::cout << "Can you guess the " << BCGame.getHiddenWordLength();
	std ::cout << " letter isogram im thinking of?" << std ::endl;
}

// returns the guess
FText getGuess() {
	std ::cout << "\n" << "Try " << BCGame.getCurrentTry()<< "/" << BCGame.getMaxTries()<<" Enter a guess: ";
	FText guess = "";	
	getline(std :: cin , guess);
	return guess;
}
// prints back the guess into the console
void printBackGuess(FText guess) {
	std ::cout << "You guessed: " << guess << std ::endl;
}
// game loop
void playGame() {

	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= BCGame.getMaxTries()) {
		isGuessValid();
	}
}

// summarizes the game with win / loose message
void PrintGameSummay() {
	if (BCGame.isGameWon()) {
		// win
		std::cout << "	 ,/         \\" << std::endl;
		std::cout << "	((__,-\"\"\"-,__))" << std::endl;
		std::cout << "	`--)~   ~(--`" << std :: endl;
		std::cout << "	.-'(       )`-," << std::endl;
		std::cout << "	`~~`d\\   /b`~~`" << std::endl;
		std::cout << "	    |     |" << std::endl;
		std::cout << "	    (6___6)" << std::endl;
		std::cout << "	     `---`" << std::endl;
		std::cout << "\n ** CONGRATULATIONS YOU WON! ** " << std::endl;
		std::cout << std::endl;
	}
	else {
		// loose
		std::cout << "          .=     ,        =." << std::endl;
		std::cout << "  _  _   /'/    )\\,/,/(_   \\ \\" << std::endl;
		std::cout << "    //-.|  (  ,\\\\)\\//\\)\\/_  ) |" << std::endl;
		std::cout << "   //___\\   `\\\\\\/\\\\/\\/\\\\///'  /" << std::endl;
		std::cout << ",-\"~`-._ `\"- - '_   `\"\"\"`  _ \\`\'\"~-,_" << std::endl;
		std::cout << "\       `-.  '_`.      .'_` \\ ,-\"~`/" << std::endl;
		std::cout << "`.__.-'`/   (-\\        /-) |-.__,'" << std::endl;
		std::cout << "   ||   |    \\O)  /^\\ (O/  |" << std::endl;
		std::cout << "    \\\\  |         /   `\\    /" << std::endl;
		std::cout << "     \\\\  \\       /      `\\ /" << std::endl;
		std::cout << "       \\\\ `-.  /' .---.--.\\" << std::endl;
		std::cout << "       `\\\\/`~(, '()      ('"<< std::endl;
		std::cout << "       /(O) \\\\   _,.-.,_)" << std::endl;
		std::cout << "      //  \\\\ `\\'`      /" << std::endl;
		std::cout << "      / |  ||   `\"\"\"\"~\"`" << std::endl;
		std::cout << "    /'  |__||" << std::endl;
		std::cout << "         `o " << std::endl;
		std::cout << "\n ** YOU LOOSE , BETTER LUCK NEXT TIME! ** " << std::endl;
		std::cout << std::endl;
	}
}

// prints out error messages if input is invalid , else it submits the valid guess 
void isGuessValid() {
	FText guess;
	EWordStatus status;
	do
	{
		guess = getGuess();
		// gets the validity of the guess
		status = BCGame.checkValidGuess(guess);

		switch (status)
		{
		case EWordStatus::OK:
		{
			// submits guess and counts bulls and cows
			FBullCowCount BullCowCount = BCGame.SumitValidGuess(guess);
			std::cout << "Bulls = " << BullCowCount.bulls << " Cows = " << BullCowCount.cows << std::endl;
		}
		break;
		case EWordStatus::NOT_ISOGRAM:
			std::cout << "-- Not a isogram --" << std::endl;
			break;

		case EWordStatus::WRONG_LENGTH:
			std::cout << "-- Incorrect word length , Please enter a " << BCGame.getHiddenWordLength() << " letter isogram --" << std::endl;
			break;
		default:
			std::cout << "-- Unknown command --" << std::endl;
			break;
		}
		std::cout << std::endl;
	} while (status != EWordStatus::OK); 

}
// asks if user wants to play again (y/n)
bool playAgain() {
	FText response = "";
	std ::cout << "Do you want to play again?" << std ::endl;
	std ::cout << "(y/n): ";
    getline(std ::cin, response);
	std ::cout << std ::endl;
	std::cout << "---------------------------------------------" << std :: endl;
	// 
	if (BCGame.toLowerCase(response)[0] == 'y') {
		std ::cout << "Restarting Game" << std ::endl;
		BCGame.reset();
		std::cout << std::endl;
		return true;
	}
	else if (BCGame.toLowerCase(response)[0] == 'n') {
		std ::cout << "Game ended" << std ::endl;
		std::cout << std::endl;
		return false;
	}
	else {
		playAgain();
	}
}



