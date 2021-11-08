#include "gem.h"

Gem::Gem(sf::RenderWindow& window, sf::Vector2f pos, string textureColor){
    windowPtr = &window;

    texture.loadFromFile("Textures/"+textureColor+"_gem.png");
    sprite.setTexture(texture);
    sprite.setPosition(pos.x + 4, pos.y); // TODO align
}

sf::Sprite Gem::getSprite(){
    return sprite;
}

void Gem::moveMe(sf::Vector2f value){
    sprite.move(value);
}

void Gem::drawMe(){
    windowPtr->draw(sprite);
}