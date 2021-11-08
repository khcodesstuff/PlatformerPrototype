#include "doughnut_bar.h"

doughnutBar::doughnutBar(sf::RenderWindow& window){
    windowPtr = &window;

    textures[0].loadFromFile("Textures/doughnut_bar_1.png");
    textures[1].loadFromFile("Textures/doughnut_bar_2.png");
    textures[2].loadFromFile("Textures/doughnut_bar_3.png");
    textures[3].loadFromFile("Textures/doughnut_bar_4.png");
    textures[4].loadFromFile("Textures/doughnut_bar_5.png");
    textures[5].loadFromFile("Textures/doughnut_bar_6.png");
    textures[6].loadFromFile("Textures/doughnut_bar_7.png");
    textures[7].loadFromFile("Textures/doughnut_bar_8.png");
    textures[8].loadFromFile("Textures/doughnut_bar_9.png");
    textures[9].loadFromFile("Textures/doughnut_bar_10.png");
    
    barValue = 10;
    sprite.setTexture(textures[barValue-1]);
    sprite.setPosition(sf::Vector2f(0, 0));
}

sf::Sprite doughnutBar::getSprite(){
    return sprite;
}

int doughnutBar::getValue(){
    return barValue;
}

void doughnutBar::setPosition(sf::Vector2f pos){
    sprite.setPosition(pos);
}

void doughnutBar::setValue(int val){
    barValue = val;
    printf("%i\n", barValue);
    sprite.setTexture(textures[barValue-1]);
}

void doughnutBar::drawMe(){
    windowPtr->draw(sprite);
}