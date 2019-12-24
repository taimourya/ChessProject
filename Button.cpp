#include "Button.h"

Button::Button() : Sprite()
{
}
void Button::createButton(int posx, int posy, int width, int height, const Color& couleur)
{
    Texture texture;
    texture.create(width, height);
    setTexture(texture);
    setColor(couleur);
    setPosition(Vector2f(posx, posy));
    this->posx = posx;
    this->posy = posy;
    this->width = width;
    this->height = height;
}
bool Button::isClicked(const Event& event)
{
    if (event.type == Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if(event.mouseButton.x >= posx && event.mouseButton.y >= posy
            && event.mouseButton.x <= posx + width && event.mouseButton.y <= posy + height)
                return true;
        }
    }
    return false;
}

