#include <SFML/Graphics.hpp>
#include "player.h"

//Constructor
Player::Player(sf::RenderWindow& window){
    // Parameters init
    windowPtr = &window;

    srand(time(NULL));

    // Loading textures
    idleTexturesRight[0].loadFromFile("Textures/right_hero_idle_0000.png");
    idleTexturesRight[1].loadFromFile("Textures/right_hero_idle_0001.png");
    idleTexturesRight[2].loadFromFile("Textures/right_hero_idle_0002.png");
    idleTexturesRight[3].loadFromFile("Textures/right_hero_idle_0003.png");
    idleTexturesRight[4].loadFromFile("Textures/right_hero_idle_0004.png");
    idleTexturesRight[5].loadFromFile("Textures/right_hero_idle_0005.png");
    idleTexturesRight[6].loadFromFile("Textures/right_hero_idle_0006.png");
    idleTexturesRight[7].loadFromFile("Textures/right_hero_idle_0007.png");
    idleTexturesLeft[0].loadFromFile("Textures/left_hero_idle_0000.png");
    idleTexturesLeft[1].loadFromFile("Textures/left_hero_idle_0001.png");
    idleTexturesLeft[2].loadFromFile("Textures/left_hero_idle_0002.png");
    idleTexturesLeft[3].loadFromFile("Textures/left_hero_idle_0003.png");
    idleTexturesLeft[4].loadFromFile("Textures/left_hero_idle_0004.png");
    idleTexturesLeft[5].loadFromFile("Textures/left_hero_idle_0005.png");
    idleTexturesLeft[6].loadFromFile("Textures/left_hero_idle_0006.png");
    idleTexturesLeft[7].loadFromFile("Textures/left_hero_idle_0007.png");

    moveTexturesRight[0].loadFromFile("Textures/right_hero_move_0000.png");
    moveTexturesRight[1].loadFromFile("Textures/right_hero_move_0001.png");
    moveTexturesRight[2].loadFromFile("Textures/right_hero_move_0002.png");
    moveTexturesRight[3].loadFromFile("Textures/right_hero_move_0003.png");
    moveTexturesRight[4].loadFromFile("Textures/right_hero_move_0004.png");
    moveTexturesRight[5].loadFromFile("Textures/right_hero_move_0005.png");
    moveTexturesRight[6].loadFromFile("Textures/right_hero_move_0006.png");
    moveTexturesRight[7].loadFromFile("Textures/right_hero_move_0007.png");
    moveTexturesLeft[0].loadFromFile("Textures/left_hero_move_0000.png");
    moveTexturesLeft[1].loadFromFile("Textures/left_hero_move_0001.png");
    moveTexturesLeft[2].loadFromFile("Textures/left_hero_move_0002.png");
    moveTexturesLeft[3].loadFromFile("Textures/left_hero_move_0003.png");
    moveTexturesLeft[4].loadFromFile("Textures/left_hero_move_0004.png");
    moveTexturesLeft[5].loadFromFile("Textures/left_hero_move_0005.png");
    moveTexturesLeft[6].loadFromFile("Textures/left_hero_move_0006.png");
    moveTexturesLeft[7].loadFromFile("Textures/left_hero_move_0007.png");

    jumpTexturesRight[0].loadFromFile("Textures/right_hero_jump_0000.png");
    jumpTexturesRight[1].loadFromFile("Textures/right_hero_jump_0001.png");
    jumpTexturesRight[2].loadFromFile("Textures/right_hero_jump_0002.png");
    jumpTexturesLeft[0].loadFromFile("Textures/left_hero_jump_0000.png");
    jumpTexturesLeft[1].loadFromFile("Textures/left_hero_jump_0001.png");
    jumpTexturesLeft[2].loadFromFile("Textures/left_hero_jump_0002.png");
    
    //texture.setSmooth(false);
    //texture.setRepeated(false);

    sprite.setTexture(idleTexturesRight[0]);
    sprite.setPosition(sf::Vector2f(150.f, 150.f));

    // Moving flags
    isMovingRight = false;
    isMovingLeft = false;

    // Moving variables
    verticalMomentum = 0;
    airTimer = 0;

    // Animation flags
    isFacingForward = true;
    canAnimRight = true;
    canAnimLeft = true;
    lastAnim = 1;

    // Animation variables
    textureCounter = 0;
    animationTimer = 0;

    walkParticleTimer = 0;
}

