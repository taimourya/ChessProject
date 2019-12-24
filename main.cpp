#include <SFML/Graphics.hpp>
#include <iostream>
#include "GraphiqueChess.h"

using namespace sf;
using namespace std;
using chess::GraphiqueChess;


int main()
{
    GraphiqueChess chess;
    chess.draw();
    return 0;
}
