#include <SFML/Graphics.hpp>
#include "game.h"

// Constructor
Game::Game(sf::RenderWindow& window){
    windowPtr = &window;

    player = new Player(*windowPtr);
    level = new Level(*windowPtr);

    view = sf::View(sf::Vector2f(player->getSprite().getPosition().x+8, player->getSprite().getPosition().y+16), sf::Vector2f(windowPtr->getSize().x/2, windowPtr->getSize().y/2));
    window.setView(view);

    doughBar = new doughnutBar(*windowPtr);

    scroll.x = 0;
    scroll.y = 0;

    doughBarTimer = 0;
    numGemsCollected = 0;
    totalNumGemsCollected = 0;
}

void Game::checkCollidePlayerGem(){ // *************************** CREATES GEMS IN BUSY POSITIONS :( *************************** //
    // PLAYER/GEMS
    vector <Gem*> gemVec = level->getGems();
    for (Gem* gem : gemVec){
        if (player->getSprite().getGlobalBounds().intersects(gem->getSprite().getGlobalBounds())){
            level->deleteRecreateGem(gem);
            createCollectParticles(gem->getSprite().getPosition());
            numGemsCollected++;
            totalNumGemsCollected++;
            printf("GEMS: %i\n", numGemsCollected);
            //printf("TOTAL GEMS: %i\n", totalNumGemsCollected);
        }
    }
}

void Game::createCollectParticles(sf::Vector2f pos){
    // Setting up texture names vector
    vector<string> collectParticlesStr;
    collectParticlesStr.push_back("gem_collected_0000.png");
    collectParticlesStr.push_back("gem_collected_0001.png");
    collectParticlesStr.push_back("gem_collected_0002.png");
    collectParticlesStr.push_back("gem_collected_0003.png");

    Particles* particles = new Particles(*windowPtr, pos, collectParticlesStr);
    collectParicles.push_back(particles);
}

void Game::updateAll(){
    player->update(level->getLevelTiles());
    updateView();
    updateDoughBar();
    checkCollidePlayerGem();
    level->updateBackground(scroll, player->getSprite().getPosition());
}

void Game::updateView(){
    // Smooth scrolling
    scroll.x = player->getSprite().getPosition().x+8 - view.getCenter().x - scroll.x / 10;
    scroll.y = player->getSprite().getPosition().y+16 - view.getCenter().y - scroll.y / 10;
    // Explanation
    //printf("Scroll x: %f\n", scroll.x);
    //printf("C: %f\n", player->getSprite().getPosition().x+8);
    //printf("V: %f\n", view.getCenter().x);

    // Update the view based on player position
    view.setCenter(player->getSprite().getPosition().x+8-scroll.x, player->getSprite().getPosition().y+16-scroll.y); // TODO tweak a bit
    
    // Left limit
    if (view.getCenter().x < view.getSize().x/2)
        view.setCenter(view.getSize().x/2, view.getCenter().y);
    // Right limit
    if (view.getCenter().x > (level->getLevelSize().x - view.getSize().x/2 - 24*2))
        view.setCenter(level->getLevelSize().x - view.getSize().x/2 - 24*2, view.getCenter().y);
    // Up limit
    if (view.getCenter().y < 20)
        view.setCenter(view.getCenter().x, 20.f);
    // Down limit
    if (view.getCenter().y > 150)
        view.setCenter(view.getCenter().x, 150);

    windowPtr->setView(view);
}

void Game::updateDoughBar(){
    // Update bar's position relatively to view's center
    doughBar->setPosition(sf::Vector2f(view.getCenter().x-60, view.getCenter().y+170));

    // Decrease
    if (doughBarTimer > 100){ // TODO make 10 dynamic
        doughBarTimer = 0;

        if (doughBar->getValue() > 1){
            doughBar->setValue(doughBar->getValue()-1);
        }
    }
    doughBarTimer++;

    // Increase
    if (doughBar->getValue() <= 8 && numGemsCollected > 2){
        doughBar->setValue(doughBar->getValue()+2);
        doughBarTimer = 0;
        numGemsCollected = 0;
    }
    else if (doughBar->getValue() == 9 && numGemsCollected > 2){
        doughBar->setValue(doughBar->getValue()+1);
        doughBarTimer = 0;
        numGemsCollected = 0;
    }
    else if (doughBar->getValue() == 10 && numGemsCollected > 2){
        numGemsCollected = 0;
    }
}

void Game::updateAnimAll(){
    player->anim();
    level->anim();

    // Particles
    if (collectParicles.size() >= 0){
        for (Particles* particles : collectParicles){
            if (particles->anim()) // // remove particles if animation ended
                collectParicles.erase(remove(collectParicles.begin(), collectParicles.end(), particles), collectParicles.end());
        }
    }
}

void Game::drawAll(){
    level->drawMe();
    player->drawMe();

    // Particles
    if (collectParicles.size() >= 0){
        for (Particles* particles : collectParicles){
            particles->drawMe();
        }
    }

    doughBar->drawMe();
}