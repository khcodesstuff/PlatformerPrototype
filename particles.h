#include <SFML/Graphics.hpp>
using namespace std; // vector

class Particles{
    public:
        Particles(sf::RenderWindow& window, sf::Vector2f pos, vector<string> texturesStr);
        
        int anim();
        void drawMe();

    private:
        sf::RenderWindow* windowPtr;

        vector<sf::Texture> texturesVector;
        sf::Sprite sprite;

        int animTimer;
        int textureCounter;
};