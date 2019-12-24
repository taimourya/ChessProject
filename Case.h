#ifndef CASE_H
#define CASE_H

#include "Piece.h"


using namespace std;

namespace chess
{
    #define VIDE 0

    class Case
    {
        public:
            Case();
            Case(string nom);
            Case(string nom, string type, int couleur, int point);
            Case(const Case&) = delete;
            Case operator=(const Case&) = delete;
            ~Case();

            void setCase(string nom, string type, int couleur, int point);
            void setCase(string nom);
            void vider();
            bool isFree() const;
            int couleurOfPiece() const;
            bool isSame(const Case&) const;
            bool isEnnemy(const Case&) const;
            bool deplacer(Case& c);
            bool switchTmp(Case& c, Case& tmp);
            bool retourTmp(Case& c, Case& tmp);

            char getCharType() const;
            string getType() const;
            int getPoint() const;

        private:
            string nom;
            Piece *p;


    };
}


#endif // CASE_H
