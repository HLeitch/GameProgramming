#pragma once
#include<iostream>

class Character
{
public:
	char myValue;
	int index;

	Character(char val, int i)
	{
		myValue = val;
		index = i;


	}

	void printMe()
	{
		printf("%c at position %u\n", myValue, index);

	}

};

