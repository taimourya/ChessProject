#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Button : public Sprite
{
    public :
        Button();
        void createButton(int posx, int posy, int width, int height, const Color& couleur);
        bool isClicked(const Event& event);
    private:
        int posx, posy;
        int width, height;
};

#endif // BUTTON_H
