#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Chess.h"

using namespace chess;

Chess::Chess()
{
    tour = WHITE;
    scoreWhite = 0;
    scoreBlack = 0;

    ///initialisation des cases

    terrain[0][0].setCase("A8", TOUR, BLACK, 5);
    terrain[0][1].setCase("B8", CHEVAL, BLACK, 3);
    terrain[0][2].setCase("C8", FOU, BLACK, 3);
    terrain[0][3].setCase("D8", REINNE, BLACK, 9);
    terrain[0][4].setCase("E8", ROI, BLACK, 0);
    terrain[0][5].setCase("F8", FOU, BLACK, 3);
    terrain[0][6].setCase("G8", CHEVAL, BLACK, 3);
    terrain[0][7].setCase("H8", TOUR, BLACK, 5);

    terrain[1][0].setCase("A7", PION, BLACK, 1);
    terrain[1][1].setCase("B7", PION, BLACK, 1);
    terrain[1][2].setCase("C7", PION, BLACK, 1);
    terrain[1][3].setCase("D7", PION, BLACK, 1);
    terrain[1][4].setCase("E7", PION, BLACK, 1);
    terrain[1][5].setCase("F7", PION, BLACK, 1);
    terrain[1][6].setCase("G7", PION, BLACK, 1);
    terrain[1][7].setCase("H7", PION, BLACK, 1);

    int i=0, j=0;
    string nomCase = "A6";
    for(i=2; i<N-2; i++)
    {
        for(j=0; j<N; j++)
        {
            terrain[i][j].setCase(nomCase);
            nomCase[0]++;
        }
        nomCase[1]--;
    }

    //terrain[3][4].setCase("E7", PION, BLACK, 1);

    terrain[7][0].setCase("A1", TOUR, WHITE, 5);
    terrain[7][1].setCase("B1", CHEVAL, WHITE, 3);
    terrain[7][2].setCase("C1", FOU, WHITE, 3);
    terrain[7][3].setCase("D1", REINNE, WHITE, 9);
    terrain[7][4].setCase("E1", ROI, WHITE, 0);
    terrain[7][5].setCase("F1", FOU, WHITE, 3);
    terrain[7][6].setCase("G1", CHEVAL, WHITE, 3);
    terrain[7][7].setCase("H1", TOUR, WHITE, 5);

    terrain[6][0].setCase("A2", PION, WHITE, 1);
    terrain[6][1].setCase("B2", PION, WHITE, 1);
    terrain[6][2].setCase("C2", PION, WHITE, 1);
    terrain[6][3].setCase("D2", PION, WHITE, 1);
    terrain[6][4].setCase("E2", PION, WHITE, 1);
    terrain[6][5].setCase("F2", PION, WHITE, 1);
    terrain[6][6].setCase("G2", PION, WHITE, 1);
    terrain[6][7].setCase("H2", PION, WHITE, 1);
}

void Chess::afficher()
{
    int i, j;
    string tourCouleur;
    int colTextCoueleur;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);
    if(tour==WHITE)
    {
        tourCouleur = "White";
        colTextCoueleur = 15;
    }
    else
    {
        tourCouleur = "Red  ";
        colTextCoueleur = 12;
    }
    cout << endl << "score white : " << scoreWhite << " | tour : ";
        SetConsoleTextAttribute(hConsole, colTextCoueleur);
    cout << tourCouleur;
        SetConsoleTextAttribute(hConsole, 15);
    cout << " | score black : " << scoreBlack << endl << endl;
        SetConsoleTextAttribute(hConsole, 10);
    cout << "      | A | B | C | D | E | F | G | H |" << endl;
        SetConsoleTextAttribute(hConsole, 15);
    cout << "      |   |   |   |   |   |   |   |   |" << endl;
    cout << "      ---------------------------------" << endl;
    for(i=0; i<N; i++)
    {

        SetConsoleTextAttribute(hConsole, 10);
        cout << "    " << N-i;
        SetConsoleTextAttribute(hConsole, 15);
        cout << " |";
        for(j=0; j<N; j++)
        {
            if(terrain[i][j].isFree())
            {
                cout << "   |";
            }
            else
            {
                if(terrain[i][j].couleurOfPiece() == BLACK)
                    SetConsoleTextAttribute(hConsole, 12);
                cout << " " << terrain[i][j].getCharType();
                SetConsoleTextAttribute(hConsole, 15);
                cout << " |";
            }
        }
        cout << endl << "      ---------------------------------" << endl;
    }
}
void Chess::play()
{
    int txKing[100], tyKing[100], nKing=0;
    bool fin = false;
    bool isCheck = false;

    ///condition checkMate fin de la partie.
    while(!fin)
    {

        system("cls");
        afficher();
        if(isCheck)
            cout << "Check" << endl;
        if(mouve())
        {
            tour = tour == WHITE? BLACK:WHITE;
            fin = checkMate(txKing, tyKing, nKing, isCheck);
        }
    }

    system("cls");
    afficher();

    //tour change avant de quitter la boucle
    string winner = tour==WHITE? "Red": "White";
    cout << "check Mate winner is " << winner << endl;
}


