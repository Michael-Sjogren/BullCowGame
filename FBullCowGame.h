#pragma once
#include <string>
#include <map>

// to make syntax fit unreal engine convention
#define TMap std :: map
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};


enum class EWordStatus
{
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH
};

class FbullCowGame 
{
public:
	FbullCowGame();
	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	void reset();
	
	EWordStatus checkValidGuess(FString guess);
	FBullCowCount SumitValidGuess(FString);
	FString toLowerCase(FString str) const;

 

private:
	// see constructor for init
	int32 currTry;
	int32 maxTries;
	FString hiddenWord;
	bool bGameIsWon;
	bool checkIsogram(FString s);
};