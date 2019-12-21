#include <iostream>
#include "Piece.h"

using namespace chess;

Piece::Piece(string t, int c, int p)
{
    type = t;
    couleur = c;
    point = p;
}
string Piece::getType() const
{
    return type;
}
int Piece::getCouleur() const
{
    return couleur;
}
int Piece::getPoint() const
{
    return point;
}