///choix mouvement
void Chess::choixMouve(int& x1, int& y1, int& x2, int& y2)
{
    char choix[20];
    char c;
    bool trouve = false;

    do
    {
        cout << "choix (a1 to b1) : ";
        fflush(stdin);
        gets(choix);
    }while(strlen(choix)!=8);

    ///debut
    if(choix[0]>= 'a' && choix[0] <= 'z')
        choix[0]-=32;

    for(c='A', y1=-1; c<='H' && !trouve; c++, y1++)
    {
        if(c == choix[0])
            trouve = true;
    }
    x1 = N-(choix[1]-'0');

    ///cible
    if(choix[6]>= 'a' && choix[6] <= 'z')
        choix[6]-=32;

    trouve = false;
    for(c='A', y2=-1; c<='H' && !trouve; c++, y2++)
    {
        if(c == choix[6])
            trouve = true;
    }
    x2 = N-(choix[7]-'0');

}

///valider mouvement des pieces
bool Chess::mouve()
{
    int x1, y1, x2, y2;
    ///x ligne
    ///y colonne
    int xKing, yKing;
    int txEnnemy[100], tyEnnemy[100], nEnnemy=0;
    Case tmp;

    do
    {
        choixMouve(x1, y1, x2, y2);
    }while((x1<0 && x1>=8) || (x2<0 && x2>=8) || (y1<0 && y1>=8) || (y2<0 && y2>=8));



    if(terrain[x1][y1].isFree())/// si on a sélectioner une case vide on quitte
        return false;
    if(terrain[x1][y1].couleurOfPiece() != tour) /// si on a sélectioner une piéce de l'ennemi on quitte
        return false;
    if(x1 == x2 && y1 == y2)/// si on a séletionner case depart = case arriver on quite
        return false;
    if(terrain[x1][y1].isSame(terrain[x2][y2]))///si la case d'arriver est une piéce coep
        return false;

    if(terrain[x1][y1].getType() == PION)
    {
        if(!mouvePion(x1, y1, x2, y2))
            return false;
    }
    if(terrain[x1][y1].getType() == TOUR)
    {
        if(!mouveTour(x1, y1, x2, y2))
            return false;
    }
    if(terrain[x1][y1].getType() == CHEVAL)
    {
        if(!mouveCheval(x1, y1, x2, y2))
            return false;
    }
    if(terrain[x1][y1].getType() == FOU)
    {
        if(!mouveFou(x1, y1, x2, y2))
            return false;
    }
    if(terrain[x1][y1].getType() == REINNE)
    {
        if(!mouveQueen(x1, y1, x2, y2))
            return false;
    }
    if(terrain[x1][y1].getType() == ROI)
    {
        if(!mouveKing(x1, y1, x2, y2))
            return false;
    }

    ///verifier si se mouvement ne mettra pas le roi en danger (check mate)
    terrain[x1][y1].switchTmp(terrain[x2][y2], tmp);

    chercherKing(xKing, yKing);
    mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
    ///si c'est le cas on quitte (false)
    if(isKingCheck(xKing, yKing, txEnnemy, tyEnnemy, nEnnemy))
    {
        terrain[x2][y2].retourTmp(terrain[x1][y1], tmp);
        return false;
    }
    terrain[x2][y2].retourTmp(terrain[x1][y1], tmp);


    ///si la case arriver est un ennemi on modifie le scors celon la piéce mangé
    if(terrain[x1][y1].isEnnemy(terrain[x2][y2]))
    {
        if(terrain[x1][y1].couleurOfPiece() == WHITE)
            scoreWhite += terrain[x2][y2].getPoint();
        else
            scoreBlack += terrain[x2][y2].getPoint();
    }

    ///si on arive jusqu'a la cela veut dire qu'on peut deplacer la piéce
    terrain[x1][y1].deplacer(terrain[x2][y2]);

    return true;
}

