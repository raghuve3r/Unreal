#include "FBullCowGame.h"
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#define TMap std::map

using int32 = int;

std::vector<std::string> words;

FBullCowGame::FBullCowGame() 
{
	
	std::ifstream file("isogramList.txt");
	std::string line;
	while (std::getline(file, line)) {
		words.push_back(line);
	}
	Reset();
}


void FBullCowGame::Reset()
{
	MyCurrentTries = 1;
	constexpr int32 NumberOfLines = 42812;
	const FString HIDDEN_WORD = words[100];
	MyHiddenWord = HIDDEN_WORD;
	bGamewon = false;
	return;
}


/*FString FBullCowGame::GetHidden()
{
	return MyHiddenWord; //debugging
}
*/

int32 FBullCowGame::GetMaxTries() const{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,6},{5,8},{6,10},{7,12} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const{return MyCurrentTries;}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGamewon;
}


//receives a guess, increment and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTries++;

	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length();

	//looping through hidden
	for (int32 i = 0; i < HiddenWordLength; i++) {
		//loop through guess
		for (int32 j = 0; j < HiddenWordLength; j++) {
			//compare the guessed word with hidden word
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) { //if they are at same place
					BullCowCount.Bulls++; //increment bulls
				}
				else {
					BullCowCount.Cows++; //increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength()) {
		bGamewon = true;
	}
	else{
		bGamewon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString word) const
{
	if (word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto Letter : word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { 
			return false; 
		}
		else { 
			LetterSeen[Letter] = true; 
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString word) const
{
	for (auto Letter : word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)){
		return EWordStatus::Not_Isogram;
	}
	else if (Guess.length() != MyHiddenWord.length()) {
		return EWordStatus::Wrong_Length;
	}
	else if (!IsLowercase(Guess)) {
		return EWordStatus::Not_Lowercase;
	}
	else {
		return EWordStatus::OK;
	}
}
