#include "GraphiqueChess.h"

using namespace chess;

GraphiqueChess::GraphiqueChess() : Chess()
{
    window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Chess");

    if(!font.loadFromFile("arial.ttf"))
    {
        cout << "erreur ouverture police arial" << endl;
    }

    createBoard();

    createPiece(pionSprite, pionTexture, "pieces/pion.png");
    createPiece(tourSprite, tourTexture, "pieces/tour.png");
    createPiece(chevalSprite, chevalTexture, "pieces/cheval.png");
    createPiece(fouSprite, fouTexture, "pieces/fou.png");
    createPiece(queenSprite, queenTexture, "pieces/queen.png");
    createPiece(kingSprite, kingTexture, "pieces/king.png");
}
void GraphiqueChess::play()
{
    pionSprite.setPosition(Vector2f(32, 32));
    pionSprite.setColor(Color::Black);
    int x1, y1;
    int x2, y2;
    bool mouve1 = true;
    bool mouve2 = false;

    int txKing[100], tyKing[100], nKing=0;
    bool fin = false;
    bool isCheck = false;


    while (window.isOpen() && !fin)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if(mouve1)
            {
                if(isBoardClicked(event, x1, y1))
                {
                    if(!terrain[x1][y1].isFree())
                    {
                        if(terrain[x1][y1].couleurOfPiece() == tour)
                        {
                            cout << "(" << x1 << "," << y1 << ")";
                            mouve1 = false;
                            mouve2 = true;
                        }
                    }
                }
            }
            else if(mouve2)
            {
                if(isBoardClicked(event, x2, y2))
                {
                    if(mouve(x1, y1, x2, y2))
                    {
                        cout << " to (" << x2 << "," << y2 << ") " << endl;
                        tour = tour == WHITE? BLACK:WHITE;
                        fin = checkMate(txKing, tyKing, nKing, isCheck);
                    }
                    mouve1 = true;
                    mouve2 = false;
                }
            }

        }
        window.clear();

        drawBoard();
        window.display();
    }
}
void GraphiqueChess::drawPiece(int i, int j, const Color& couleur)
{
            if(terrain[i][j].getType()==PION)
            {
                pionSprite.setColor(couleur);
                pionSprite.setPosition(Vector2f(32+(BLOCK*j), 32+(BLOCK*i)));
                window.draw(pionSprite);
            }
            else if(terrain[i][j].getType()==TOUR)
            {
                tourSprite.setColor(couleur);
                tourSprite.setPosition(Vector2f(32+(BLOCK*j), 32+(BLOCK*i)));
                window.draw(tourSprite);
            }
            else if(terrain[i][j].getType()==CHEVAL)
            {
                chevalSprite.setColor(couleur);
                chevalSprite.setPosition(Vector2f(32+(BLOCK*j), 32+(BLOCK*i)));
                window.draw(chevalSprite);
            }
            else if(terrain[i][j].getType()==FOU)
            {
                fouSprite.setColor(couleur);
                fouSprite.setPosition(Vector2f(32+(BLOCK*j), 32+(BLOCK*i)));
                window.draw(fouSprite);
            }
            else if(terrain[i][j].getType()==REINNE)
            {
                queenSprite.setColor(couleur);
                queenSprite.setPosition(Vector2f(32+(BLOCK*j), 32+(BLOCK*i)));
                window.draw(queenSprite);
            }
            else if(terrain[i][j].getType()==ROI)
            {
                kingSprite.setColor(couleur);
                kingSprite.setPosition(Vector2f(32+(BLOCK*j), 32+(BLOCK*i)));
                window.draw(kingSprite);
            }
}

Sprite GraphiqueChess::createSprite(int posx, int posy, int width, int height, const Color& couleur)
{
    Texture texture;
    texture.create(width, height);
    Sprite sprite(texture);
    sprite.setColor(couleur);
    sprite.setPosition(Vector2f(posx, posy));

    return sprite;
}
void GraphiqueChess::createBoard()
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            Color couleur = (i%2 == 0? (j%2==0? Color(232, 191, 124): Color(144, 81, 32)) : (j%2==0)? Color(144, 81, 32) : Color(232, 191, 124));
            //board[i][j] = createSprite(25+(BLOCK*j), 25+(BLOCK*i), BLOCK, BLOCK, couleur);
            board[i][j].createButton(25+(BLOCK*j), 25+(BLOCK*i), BLOCK, BLOCK, couleur);
        }
    }
}
void GraphiqueChess::drawBoard()
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            window.draw(board[i][j]);
            if(!terrain[i][j].isFree())
            {
                if(terrain[i][j].couleurOfPiece() == BLACK)
                {
                    drawPiece(i, j, Color::Black);
                }
                else
                {
                    drawPiece(i, j, Color::White);
                }
            }
        }
    }
}
bool GraphiqueChess::isBoardClicked(const Event& event, int &x, int &y)
{

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(board[i][j].isClicked(event))
            {
                x=i;
                y=j;
                return true;
            }
        }
    }
    return false;
}
Text GraphiqueChess::createText(const string& textString, int taille, int posx, int posy, const Color& couleur)
{
    Text text;
    text.setFont(font);

    text.setString(textString);

    text.setCharacterSize(taille);
    text.setFillColor(couleur);
    text.setPosition(Vector2f(posx, posy));
    return text;
}
void GraphiqueChess::createPiece(Sprite& pieceSprite, Texture& pieceTexture, const string& textureFile)
{
    if(!pieceTexture.loadFromFile(textureFile))
    {
        cout << "erreur ouverture piece " << textureFile << endl;
    }
    pieceSprite.setTexture(pieceTexture);
}

bool GraphiqueChess::mouve(int x1, int y1, int x2, int y2)
{
    ///x ligne
    ///y colonne
    int xKing, yKing;
    int txEnnemy[100], tyEnnemy[100], nEnnemy=0;
    Case tmp;


    if(terrain[x1][y1].isFree())/// si on a sélectioner une case vide on quitte
        return false;
    if(terrain[x1][y1].couleurOfPiece() != tour) /// si on a sélectioner une piéce de l'ennemi on quitte
        return false;
    if(x1 == x2 && y1 == y2)/// si on a séletionner case depart = case arriver on quitte
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