bool Chess::mouvePion(int x1, int y1, int x2, int y2)
{

    int po;
    if(x1==x2)
        return false;
    if((y2 > y1+1 || y2 < y1-1)) ///un pion peut manger ses diagonale
        return false;
    if((!terrain[x1][y1].isEnnemy(terrain[x2][y2]) && ((y2 == y1+1 || y2 == y1-1))))/// on peut manger sur la diagonale que si un ennemi s'y trouve
        return false;

    if(terrain[x1][y1].couleurOfPiece()==WHITE)
    {
        if(y2 == y1)
        {
            if(!terrain[x1-1][y1].isFree())///si il y'as un obstacle
                return false;
        }
        po = x1 == 6? 2:1; /// la porter du pion qu'on il est sur ca case de depart est 2
        if(x2 < x1-po || x1 < x2) ///on ne peut pas depasser la porter du pion et pas de retour en arriére
            return false;
    }
    if(terrain[x1][y1].couleurOfPiece()==BLACK)
    {
        if(y2 == y1)
        {
            if(!terrain[x1+1][y1].isFree())///si il y'as un obstacle
                return false;
        }
        po = x1 == 1? 2:1;
        if(x2 > x1+po || x1 > x2)
            return false;
    }

    return true;
}

bool Chess::mouveTour(int x1, int y1, int x2, int y2)
{
    if(x1 != x2 && y1 != y2)/// une tour bouge que en ligne
        return false;

    int debut, fin;

    if(x1 == x2)///verification obstacle colonne
    {
        if(y1<y2)
        {
            debut = y1+1;
            fin = y2;
        }
        else
        {
            debut = y2+1;
            fin = y1;
        }
        for(; debut<fin; debut++)
        {
            if(!terrain[x1][debut].isFree())
                return false;
        }
    }
    else///verification obstacle ligne
    {
        if(x1<x2)
        {
            debut = x1+1;
            fin = x2;
        }
        else
        {
            debut = x2+1;
            fin = x1;
        }
        for(; debut<fin; debut++)
        {
            if(!terrain[debut][y1].isFree())
                return false;
        }
    }

    return true;
}
bool Chess::mouveCheval(int x1, int y1, int x2, int y2)
{
    /// si la case choisi ne fait pas parti des cases possible pour le cheval on retourne false
    if((x1!=x2+2 || y1!=y2+1) && (x1!=x2+2 || y1!=y2-1) && (x1!=x2-2 || y1!=y2+1) && (x1!=x2-2 || y1!=y2-1)
    && (x1!=x2+1 || y1!=y2+2) && (x1!=x2-1 || y1!=y2+2) && (x1!=x2+1 || y1!=y2-2) && (x1!=x2-1 || y1!=y2-2))
        return false;
    return true;
}
bool Chess::mouveFou(int x1, int y1, int x2, int y2)
{
    int i, j;
    bool trouve = false;
    bool obstacle = false;

    for(i=x1-1, j=y1-1; i>= 0 && j>=0 && !trouve; i--, j--) ///diag-
    {
        if(x2 == i && y2 == j)
            trouve = true;
        else
        {
            if(!terrain[i][j].isFree())
                obstacle = true;
        }
    }

    if(trouve)
    {
        ///verification obstacle
        if(obstacle)
            return false;
    }
    else
    {
        trouve = false;
        obstacle = false;
        for(i=x1+1, j=y1+1; i<N && j<N && !trouve; i++, j++) ///diag+
        {
            if(x2 == i && y2 == j)
                trouve = true;
            else
            {
                if(!terrain[i][j].isFree())
                    obstacle = true;
            }
        }
        if(trouve)
        {
            ///verification obstacle
            if(obstacle)
                return false;
        }
        else
        {
            trouve = false;
            obstacle = false;
            for(i=x1-1, j=y1+1; i>=0 && j<N && !trouve; i--, j++) ///anti diag-
            {
                if(x2 == i && y2 == j)
                    trouve = true;
                else
                {
                    if(!terrain[i][j].isFree())
                        obstacle = true;
                }
            }
            if(trouve)
            {
                if(obstacle)
                    return false;
            }
            else
            {
                trouve = false;
                for(i=x1+1, j=y1-1; i<N && j>=0 && !trouve; i++, j--)///anti diag +
                {
                    if(x2 == i && y2 == j)
                        trouve = true;
                    else
                    {
                        if(!terrain[i][j].isFree())
                            obstacle = true;
                    }
                }
                if(trouve)
                {
                    if(obstacle)
                        return false;
                }
                else
                {
                    return false;
                }
            }
        }
    }



    return true;
}
bool Chess::mouveQueen(int x1, int y1, int x2, int y2)
{
    ///reinne = mouvement de la tour + fou
    if(!mouveTour(x1, y1, x2, y2))
    {
        if(!mouveFou(x1, y1, x2, y2))
            return false;
    }
    return true;
}

