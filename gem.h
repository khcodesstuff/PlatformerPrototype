#include <SFML/Graphics.hpp>
using std::string;

class Gem{
    public:
        Gem(sf::RenderWindow& window, sf::Vector2f pos, string textureColor);

        sf::Sprite getSprite();
        
        void moveMe(sf::Vector2f value);

        void udpate();
        void drawMe();

    private:
        sf::RenderWindow* windowPtr;

        sf::Texture texture;
        sf::Sprite sprite;
};