#pragma once
#include<string>

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};


enum EWordStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame(); //constructor
	void Reset();

	//debugging purpose
	//FString GetHidden();
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(FString) const;

	//count number of bulls and cows and increment tries
	FBullCowCount SubmitValidGuess(FString);
private:
	int32 MyMaxTries;
	int32 MyCurrentTries;
	bool bGamewon;
	FString MyHiddenWord;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};