bool Chess::mouveKing(int x1, int y1, int x2, int y2)
{
    if((x1!=x2+1 || y1!=y2) && (x1!=x2-1 || y1!=y2) && (x1!=x2|| y1!=y2+1) && (x1!=x2 || y1!=y2-1)
    && (x1!=x2+1 || y1!=y2+1) && (x1!=x2-1 || y1!=y2+1) && (x1!=x2+1 || y1!=y2-1) && (x1!=x2-1 || y1!=y2-1))
        return false;
    return true;
}



///traitement check et check mate
void Chess::chercherKing(int& x, int& y)
{
    ///chercher la position du roi du tour actuelle
    for(x=0; x<N; x++)
    {
        for(y=0; y<N; y++)
        {
            if(!terrain[x][y].isFree())
            {
                if(terrain[x][y].getType() == ROI && terrain[x][y].couleurOfPiece() == tour)
                {
                    return;
                }
            }
        }
    }
}

bool Chess::isKingCheck(int x, int y, int* txEnnemy, int *tyEnnemy, int nEnnemy)
{
    int i;
    ///verifie si le roi est en etat check par rapport au case domminer par l'ennemi
    for(i=0; i<nEnnemy; i++)
    {
        if(x==txEnnemy[i] && y==tyEnnemy[i])
        {
            return true;
        }
    }
    return false;
}
bool Chess::checkMate(int* txKing, int* tyKing, int &nKing, bool &isCheck)
{
    ///si aucun mouvement possible et le roi ne peut pas bouger cela veut dire que c'est la fin de la parti check mate return false
    int x, y;
    int cpt = 0;
    int txEnnemy[100], tyEnnemy[100], nEnnemy=0;
    Case tmp;

    isCheck = false;
    nKing = 0;
    chercherKing(x, y);

    ///cpt compteur sur le nombre de position check sur le roi Max 9

    ///check sur la place du roi
    mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
    if(isKingCheck(x, y, txEnnemy, tyEnnemy, nEnnemy))
    {
        ///si le roi est check sur ca place cpt++
        isCheck = true;
        cpt++;
    }

    ///verification sur la porter du roi
    if(x+1<N)
    {
        if(!terrain[x][y].isSame(terrain[x+1][y]))
        {
            terrain[x][y].switchTmp(terrain[x+1][y], tmp);
            mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
            if(isKingCheck(x+1, y, txEnnemy, tyEnnemy, nEnnemy))
                cpt++;
            else
            {
                txKing[nKing] = x+1;
                tyKing[nKing] = y;
                nKing++;
            }
            terrain[x+1][y].retourTmp(terrain[x][y], tmp);
        }
        else
            cpt++;
    }
    else
        cpt++;
    if(x-1>=0)
    {
        if(!terrain[x][y].isSame(terrain[x-1][y]))
        {
            terrain[x][y].switchTmp(terrain[x-1][y], tmp);
            mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
            if(isKingCheck(x-1, y, txEnnemy, tyEnnemy, nEnnemy))
                cpt++;
            else
            {
                txKing[nKing] = x-1;
                tyKing[nKing] = y;
                nKing++;
            }
            terrain[x-1][y].retourTmp(terrain[x][y], tmp);
        }
        else
            cpt++;
    }
    else
        cpt++;
    if(y+1<N)
    {
        if(!terrain[x][y].isSame(terrain[x][y+1]))
        {
            terrain[x][y].switchTmp(terrain[x][y+1], tmp);
            mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
            if(isKingCheck(x, y+1, txEnnemy, tyEnnemy, nEnnemy))
                cpt++;
            else
            {
                txKing[nKing] = x;
                tyKing[nKing] = y+1;
                nKing++;
            }
            terrain[x][y+1].retourTmp(terrain[x][y], tmp);
        }
        else
            cpt++;
    }
    else
        cpt++;
    if(y-1>=0)
    {
        if(!terrain[x][y].isSame(terrain[x][y-1]))
        {
            terrain[x][y].switchTmp(terrain[x][y-1], tmp);
            mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
            if(isKingCheck(x, y-1, txEnnemy, tyEnnemy, nEnnemy))
                cpt++;
            else
            {
                txKing[nKing] = x;
                tyKing[nKing] = y-1;
                nKing++;
            }
            terrain[x][y-1].retourTmp(terrain[x][y], tmp);
        }
        else
            cpt++;
    }
    else
        cpt++;
    if(x+1<N && y+1<N)
    {
        if(!terrain[x][y].isSame(terrain[x+1][y+1]))
        {
            terrain[x][y].switchTmp(terrain[x+1][y+1], tmp);
            mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
            if(isKingCheck(x+1, y+1, txEnnemy, tyEnnemy, nEnnemy))
                cpt++;
            else
            {
                txKing[nKing] = x+1;
                tyKing[nKing] = y+1;
                nKing++;
            }
            terrain[x+1][y+1].retourTmp(terrain[x][y], tmp);
        }
        else
            cpt++;
    }
    else
        cpt++;
    if(x-1>=0 && y+1<N)
    {
        if(!terrain[x][y].isSame(terrain[x-1][y+1]))
        {
            terrain[x][y].switchTmp(terrain[x-1][y+1], tmp);
            mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
            if(isKingCheck(x-1, y+1, txEnnemy, tyEnnemy, nEnnemy))
                cpt++;
            else
            {
                txKing[nKing] = x-1;
                tyKing[nKing] = y+1;
                nKing++;
            }
            terrain[x-1][y+1].retourTmp(terrain[x][y], tmp);
        }
        else
            cpt++;
    }
    else
        cpt++;
    if(x+1<N && y-1>=0)
    {
        if(!terrain[x][y].isSame(terrain[x+1][y-1]))
        {
            terrain[x][y].switchTmp(terrain[x+1][y-1], tmp);
            mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
            if(isKingCheck(x+1, y-1, txEnnemy, tyEnnemy, nEnnemy))
                cpt++;
            else
            {
                txKing[nKing] = x+1;
                tyKing[nKing] = y-1;
                nKing++;
            }
            terrain[x+1][y-1].retourTmp(terrain[x][y], tmp);
        }
        else
            cpt++;
    }
    else
        cpt++;
    if(x-1>=0 && y-1>=0)
    {
        if(!terrain[x][y].isSame(terrain[x-1][y-1]))
        {
            terrain[x][y].switchTmp(terrain[x-1][y-1], tmp);
            mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
            if(isKingCheck(x-1, y-1, txEnnemy, tyEnnemy, nEnnemy))
                cpt++;
            else
            {
                txKing[nKing] = x-1;
                tyKing[nKing] = y-1;
                nKing++;
            }
            terrain[x-1][y-1].retourTmp(terrain[x][y], tmp);
        }
        else
            cpt++;
    }
    else
        cpt++;


    /*cout << "cpt : " << cpt << endl;
    system("pause");*/
    ///si cpt == 9 veut dire que tout les mouvements du roi sont controler par l'ennemie
    if(cpt==9)
    {
        ///reste a voir si une autre piece peut se sacrifier pour sauver le roi
        if(!isMouveSaveKing(x, y))
        {
            return true;
        }
    }

    return false;
}


