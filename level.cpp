#include "level.h"

// Constructor
Level::Level(sf::RenderWindow& window){
    windowPtr = &window;
    srand(time(NULL));

    // Loading textures
    if (!backgroundClouds.loadFromFile("Textures/sky.png")){
        printf("Couldnt load sky texture");
    }

    grassTextures[0].loadFromFile("Textures/red_grass.png");
    grassTextures[1].loadFromFile("Textures/orange_grass.png");
    grassTextures[2].loadFromFile("Textures/yellow_grass.png");
    grassTextures[3].loadFromFile("Textures/green_grass.png");
    grassTextures[4].loadFromFile("Textures/blue_grass.png");
    grassTextures[5].loadFromFile("Textures/d_blue_grass.png");
    grassTextures[6].loadFromFile("Textures/purple_grass.png");

    lawnTextures[0].loadFromFile("Textures/red_lawn.png");
    lawnTextures[1].loadFromFile("Textures/orange_lawn.png");
    lawnTextures[2].loadFromFile("Textures/yellow_lawn.png");
    lawnTextures[3].loadFromFile("Textures/green_lawn.png");
    lawnTextures[4].loadFromFile("Textures/blue_lawn.png");
    lawnTextures[5].loadFromFile("Textures/d_blue_lawn.png");
    lawnTextures[6].loadFromFile("Textures/purple_lawn.png");

    gemTextures[0].loadFromFile("Textures/red_gem.png");
    gemTextures[1].loadFromFile("Textures/orange_gem.png");
    gemTextures[2].loadFromFile("Textures/yellow_gem.png");
    gemTextures[3].loadFromFile("Textures/green_gem.png");
    gemTextures[4].loadFromFile("Textures/blue_gem.png");
    gemTextures[5].loadFromFile("Textures/d_blue_gem.png");
    gemTextures[6].loadFromFile("Textures/purple_gem.png");


    if (!stone.loadFromFile("Textures/stone_small.png")){
        printf("Couldn't load stone texture");
    }
    if (!targetTexture.loadFromFile("Textures/target.png")){
        printf("Couldn't load target texture");
    }

    gemAnimTimer = 0;
    isGemMovesUp = true;

    // Building level
    buildLevel();
}

void Level::buildLevel(){
    string levelStr[] = {
    "S                                                           S",
    "S            G                                              S",
    "S          GBB                                GGG           S",
    "S          B                        G  G     BBBBB   G      S",
    "S     G             G     GG      BBBBBBBB    SSS           S",
    "S     BB         G  B   BBBBBB     SSSSSS            G      S",
    "S             G  B        SS                                S",
    "S             B                                             S",
    "S      GGBB         G                               GG      S",
    "S      BBSSB        B                              BBBB     S",
    "S GB          BB          G G                               S",
    "SBBSB                    BBBBB         G       G          G S",
    "SSSSSB   BB   G  G    BBBSSSSSB    G       G       G     BBBS",
    "SSSSSSBBBSSBBBBBBBBBBBSSSSSSSSSBBBBBBBBBBBBBBBBBBBBBBBBBBSSSS",
    "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"
    };

    // Building
    vector<sf::Sprite> lvl;

    int rainbowGrassCounter = 0;
    int rainbowLenCounter = 0;

    float x = -24;
    float y = 0;
    for(int i = 0; i < (sizeof(levelStr)/sizeof(levelStr[0])); i++){
        string row = levelStr[i];
        for(int j = 0; j < row.size(); j++){
            if (rainbowGrassCounter > 6)
                rainbowGrassCounter = 0;
            if (row[j] == 'B'){
                sf::Sprite tile;
                tile.setTexture(grassTextures[rainbowGrassCounter]);
                tile.setPosition(sf::Vector2f(x, y));
                levelTilesVec.push_back(tile);
                sf::Sprite lawn;
                lawn.setTexture(lawnTextures[rainbowGrassCounter]);
                lawn.setPosition(sf::Vector2f(x, y-8));
                lawnVector.push_back(lawn);
            }
            else if (row[j] == 'S'){
                sf::Sprite tile;
                tile.setTexture(stone);
                tile.setPosition(sf::Vector2f(x, y));
                levelTilesVec.push_back(tile);
            }
            else if (row[j] == 'G'){
                gemPositionsVec.push_back(sf::Vector2f(x, y));
            }
            x += 24;
            rainbowLenCounter++;
            if (rainbowLenCounter > 1){
                rainbowLenCounter = 0;
                rainbowGrassCounter++;
            }
        }
        rainbowLenCounter = 0;
        rainbowGrassCounter = rand() % 6;
        y += 24;
        x = -24;
    }

    levelSize.x = levelStr[0].size()*24;
    levelSize.y = sizeof(levelStr)/sizeof(levelStr[0])*24;

    //printf("%i\n", levelStr[0].size());
    //printf("%f", levelSize.x);

    background.setTexture(backgroundClouds);
    background.setPosition(sf::Vector2f(0, -200));

    // Creating 20 gems for the first time
    for (int i = 0; i < 20; i++){
        // Choosing position
        sf::Vector2f pos;
        if (busyGemPositionsVec.size() == 0){
            pos = gemPositionsVec[rand()%gemPositionsVec.size()];
        }
        else if (busyGemPositionsVec.size() > 0){
            //pos = chooseFreeGemPosition();
            pos = freeGemPositionsVec[rand()%freeGemPositionsVec.size()];
        }

        createGem(pos);
        updateBusyGemPositionsVec();
        updateFreeGemPositionsVec();
        //busyGemPositionsVec.push_back(pos);
    }
}

