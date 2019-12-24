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

        protected:
            void afficher();
            void afficherGraphique();

            ///choix mouvement
            void choixMouve(int& x1, int& y1, int& x2, int& y2);

            ///valider mouvement des pieces
            bool mouve();
            bool mouvePion(int x1, int y1, int x2, int y2);
            bool mouveTour(int x1, int y1, int x2, int y2);
            bool mouveCheval(int x1, int y1, int x2, int y2);
            bool mouveFou(int x1, int y1, int x2, int y2);
            bool mouveQueen(int x1, int y1, int x2, int y2);
            bool mouveKing(int x1, int y1, int x2, int y2);

            ///traitement check et check mate
            bool isKingCheck(int x, int y, int* txEnnemy, int *tyEnnemy, int nEnnemy);
            void chercherKing(int &x, int &y);
            bool checkMate(int* txKing, int* tyKing, int &nKing, bool &isCheck);
            bool isMouveSaveKing(int xKing, int yKing);

            ///calcule des cas possible de l'ennemi
            void mouveEnnemyPossible(int* tx, int* ty, int &nb);

            ///calcule des cas possible
            void calculMouveOfPiece(int x, int y, int *tx, int *ty, int &nb);

            void calculMouveOfPion(int x, int y, int *tx, int *ty, int &nb);
            void calculMouveOfTour(int x, int y, int *tx, int *ty, int &nb);
            void calculMouveOfCheval(int x, int y, int *tx, int *ty, int &nb);
            void calculMouveOfFou(int x, int y, int *tx, int *ty, int &nb);
            void calculMouveOfQueen(int x, int y, int *tx, int *ty, int &nb);
            void calculMouveOfKing(int x, int y, int *tx, int *ty, int &nb);


        protected:
            Case terrain[8][8];
            int tour;
            int scoreWhite, scoreBlack;

    };
}

#endif // CHESS_H