bool Chess::isMouveSaveKing(int xKing, int yKing)
{
    ///verifie si une piéce peut se sacrifier
    int i, j, k;
    int txPosb[100], tyPosb[100], nPosb=0;
    int txEnnemy[100], tyEnnemy[100], nEnnemy=0;
    Case tmp;


    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            ///si la case n'est pas vide
            if(!terrain[i][j].isFree())
            {
                ///si se n'est pas le roi
                if(xKing != i || yKing != j)
                {
                    ///si c'est une piece du joueur tour
                    if(terrain[i][j].couleurOfPiece() == tour)
                    {
                        nPosb = 0;
                        ///calcule des mouvement possible de la piece actuelle
                        calculMouveOfPiece(i, j, txPosb, tyPosb, nPosb);

                        ///parcours des mouvement possible de la piece actuelle
                        for(k=0; k<nPosb; k++)
                        {
                            ///simulation des mouvement possible et verifierr si on a trouver un mouvement qui va sauver le roi
                            terrain[i][j].switchTmp(terrain[txPosb[k]][tyPosb[k]], tmp);
                            mouveEnnemyPossible(txEnnemy, tyEnnemy, nEnnemy);
                            ///si se mouvement peut sauver le roi
                            if(!isKingCheck(xKing, yKing, txEnnemy, tyEnnemy, nEnnemy))
                            {
                                ///on quitte avec return true (on peut sauver le roi)
                                terrain[txPosb[k]][tyPosb[k]].retourTmp(terrain[i][j], tmp);
                                return true;
                            }
                            terrain[txPosb[k]][tyPosb[k]].retourTmp(terrain[i][j], tmp);
                        }
                    }
                }
            }
        }
    }

    ///si on arrive jusqu'au la c'est que aucun mouvement ne peut sauver le roi
    return false;
}


