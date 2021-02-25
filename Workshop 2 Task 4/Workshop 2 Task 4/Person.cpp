#include "Person.h"

Person::Person(char name)
{

	score = 0;
	this->name = name;

}

void Person::addScore()
{

	this->score++;
}

void Person::subtractScore()
{
	this->score--;
}

void Person::displayScore()
{

	printf("%c",name);
	printf(":");
	printf("%d",score);
	printf("\n");

}
