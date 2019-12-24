#ifndef GRAPHIQUECHESS_H
#define GRAPHIQUECHESS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Chess.h"
#include "Button.h"


using namespace sf;
using namespace std;
using chess::Chess;

namespace chess
{
    #define BLOCK 100
    #define SCREEN_WIDTH N*BLOCK+50
    #define SCREEN_HEIGHT N*BLOCK+50

    class GraphiqueChess : public Chess
    {
        public:
            GraphiqueChess();

            void draw();

        private:
            void drawPiece(int i, int j, const Color& couleur);
            bool mouve(int x1, int y1, int x2, int y2); /// masquage

            Sprite createSprite(int posx, int posy, int width, int height, const Color& couleur);
            void createBoard();
            void drawBoard();
            bool isBoardClicked(const Event& event, int &x, int &y);
            Text createText(const string& textString, int taille, int posx, int posy, const Color& couleur);
            void createPiece(Sprite& pieceSprite, Texture& PieceTexture, const string& textureFile);
        private:
            RenderWindow window;
            Font font;
            Button board[N][N];

            Sprite pionSprite;
            Sprite tourSprite;
            Sprite fouSprite;
            Sprite chevalSprite;
            Sprite kingSprite;
            Sprite queenSprite;
            Texture pionTexture;
            Texture tourTexture;
            Texture fouTexture;
            Texture chevalTexture;
            Texture kingTexture;
            Texture queenTexture;
    };
}


#endif // GRAPHIQUECHESS_H
