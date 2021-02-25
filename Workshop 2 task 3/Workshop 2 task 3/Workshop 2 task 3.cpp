// Workshop 2 task 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <vector>

int main()
{

	std::string userInput;

	printf("Please choose some dice to roll\n");

	std::cin >> userInput;
	std::stringstream input(userInput);

	std::string die;

	if(std::getline(input,die,' '))
	{
		int seperator = die.find('d');
		int numberOfdie = std::stoi(die.substr(0, seperator));

		int typeOfDie = std::stoi(die.substr(seperator+1, die.length()));


		int rollCount = 0;

		int result = 0;

		while (rollCount < numberOfdie)
		{
			int roll = rand();
			bool rolled = false;
			while (!rolled)
			{
				roll = roll / typeOfDie;

				roll% typeOfDie;
				if (roll <= typeOfDie)
				{
					rolled = true;
				}
			}
			rollCount++;
			result += roll;
			std::cout<< die+ " die rolled a/an "+ std::to_string(roll) <<std::endl;
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
