/*********************************************************************
** Program Filename: gol
** Author: Travis Nykaza
** Date: January 17, 2016
** Description: This program simulates the Game of Life. Users choose
** both an initial clump of cells and its positon
** Input: User choice for both shape and position.
** Output: Animation of cells are they grow and die according to
** the rules in the Game of Life.
*********************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
//#include <windows.h> 
//#include <conio.h>


int inputValidation();
// [Rows_X][Columns_Y]

int main()
{
	// Initializes 2d "visible" array
	bool board[50][80];
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			board[i][j] = 0;
		}
	}

	int userChoice = 3;
	userChoice = inputValidation();
	std::cout << std::endl;

	std::cout << "Please enter a coordinate from (0, 0) to (19, 39)\n"
		"for where you would like to place your object.\n"
		"Your choice is the approximate center of the object :)!" << std::endl;


	std::string xCoord;
	std::string yCoord;

	int xResult = -1;
	int yResult = -1;

	std::cout << std::endl;

	while ((xResult < 0) || (xResult > 39))
	{
		std::cout << "Please enter a X coordinate from 0 to 39 and press enter: ";
		std::getline(std::cin, xCoord);

		std::stringstream conversion(xCoord);
		if (!(conversion >> xResult))
			xResult = -1;
	}

	while ((yResult < 0) || (yResult > 19))
	{
		std::cout << "Please enter a Y coordinate from 0 to 19 and press enter: ";
		std::getline(std::cin, yCoord);

		std::stringstream conversion(yCoord);
		if (!(conversion >> yResult))
			yResult = -1;
	}

	// set 0,0 to 5,5 for x and y coordinates
	xResult += 7;
	yResult += 7;

	// Oscilator Pattern Initiation
	if (userChoice == 1)
	{
		board[yResult][xResult + 1] = 1;
		board[yResult][xResult] = 1;
		board[yResult][xResult - 1] = 1;
	}

	// Glider Pattern Initiation
	if (userChoice == 2)
	{
		board[yResult][xResult - 1] = 1;
		board[yResult][xResult + 1] = 1;
		board[yResult + 1][xResult + 1] = 1;
		board[yResult + 1][xResult] = 1;
		board[yResult - 1][xResult + 1] = 1;
	}

	// Glider Gun Pattern Initiation
	if (userChoice == 3)
	{
		board[yResult][xResult - 17] = 1, board[yResult][xResult - 18] = 1, board[yResult + 1][xResult - 17] = 1;
		board[yResult + 1][xResult - 18] = 1, board[yResult - 1][xResult + 16] = 1, board[yResult - 2][xResult + 16] = 1;
		board[yResult - 2][xResult + 17] = 1, board[yResult - 1][xResult + 17] = 1, board[yResult][xResult + 2] = 1;
		board[yResult - 2][xResult + 2] = 1, board[yResult - 1][xResult + 2] = 1, board[yResult][xResult + 3] = 1;
		board[yResult - 1][xResult + 3] = 1, board[yResult - 2][xResult + 3] = 1, board[yResult - 3][xResult + 6] = 1;
		board[yResult + 1][xResult + 6] = 1, board[yResult + 2][xResult + 6] = 1, board[yResult - 4][xResult + 6] = 1;
		board[yResult + 1][xResult + 4] = 1, board[yResult - 3][xResult + 4] = 1, board[yResult + 1][xResult - 1] = 1;
		board[yResult][xResult - 2] = 1, board[yResult + 1][xResult - 2] = 1, board[yResult + 2][xResult - 2] = 1;
		board[yResult + 1][xResult - 4] = 1, board[yResult - 2][xResult - 5] = 1, board[yResult + 4][xResult - 5] = 1;
		board[yResult - 1][xResult - 3] = 1, board[yResult + 3][xResult - 3] = 1, board[yResult + 3][xResult - 7] = 1;
		board[yResult - 1][xResult - 7] = 1, board[yResult + 4][xResult - 6] = 1, board[yResult - 2][xResult - 6] = 1;
		board[yResult][xResult - 8] = 1, board[yResult + 1][xResult - 8] = 1, board[yResult + 2][xResult - 8] = 1;
	}

	/*
	* Initializes array to hold pending values.
	*/
	bool boardTemp[50][80];
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			boardTemp[i][j] = 0;
		}
	}

	std::cout << std::endl;

	/*
	* This algorithm decides whether a cell should live or die.
	* It tests every cell in the initial array and counts the
	* number of live cells surrounding it. It then determines
	* if a cell lives, dies, or spawns based on that number.
	*/
	for (int runs = 0; runs < 100; runs++) // number of runs to do
	{
		// copies board(current) into boardTemp(pending)
		for (int a = 0, a1 = 0; a < 50; a++, a1++)
		{
			for (int b = 0, b1 = 0; b < 80; b++, b1++)
				boardTemp[a1][b1] = board[a][b];
		}

		int count = 0;


		for (int d = 0; d < 50; d++)
		{
			for (int f = 0; f < 80; f++)
			{
				int livingCells = 0;

				if (board[d - 1][f - 1] == 1)
					livingCells++;

				if (board[d - 1][f] == 1)
					livingCells++;

				if (board[d - 1][f + 1] == 1)
					livingCells++;

				if (board[d][f - 1] == 1)
					livingCells++;

				if (board[d][f + 1] == 1)
					livingCells++;

				if (board[d + 1][f - 1] == 1)
					livingCells++;

				if (board[d + 1][f] == 1)
					livingCells++;

				if (board[d + 1][f + 1] == 1)
					livingCells++;

				// spawning by "reproduction"
				if (livingCells == 3)
					boardTemp[d][f] = 1;

				// death by loneliness
				if (livingCells < 2)
					boardTemp[d][f] = 0;

				//death by overpopulation
				if (livingCells > 3)
					boardTemp[d][f] = 0;

			}
		}

		// copies boardTemp(current) into board(past)
		// boardTemp is ONLY current because it has
		// been run through the algorithm above.
		for (int a = 0, a1 = 0; a < 50; a++, a1++)
		{
			for (int b = 0, b1 = 0; b < 80; b++, b1++)
				board[a1][b1] = boardTemp[a][b];
		}


		// prints out matrix (orginal)
		std::cout << "Original Matrix:" << std::endl;
		for (int i = 7; i < 27; i++)
		{
			for (int j = 7; j < 47; j++)
			{
				if (board[i][j] == 0)
					std::cout << "_";
				else
					std::cout << "x";
				if (j == 46)
					std::cout << std::endl;
			}
		}
		

		std::cout << std::endl;

		usleep(100000); // change to usleep(100000) on linux
		system("clear"); // change to system("clear") on linux

		if (runs == 99)
		{
			int x;
			std::cout << "Press 1 to continue for 100"
				"more generations or\npress 2 to exit." << std::endl;
			std::cin >> x;
			
			if (x == 1)
				runs = 0;
		}
	}

	//std::cin.get();
	//std::cin.get();
	return 0;
}
/*********************************************************************
** Function: inputValidation()
** Description: Loops until user either exits or chooses valid input
** Parameters: nothing
** Pre-Conditions: needs to be called in main
** Post-Conditions:
*********************************************************************/
int inputValidation()
{
	bool inputFlag = 0;
	int choiceInt;
	std::string choice;
	std::cout << "Please enter\n1 for Oscilator,\n2 for glider, or"
		"\n3 for a glider cannon!" << std::endl;
	do {
		// converts input to int
		std::getline(std::cin, choice);
		std::stringstream conversion(choice);
		if (!(conversion >> choiceInt))
			choiceInt = 0;

		if (choiceInt == 1)
		{
			std::cout << "Your choice is an Oscilator!";
			inputFlag = 1;
		}

		else if (choiceInt == 2)
		{
			std::cout << "Your choice is a Glider!";
			inputFlag = 1;
		}
		else if (choiceInt == 3)
		{
			std::cout << "Your choice is a Glider Cannon!";
			inputFlag = 1;
		}
		else
		{
			std::cout << "Invalid choice. Please enter 1, 2, 3." << std::endl;
		}
	} while (inputFlag == 0);
	return choiceInt;
}