#include <SFML/Graphics.hpp>
#include "particles.h"

Particles::Particles(sf::RenderWindow& window, sf::Vector2f pos, vector<string> texturesStr){
    // Parameters init
    windowPtr = &window;

    // Load textures
    for (int i = 0; i < texturesStr.size(); i ++){
        sf::Texture texture;
        texture.loadFromFile("Textures/"+texturesStr[i]);
        texturesVector.push_back(texture);
    }

    sprite.setTexture(texturesVector[0]);
    sprite.setPosition(pos);

    animTimer = 0;
    textureCounter = 1;
}

int Particles::anim(){
    if (textureCounter >= texturesVector.size())
        return 1; // end and delete particles object when animation ends (when all textures were shown)
    if (animTimer > 3){ // default is 7 *changed!*, 3 is better
        animTimer = 0;
        sprite.setTexture(texturesVector[textureCounter]);
        textureCounter++;
    }
    animTimer++;
    return 0;
}

void Particles::drawMe(){
    windowPtr->draw(sprite);
}