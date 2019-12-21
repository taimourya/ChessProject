#ifndef PIECE_H
#define PIECE_H

#include <iostream>


using namespace std;

namespace chess
{
    ///couleur de la piece
    #define WHITE 1
    #define BLACK 2

    ///types
    #define TOUR "Tour"
    #define CHEVAL "Cheval"
    #define FOU "Fou"
    #define REINNE "Queen"
    #define ROI "King"
    #define PION "Pion"

    class Piece
    {
        public:
            Piece(string, int, int);
            string getType() const;
            int getCouleur() const;
            int getPoint() const;

        private:
            string type;
            int couleur;
            int point;

    };
}

#endif // PIECE_H
