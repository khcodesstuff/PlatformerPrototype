#include <SFML/Graphics.hpp>

class doughnutBar{
    public:
        doughnutBar(sf::RenderWindow& window);

        sf::Sprite getSprite();
        int getValue();

        void setPosition(sf::Vector2f pos);
        void setValue(int val);
        void drawMe();

    private:
        sf::RenderWindow* windowPtr;
        
        sf::Texture textures[10];
        sf::Sprite sprite;
        int barValue;
};