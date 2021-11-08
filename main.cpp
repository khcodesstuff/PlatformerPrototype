#include <SFML/Graphics.hpp>
#include "game.h"

// TODO properly set fps

int main() {
  sf::RenderWindow window(sf::VideoMode(1200, 800), "GGGame");
  window.setFramerateLimit(60);

  Game* game = new Game(window);
  
  while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Q)
          window.close();
        if (event.key.code == sf::Keyboard::D){
          game->player->setIsMovingRight(true);
          game->player->setIsFacingForward(true);
        }
        if (event.key.code == sf::Keyboard::A){
          game->player->setIsMovingLeft(true);
          game->player->setIsFacingForward(false);
        }
        if (event.key.code == sf::Keyboard::Space){
          if (game->player->getAirTimer() < 3){
            game->player->setVerticalMomentum(-17);
          }
        }
      }

      if (event.type == sf::Event::KeyReleased){
        if (event.key.code == sf::Keyboard::D){
          game->player->setIsMovingRight(false);
        }
        if (event.key.code == sf::Keyboard::A){
          game->player->setIsMovingLeft(false);
        }
      }
    }

    game->updateAll();
    game->updateAnimAll();

    window.clear();
    game->drawAll();

    window.display();
  }
  return 0;
}
