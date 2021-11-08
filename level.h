#include <SFML/Graphics.hpp>
//#include <string>
#include <time.h>
#include "gem.h"
using namespace std; // strings, vector

class Level{
    public:
        // Constructor
        Level(sf::RenderWindow& window);

        sf::Vector2f getLevelSize(); // for borders

        vector<sf::Sprite> getLevelTiles();
        vector<Gem*> getGems();
        void deleteRecreateGem(Gem* gemToDelete);

        void updateBackground(sf::Vector2f scroll, sf::Vector2f playerPos); // move background
        void update();
        void anim();
        void drawMe();

    private:
        sf::RenderWindow* windowPtr;

        // For borders
        sf::Vector2f levelSize;

        // Textures
        sf::Texture grassTextures[7];
        sf::Texture lawnTextures[7];
        sf::Texture gemTextures[7];
        sf::Texture stone;
        sf::Texture backgroundClouds;
        sf::Texture targetTexture;

        // Anim timers and flags
        int gemAnimTimer;
        bool isGemMovesUp;

        sf::Sprite background;
        vector<sf::Sprite> levelTilesVec;
        vector<sf::Sprite> lawnVector;
        void buildLevel();

        // Gem stuff
        vector<sf::Vector2f> gemPositionsVec;
        vector<sf::Vector2f> busyGemPositionsVec;
        vector<sf::Vector2f> freeGemPositionsVec;
        vector<Gem*> gemVec;
        void createGem(sf::Vector2f pos);
        void deleteGem(Gem* gemCollected);
        void updateBusyGemPositionsVec();
        void updateFreeGemPositionsVec();
};