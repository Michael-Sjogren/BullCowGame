/* This is the BullCow class
this acts as the model in a MVC pattern , and is responsible for all
game logic.
*/

#pragma once
#include "FBullCowGame.h"
#include <algorithm>
#include <map>

// to make syntax fit unreal engine convention
#define TMap std :: map
using FString = std::string;
using int32 = int;

// Constructor
FbullCowGame::FbullCowGame()
{
	reset();
}
// returns the number of max tries depending on the length or the hidden word
int32 FbullCowGame::getMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries = { {4,6},{5,10},{6,16},{7,20} };
	return WordLengthToMaxTries[getHiddenWordLength()];
}
int32 FbullCowGame::getCurrentTry() const {return currTry;}
int32 FbullCowGame::getHiddenWordLength() const{return	hiddenWord.length();}
bool FbullCowGame::isGameWon() const{return bGameIsWon;}

// checks if the guess is valid. If the guess is not valid it will handle that error
EWordStatus FbullCowGame::checkValidGuess(FString guess)
{	
	if (guess.length() != getHiddenWordLength()) {
		return EWordStatus::WRONG_LENGTH;
	}	
	else if (!checkIsogram(guess)) {
		return EWordStatus::NOT_ISOGRAM;
	}
	else
	{
		return EWordStatus::OK;
	}
}

// recives a valid guess , increments try #
FBullCowCount FbullCowGame::SumitValidGuess(FString guess)
{
	bGameIsWon = false;
	FString g = toLowerCase(guess);
	FBullCowCount BullCowCount;
	int32 hiddenWordLength = getHiddenWordLength();
		
		currTry++;
		// loop through all letters in the hidden word
		for (int32 HWChar = 0; HWChar < hiddenWordLength; HWChar++) {
			// compare letters against the guess
			for (int32 GChar = 0; GChar < hiddenWordLength; GChar++) {
				if (g[GChar] == hiddenWord[HWChar])
				{
					
					if (HWChar == GChar)
					{
						BullCowCount.bulls++;
					}
					else
					{
						BullCowCount.cows++;
					}
				}
			}

			if (BullCowCount.bulls == hiddenWordLength) {
				bGameIsWon = true;
			}
			else {
				bGameIsWon = false;
			}
	}	
	return BullCowCount;
}

// resets score and tries  
void FbullCowGame::reset()
{	
	bGameIsWon = false;
	// TODO randomize the choosing of an isogram of a list of isograms
	const FString HIDDEN_WORD = "south"; // this MUST be an isogram(word with non-repeating characters) , else game will not function!!
	hiddenWord = HIDDEN_WORD;
	currTry = 1;
}

// check if it is an isogram
bool FbullCowGame::checkIsogram(FString s) {
	
	TMap <char, bool>LetterSeen;
	for (auto letter : s) {
		
		if (LetterSeen[letter]) {
			return false;
		}
		else
		{
			LetterSeen[letter] = true;
		}
	}
	// TODO if an isogram is valid but isnt the right answer write it to a text file
	return true;
}

// turns a string into lower case
FString FbullCowGame::toLowerCase(FString str) const {
	FString s = "";

	for (int32 i = 0; i < str.size(); i++)
	{
		s += tolower(str[i]);
	}
	return s;
}
