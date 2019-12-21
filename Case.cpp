#include "Case.h"
#include <stdlib.h>

using namespace chess;

Case::Case()
{
    this->nom = "a1";
    this->p = 0;
}
Case::Case(string nom)
{
    this->nom = nom;
    this->p = 0;
}

Case::Case(string nom, string type, int couleur, int point)
{
    this->nom = nom;
    this->p = new Piece(type, couleur, point);
}

Case::~Case()
{
    if(p!=0)
    {
        delete p;
        p=0;
    }
}

void Case::setCase(string nom)
{
    this->nom = nom;
    this->p = 0;
}
void Case::setCase(string nom, string type, int couleur, int point)
{
    this->nom = nom;
    this->p = new Piece(type, couleur, point);
}

void Case::vider()
{
    if(p!=0)
    {
        delete p;
        p=0;
    }
}
bool Case::isFree() const
{
    if(p==0)
        return true;
    return false;
}
int Case::couleurOfPiece() const
{
    if(isFree())
        return VIDE;
    return p->getCouleur();
}
bool Case::isSame(const Case& c) const
{
    if(isFree() || c.isFree())
        return false;
    //cout << couleurOfPiece() << " vs " << c.couleurOfPiece() << endl;
    if(couleurOfPiece() == c.couleurOfPiece())
        return true;

    return false;
}
bool Case::isEnnemy(const Case& c) const
{
    if(isFree() || c.isFree())
        return false;
    if(p->getCouleur() != c.p->getCouleur())
        return true;
    return false;
}
bool Case::deplacer(Case& c)
{
    if(isSame(c))
        return false;
    if(!c.isFree())
        c.vider();

    c.p = p;
    p = 0;
    return true;
}

char Case::getCharType() const
{
    char c = (p->getType())[0];
    if(c>='a' && c>='z')
        c-=32;
    return c; ///-32 pour maj
}
string Case::getType() const
{
    return p->getType();
}
int Case::getPoint() const
{
    return p->getPoint();
}















