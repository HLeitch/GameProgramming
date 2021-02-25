// Workshop 2 Task 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "person.h"
#include<vector>





int main()
{
	std::vector<Person*> players;
	std::string userInput;
	printf("Please input players \n");
	std::cin >> userInput;


	for(char c : userInput)
	{
		Person* newPlayer = new Person(c);

		players.push_back(newPlayer);

	}

	for (Person* p : players)
	{
		p->displayScore();

	}
	std::string exiting = "";

	while (exiting != "exit")
	{
		userInput = "";
		printf("Please insert a score table\n");
		std::cin >> userInput;

		for (char c : userInput)
		{
			bool found = false;

			for (Person* p : players)
			{
				if (c == p->name)
				{
					p->addScore();
					found = true;
					break;
				}
				else if (c == p->name + 26)
				{
					p->subtractScore();
					found = true;
					break;

				}

			}

			

		}

		for (Person* p : players)
		{
			p->displayScore();

		}

		if (userInput == "exit")
			{
				exiting = "exit";

			}
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