///calcule des cas possible de l'ennemi
void Chess::mouveEnnemyPossible(int* tx, int* ty, int &nb)
{
    int i, j;

    int couleurEnnemy = tour == WHITE? BLACK: WHITE;

    nb = 0;

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(!terrain[i][j].isFree())
            {
                if(terrain[i][j].couleurOfPiece() == couleurEnnemy)
                {
                    calculMouveOfPiece(i, j, tx, ty, nb);
                }
            }
        }
    }
}


///calcule des cas possible
void Chess::calculMouveOfPiece(int x, int y, int *tx, int *ty, int &nb)
{
    if(terrain[x][y].getType() == PION)
        calculMouveOfPion(x, y, tx, ty, nb);
    else if(terrain[x][y].getType() == CHEVAL)
        calculMouveOfCheval(x, y, tx, ty, nb);
    else if(terrain[x][y].getType() == ROI)
        calculMouveOfKing(x, y, tx, ty, nb);
    else if(terrain[x][y].getType() == TOUR)
        calculMouveOfTour(x, y, tx, ty, nb);
    else if(terrain[x][y].getType() == FOU)
        calculMouveOfFou(x, y, tx, ty, nb);
    else if(terrain[x][y].getType() == REINNE)
        calculMouveOfQueen(x, y, tx, ty, nb);
}
void Chess::calculMouveOfPion(int x, int y, int* tx, int* ty, int &nb)
{
    int mouvementX = terrain[x][y].couleurOfPiece()==WHITE? -1: 1;

    if(y+1<N)
    {
        if(terrain[x][y].isEnnemy(terrain[x+mouvementX][y+1]))
        {
            tx[nb] = x+mouvementX;
            ty[nb] = y+1;
            nb++;
        }
    }
    if(y-1>=0)
    {
        if(terrain[x][y].isEnnemy(terrain[x+mouvementX][y-1]))
        {
            tx[nb] = x+mouvementX;
            ty[nb] = y-1;
            nb++;
        }
    }
}
void Chess::calculMouveOfCheval(int x, int y, int* tx, int* ty, int &nb)
{
    if(x+2<N && y+1<N)
    {
        if(!terrain[x][y].isSame(terrain[x+2][y+1]))
        {
            tx[nb] = x+2;
            ty[nb] = y+1;
            nb++;
        }
    }
    if(x+2<N && y-1>=0)
    {
        if(!terrain[x][y].isSame(terrain[x+2][y-1]))
        {
            tx[nb] = x+2;
            ty[nb] = y-1;
            nb++;
        }
    }
    if(x-2>=0 && y+1<N)
    {
        if(!terrain[x][y].isSame(terrain[x-2][y+1]))
        {
            tx[nb] = x-2;
            ty[nb] = y+1;
            nb++;
        }
    }
    if(x-2>=0 && y-1>=0)
    {
        if(!terrain[x][y].isSame(terrain[x-2][y-1]))
        {
            tx[nb] = x-2;
            ty[nb] = y-1;
            nb++;
        }
    }
    if(x+1<N && y+2<N)
    {
        if(!terrain[x][y].isSame(terrain[x+1][y+2]))
        {
            tx[nb] = x+1;
            ty[nb] = y+2;
            nb++;
        }
    }
    if(x-1>=0 && y+2<N)
    {
        if(!terrain[x][y].isSame(terrain[x-1][y+2]))
        {
            tx[nb] = x-1;
            ty[nb] = y+2;
            nb++;
        }
    }
    if(x+1<N && y-2>=0)
    {
        if(!terrain[x][y].isSame(terrain[x+1][y-2]))
        {
            tx[nb] = x+1;
            ty[nb] = y-2;
            nb++;
        }
    }
    if(x-1>=0 && y-2>=0)
    {
        if(!terrain[x][y].isSame(terrain[x-1][y-2]))
        {
            tx[nb] = x-1;
            ty[nb] = y-2;
            nb++;
        }
    }
}


