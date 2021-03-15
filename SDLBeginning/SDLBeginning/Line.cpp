#include "Line.h"

Line::Line()
{
    xStart = rand() % 1000 + 1;
    xEnd = rand() % 1000 + 1;
    yEnd = rand() % 1000 + 1;
    yStart = rand() % 1000 + 1;

}

int randColorElement()
{
    int r = rand() % 255 + 1;


    return r;




}
