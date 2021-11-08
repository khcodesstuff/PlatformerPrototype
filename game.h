#include <SFML/Graphics.hpp>
#include "player.h"
#include "level.h"
//#include "particles.h"
//#include "gem.h"
#include "doughnut_bar.h"

class Game{
    public:
        // Constructor
        Game(sf::RenderWindow& window);

        Player* player;
        Level* level;
        doughnutBar* doughBar;

        void checkCollidePlayerGem();

        // Particles
        vector<Particles*> collectParicles;
        void createCollectParticles(sf::Vector2f pos);
        
        void updateAll();
        void updateView();
        void updateDoughBar();
        void updateAnimAll();
        void drawAll();

    private:
        sf::RenderWindow* windowPtr;

        sf::Vector2f scroll;
        
        int doughBarTimer;
        int numGemsCollected;
        int totalNumGemsCollected;

        sf::View view;

};