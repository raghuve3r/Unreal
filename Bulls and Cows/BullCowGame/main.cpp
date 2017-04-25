/*

Console executable for BullCow class
Main class responsible for user interface
See FBullCowGame class for details

*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

//entry point for program
int main() 
{
	bool playAgain = false;
	
	do {
		PrintIntro();
		PlayGame();
		playAgain = AskPlayAgain();
	} while (playAgain);
	
	return 0;
}


void PrintIntro() 
{
	//game intro
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	//debugging purpose
	//std::cout << BCGame.GetHidden();
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//user input for guesses and loop for number of turns
	
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		//repeat guess
		FText Guess = GetValidGuess(); //TODO make loop checking
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//Submit valid guess
		//Print number of Bulls and Cows
		std::cout << "Bulls: " << BullCowCount.Bulls << ". Cows: " << BullCowCount.Cows <<std::endl << std::endl;
		
	}
	//printing the game summary
	PrintGameSummary();
	return;

}


FText GetValidGuess() 
{
	EWordStatus Status = EWordStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 MaxTries = BCGame.GetMaxTries();
		std::cout << "Try " << CurrentTry << " of "<< MaxTries << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter " << BCGame.GetHiddenWordLength() << " letter word! \n" << std::endl;
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter an Isogram \n" << std::endl;
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter a word with lowercase \n" << std::endl;
			break;
		default:
			break;
		}
		//std::cout << std::endl;
	} while (Status != EWordStatus::OK); //keep looping until there are no error
	return Guess;
}

bool AskPlayAgain() 
{
	while (true)
	{
		std::cout << "Do you want to play again? (y/n)" << std::endl << std::endl;
		FText Response = "";
		getline(std::cin, Response);
		if (Response == "Y" || Response == "y") {
			return true;
		}
		else if (Response == "N" || Response == "n" ) {
			return false;
		}
		else {
			std::cout << "Enter Y/N!" << std::endl << std::endl;
		}
	}
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Well done - You've won the game!" << std::endl;
	}
	else {
		std::cout << "Sorry! Better luck next time." << std::endl;
	}
}