sf::Vector2f Level::getLevelSize(){
    return levelSize;
}

vector<sf::Sprite> Level::getLevelTiles(){
    return levelTilesVec;
}

vector<Gem*> Level::getGems(){
    return gemVec;
}

void Level::deleteRecreateGem(Gem* gemToDelete){
    deleteGem(gemToDelete);
    updateBusyGemPositionsVec(); // allows to exclude deleted gem position, making this position available (erasing it from vec doesn't work)
    updateFreeGemPositionsVec();
    sf::Vector2f pos = freeGemPositionsVec[rand()%freeGemPositionsVec.size()];
    createGem(pos);
    updateBusyGemPositionsVec();
    updateFreeGemPositionsVec();
    //busyGemPositionsVec.push_back(pos);
}

void Level::createGem(sf::Vector2f pos){
    // Choosing gem color
    string color = "";
    int rainbow = rand()%7;
    if (rainbow == 0)
        color = "red";
    else if (rainbow == 1)
        color = "orange";
    else if (rainbow == 2)
        color = "yellow";
    else if (rainbow == 3)
        color = "green";
    else if (rainbow == 4)
        color = "blue";
    else if (rainbow == 5)
        color = "d_blue";
    else if (rainbow == 6)
        color = "purple";

    Gem* gem = new Gem(*windowPtr, pos, color);

    gemVec.push_back(gem);
}

void Level::deleteGem(Gem* gemCollected){
    for(Gem* gemOrig : gemVec){
        gemVec.erase(remove(gemVec.begin(), gemVec.end(), gemCollected), gemVec.end());
    }
}

void Level::updateBusyGemPositionsVec(){
    // Erase all positions and refill the vector again
    busyGemPositionsVec.clear();
    for (Gem* gem : gemVec){
        busyGemPositionsVec.push_back(gem->getSprite().getPosition());
    }
}

void Level::updateFreeGemPositionsVec(){
    // Erase and refill
    freeGemPositionsVec.clear();

    bool isFree = true;
    for (int i = 0; i < gemPositionsVec.size(); i++){
        // Check if gem position is free
        for (int k = 0; k < busyGemPositionsVec.size(); k++){
            if (gemPositionsVec[i] == busyGemPositionsVec[k]){
                isFree == false;
                break;
            }
        }

        // Add to vector if position is free
        if (isFree){
            freeGemPositionsVec.push_back(gemPositionsVec[i]);
        }
    }
}

void Level::updateBackground(sf::Vector2f scroll, sf::Vector2f playerPos){
    //sf::Vector2f playerMovement;
    //playerMovement.x = background.getPosition().x+960 - playerPos.x+8;

    //background.move(playerMovement.x-scroll.x, 0);
    
    
    //background.setPosition(playerPos.x+8-scroll.x*2-960, playerPos.y+16-scroll.y*2-540);

    // Up limit
    //if (background.getPosition().y < 20 + 540){
    //    background.setPosition(background.getPosition().x, 20.f-540.f);
    //}
    
    
    //TODO doesn't work
    //background.setPosition(playerPos.x-3000, playerPos.y-1050);

    //float diffX = playerPos.x-background.getPosition().x+1000;
    //float diffY = playerPos.y-background.getPosition().y+350;
    //printf("(%f, %f)", diffX, diffY);

    //background.move(sf::Vector2f(diffX-1000, diffY+350));
    //printf("BG POS:(%f, %f)", background.getPosition().x, background.getPosition().y);
}

void Level::anim(){
    // TARGETS (maybe refactor later)
    if (gemAnimTimer > 15){
        gemAnimTimer = 0;
        // Moving up
        if (isGemMovesUp){
            for (Gem* gem : gemVec){ // &
                gem->moveMe(sf::Vector2f(0.f, -5.f));
            }
            isGemMovesUp = !isGemMovesUp;
        }
        // Moving down
        else if (!isGemMovesUp){
            for (Gem* gem : gemVec){
                gem->moveMe(sf::Vector2f(0.f, 5.f));
            }
            isGemMovesUp = !isGemMovesUp;
        }
    }
    gemAnimTimer++;
}

void Level::drawMe(){
    windowPtr->draw(background);
    for (sf::Sprite tile : levelTilesVec){
        windowPtr->draw(tile);
    }
    for (Gem* gem : gemVec){
        gem->drawMe();
    }
    for (sf::Sprite lawn : lawnVector){
        windowPtr->draw(lawn);
    }
}