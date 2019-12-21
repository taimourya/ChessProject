#ifndef CHESS_H
#define CHESS_H

#include "Case.h"


namespace chess
{

    #define N 8

    class Chess
    {
        public:
            Chess();
            void play();

        private:
            void afficher();

            void choixMouve(int& x1, int& y1, int& x2, int& y2);
            bool mouve();

            bool mouvePion(int x1, int y1, int x2, int y2);
            bool mouveTour(int x1, int y1, int x2, int y2);
            bool mouveCheval(int x1, int y1, int x2, int y2);
            bool mouveFou(int x1, int y1, int x2, int y2);
            bool mouveQueen(int x1, int y1, int x2, int y2);
            bool mouveKing(int x1, int y1, int x2, int y2);

            void mouveEnnemyPossible(int* tx, int* ty, int &nb);

            void calculMouveOfPiece(int x, int y, int *tx, int *ty, int &nb);

            void calculMouveOfPion(int x, int y, int *tx, int *ty, int &nb);
            void calculMouveOfTour(int x, int y, int *tx, int *ty, int &nb);
            void calculMouveOfCheval(int x, int y, int *tx, int *ty, int &nb);
            void calculMouveOfFou(int x, int y, int *tx, int *ty, int &nb);
            void calculMouveOfQueen(int x, int y, int *tx, int *ty, int &nb);
            void calculMouveOfKing(int x, int y, int *tx, int *ty, int &nb);


        private:
            Case terrain[8][8];
            int tour;
            int scoreWhite, scoreBlack;
    };
}

#endif // CHESS_H
