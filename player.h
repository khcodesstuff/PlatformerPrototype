#include <SFML/Graphics.hpp>
#include <time.h>
#include "particles.h"
using namespace std;

class Player{
    public:
        //Constructor
        Player(sf::RenderWindow& window);

        void setIsMovingRight(bool value);
        void setIsMovingLeft(bool value);
        void setVerticalMomentum(float value);
        void setIsFacingForward(bool value);

        int getAirTimer();
        sf::Sprite getSprite();

        void anim();
        void resetAnim();
        void update(vector<sf::Sprite> levelTiles);
        void drawMe();
    
    private:
        sf::RenderWindow* windowPtr;

        // Textures
        sf::Texture idleTexturesRight[8];
        sf::Texture idleTexturesLeft[8];
        sf::Texture moveTexturesRight[8];
        sf::Texture moveTexturesLeft[8];
        sf::Texture jumpTexturesRight[3];
        sf::Texture jumpTexturesLeft[3];
        sf::Sprite sprite;

        // Particles
        vector<Particles*> groundHitParticles;
        void createGroundHitParticles();
        vector<Particles*> walkParticles;
        void createWalkParticles();
        int walkParticleTimer;

        vector<sf::Sprite> checkHit(vector<sf::Sprite> levelTiles);

        // Moving flags
        bool isMovingRight;
        bool isMovingLeft;
        
        // Moving variables
        float verticalMomentum;
        int airTimer;

        // Animation flags
        bool isFacingForward; // 1 - right, 0 - left
        bool canAnimRight;
        bool canAnimLeft;
        int lastAnim; // 1 - idle, 2 - move, 3 - jump

        // Animation vriables
        int textureCounter;
        int animationTimer;

        // Animation
        void idleAnim();
        void moveAnim();
        void jumpAnim();
};