void Player::setIsMovingRight(bool value){
    isMovingRight = value;
}

void Player::setIsMovingLeft(bool value){
    isMovingLeft = value;
}

void Player::setVerticalMomentum(float value){
    verticalMomentum = value;
}

void Player::setIsFacingForward(bool value){
    isFacingForward = value;
}

int Player::getAirTimer(){
    return airTimer;
}

sf::Sprite Player::getSprite(){
    return sprite;
}

void Player::update(vector<sf::Sprite> levelTiles){
    int playerMovementX = 0;
    int playerMovementY = 0;

    if (isMovingRight){
        playerMovementX = 4;
    }
    if (isMovingLeft){
        playerMovementX = -4;
    }

    verticalMomentum += 1.6;
    if (verticalMomentum > 6)
        verticalMomentum = 6;
    playerMovementY += verticalMomentum;

    // Temporary collision side flags
    bool isCollidesTop = false;
    bool isCollidesBottom = false;
    bool isCollidesRight = false;
    bool isCollidesLeft = false;

    vector<sf::Sprite> hitSprites;

    //
    // Align and flag the side of the collision
    //
    // RIGHT / LEFT
    sprite.move(playerMovementX, 0);
    hitSprites = checkHit(levelTiles);

    // Align and flag
    for (sf::Sprite tileRect : hitSprites){
        // right
        if (playerMovementX > 0){
            sprite.setPosition(tileRect.getPosition().x-moveTexturesRight[0].getSize().x, sprite.getPosition().y);
            isCollidesRight = true;
        }
        // left
        else if (playerMovementX < 0){
            sprite.setPosition(tileRect.getPosition().x+tileRect.getTexture()->getSize().x, sprite.getPosition().y);
            isCollidesLeft = true;
        }
    }
    //

    hitSprites.clear();

    // TOP / BOTTOM 
    sprite.move(0, playerMovementY);
    hitSprites = checkHit(levelTiles);
    
    // Align and flag
    for (sf::Sprite tileRect : hitSprites){
        // bottom
        if (playerMovementY > 0){
            sprite.setPosition(sprite.getPosition().x, tileRect.getPosition().y-sprite.getTexture()->getSize().y);
            isCollidesBottom = true;
        }
        // top
        else if (playerMovementY < 0){
            sprite.setPosition(sprite.getPosition().x, tileRect.getPosition().y+tileRect.getTexture()->getSize().y);
            isCollidesTop = true;        
        }
    }
    //

    // Update stuff based on collision side
    if (isCollidesTop)
        verticalMomentum = 4; // instant falling
    if (isCollidesBottom){
        airTimer = 0;
        verticalMomentum = 0;
    }
    else{
        airTimer += 1;
    }
    if (isCollidesRight)
        canAnimRight = false;
    else
        canAnimRight = true;
    if (isCollidesLeft)
        canAnimLeft = false;
    else
        canAnimLeft = true;

    // Particles
    if ((isMovingRight || isMovingLeft) && airTimer == 0){
        if (walkParticleTimer > 12){
            walkParticleTimer = 0;
            createWalkParticles();
        }
        walkParticleTimer++;
    }
}

void Player::createGroundHitParticles(){
    // Setting up texture names vector
    vector<string> groundHitParticlesStr;
    groundHitParticlesStr.push_back("ground_hit_partic_0000.png");
    groundHitParticlesStr.push_back("ground_hit_partic_0001.png");
    groundHitParticlesStr.push_back("ground_hit_partic_0002.png");
    
    sf::Vector2f pos;
    // Align position based on facing direction
    if (isFacingForward)
        pos = sf::Vector2f(sprite.getPosition().x-2, sprite.getPosition().y+24);
    else if (!isFacingForward)
        pos = sf::Vector2f(sprite.getPosition().x-6, sprite.getPosition().y+24);

    Particles* particles = new Particles(*windowPtr, pos, groundHitParticlesStr);
    groundHitParticles.push_back(particles);
}