void Chess::calculMouveOfKing(int x, int y, int* tx, int* ty, int& nb)
{
    if(x+1<N)
    {
        if(!terrain[x][y].isSame(terrain[x+1][y]))
        {
            tx[nb] = x+1;
            ty[nb] = y;
            nb++;
        }
    }
    if(x-1>=0)
    {
        if(!terrain[x][y].isSame(terrain[x-1][y]))
        {
            tx[nb] = x-1;
            ty[nb] = y;
            nb++;
        }
    }
    if(y+1<N)
    {
        if(!terrain[x][y].isSame(terrain[x][y+1]))
        {
            tx[nb] = x;
            ty[nb] = y+1;
            nb++;
        }
    }
    if(y-1>=0)
    {
        if(!terrain[x][y].isSame(terrain[x][y-1]))
        {
            tx[nb] = x;
            ty[nb] = y-1;
            nb++;
        }
    }
    if(x+1<N && y+1<N)
    {
        if(!terrain[x][y].isSame(terrain[x+1][y+1]))
        {
            tx[nb] = x+1;
            ty[nb] = y+1;
            nb++;
        }
    }
    if(x-1>=0 && y+1<N)
    {
        if(!terrain[x][y].isSame(terrain[x-1][y+1]))
        {
            tx[nb] = x-1;
            ty[nb] = y+1;
            nb++;
        }
    }
    if(x+1<N && y-1>=0)
    {
        if(!terrain[x][y].isSame(terrain[x+1][y-1]))
        {
            tx[nb] = x+1;
            ty[nb] = y-1;
            nb++;
        }
    }
    if(x-1>=0 && y-1>=0)
    {
        if(!terrain[x][y].isSame(terrain[x-1][y-1]))
        {
            tx[nb] = x-1;
            ty[nb] = y-1;
            nb++;
        }
    }
}
void Chess::calculMouveOfTour(int x, int y, int* tx, int* ty, int& nb)
{
    int i;
    int free = true;

    for(i=x+1; i<N && free; i++)///ligne +
    {
        if(!terrain[i][y].isFree())
        {
            if(!terrain[i][y].isSame(terrain[x][y]))
            {
                tx[nb] = i;
                ty[nb] = y;
                nb++;
            }
            free = false;
        }
        else
        {
            tx[nb] = i;
            ty[nb] = y;
            nb++;
        }
    }
    free=true;
    for(i=x-1; i>=0 && free; i--)///ligne -
    {
        if(!terrain[i][y].isFree())
        {
            if(!terrain[i][y].isSame(terrain[x][y]))
            {
                tx[nb] = i;
                ty[nb] = y;
                nb++;
            }
            free = false;
        }
        else
        {
            tx[nb] = i;
            ty[nb] = y;
            nb++;
        }
    }
    free=true;
    for(i=y+1; i<N && free; i++)///colonne +
    {
        if(!terrain[x][i].isFree())
        {
            if(!terrain[x][i].isSame(terrain[x][y]))
            {
                tx[nb] = x;
                ty[nb] = i;
                nb++;
            }
            free = false;
        }
        else
        {
            tx[nb] = x;
            ty[nb] = i;
            nb++;
        }
    }
    free=true;
    for(i=y-1; i>=0 && free; i--)///colonne -
    {
        if(!terrain[x][i].isFree())
        {
            if(!terrain[x][i].isSame(terrain[x][y]))
            {
                tx[nb] = x;
                ty[nb] = i;
                nb++;
            }
            free = false;
        }
        else
        {
            tx[nb] = x;
            ty[nb] = i;
            nb++;
        }
    }
}
void Chess::calculMouveOfFou(int x, int y, int* tx, int* ty, int& nb)
{
    int i, j;
    int free = true;

    for(i=x+1, j=y+1; i<N && j<N && free; i++, j++) ///diag +
    {
        if(!terrain[i][j].isFree())
        {
            if(!terrain[i][j].isSame(terrain[x][y]))
            {
                tx[nb] = i;
                ty[nb] = j;
                nb++;
            }
            free = false;
        }
        else
        {
            tx[nb] = i;
            ty[nb] = j;
            nb++;
        }
    }
    free = true;
    for(i=x-1, j=y-1; i>=0 && j>=0 && free; i--, j--) /// diag -
    {
        if(!terrain[i][j].isFree())
        {
            if(!terrain[i][j].isSame(terrain[x][y]))
            {
                tx[nb] = i;
                ty[nb] = j;
                nb++;
            }
            free = false;
        }
        else
        {
            tx[nb] = i;
            ty[nb] = j;
            nb++;
        }
    }
    free = true;
    for(i=x+1, j=y-1; i<N && j>=0 && free; i++, j--) /// anti diag +
    {
        if(!terrain[i][j].isFree())
        {
            if(!terrain[i][j].isSame(terrain[x][y]))
            {
                tx[nb] = i;
                ty[nb] = j;
                nb++;
            }
            free = false;
        }
        else
        {
            tx[nb] = i;
            ty[nb] = j;
            nb++;
        }
    }
    free = true;
    for(i=x-1, j=y+1; i>=0 && j<N && free; i--, j++) /// anti diag -
    {
        if(!terrain[i][j].isFree())
        {
            if(!terrain[i][j].isSame(terrain[x][y]))
            {
                tx[nb] = i;
                ty[nb] = j;
                nb++;
            }
            free = false;
        }
        else
        {
            tx[nb] = i;
            ty[nb] = j;
            nb++;
        }
    }
}

void Chess::calculMouveOfQueen(int x, int y, int* tx, int* ty, int& nb)
{
    calculMouveOfTour(x, y, tx, ty, nb);
    calculMouveOfFou(x, y, tx, ty, nb);
}