void Player::createWalkParticles(){
    // Setting up texture names vector
    vector<string> walkParticlesStr;
    // Particles based on position
    if (isFacingForward){
        walkParticlesStr.push_back("right_walk_partic_0000.png");
        walkParticlesStr.push_back("right_walk_partic_0001.png");
    }
    else if (!isFacingForward){
        walkParticlesStr.push_back("left_walk_partic_0000.png");
        walkParticlesStr.push_back("left_walk_partic_0001.png");
    }

    Particles* particles = new Particles(*windowPtr, sf::Vector2f(sprite.getPosition().x-2, sprite.getPosition().y+22), walkParticlesStr);
    walkParticles.push_back(particles);
}

vector<sf::Sprite> Player::checkHit(vector<sf::Sprite> levelTiles){
    vector<sf::Sprite> hitSprites;
    for(sf::Sprite tile : levelTiles){
        if (sprite.getGlobalBounds().intersects(tile.getGlobalBounds()))
            hitSprites.push_back(tile);
    }
    return hitSprites;
}

void Player::anim(){
    // PARTICLES
    if (groundHitParticles.size() != 0){
        for (Particles* particles : groundHitParticles){
            if (particles->anim()) // remove particles if animation ended
                groundHitParticles.erase(remove(groundHitParticles.begin(), groundHitParticles.end(), particles), groundHitParticles.end());
        }
    }
    if (walkParticles.size() != 0){
        for (Particles* particles : walkParticles){
            if (particles->anim()) // remove particles if animation ended
                walkParticles.erase(remove(walkParticles.begin(), walkParticles.end(), particles), walkParticles.end());
        }
    }

    // JUMP
    if (airTimer > 0){
        // Instant change of textures
        if (lastAnim != 3){
            resetAnim();
            lastAnim = 3;
            textureCounter = rand() % 2; // for random first texture
        }

        jumpAnim();
        return;
    }

    // IDLE
    if (!isMovingRight && !isMovingLeft){
        // Instant change of textures
        if (lastAnim != 1){
            if (lastAnim == 3){
                createGroundHitParticles();
            }
            resetAnim();
            lastAnim = 1;
        }

        idleAnim();
        return;
    }

    // MOVE
    if ((isMovingRight && canAnimRight) || (isMovingLeft && canAnimLeft)){
        // Instant change of textures
        if (lastAnim != 2){
            if (lastAnim == 3){
                createGroundHitParticles();
            }
            resetAnim();
            lastAnim = 2;
        }

        moveAnim();
        return;
    }
}

void Player::idleAnim(){
    if (textureCounter > 5){
        textureCounter = 0;
    }
    if (animationTimer > 10){
        animationTimer = 0;
        if (isFacingForward){
            sprite.setTexture(idleTexturesRight[textureCounter]);
        }
        else if (!isFacingForward){
            sprite.setTexture(idleTexturesLeft[textureCounter]);
        }
        textureCounter++;
    }
    animationTimer++;
}

void Player::moveAnim(){
    if (textureCounter > 7){
        textureCounter = 0;
    }
    if (animationTimer > 3){
        animationTimer = 0;
        if (isFacingForward){
            sprite.setTexture(moveTexturesRight[textureCounter]);
        }
        else if (!isFacingForward){
            sprite.setTexture(moveTexturesLeft[textureCounter]);
        }
        textureCounter++;
    }
    animationTimer++;
}

void Player::jumpAnim(){
    if (textureCounter > 2){
        textureCounter = 0;
    }
    if (animationTimer > 6){
        animationTimer = 0;
        if (isFacingForward){
            sprite.setTexture(jumpTexturesRight[textureCounter]);
        }
        else if (!isFacingForward){
            sprite.setTexture(jumpTexturesLeft[textureCounter]);
        }
        textureCounter++;
    }
    animationTimer++;
}

void Player::resetAnim(){
    textureCounter = 0;
    animationTimer = 100;
    walkParticleTimer = 100;
}

void Player::drawMe(){
    windowPtr->draw(sprite);
    // Draw particles, if any
    if (groundHitParticles.size() != 0){
        for (Particles* particles : groundHitParticles)
            particles->drawMe();
    }
    if (walkParticles.size() != 0){
        for (Particles* particles : walkParticles)
            particles->drawMe();
    }
}

