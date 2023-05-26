#include "Game.h"
#include "LevelLoader.h"

vector<EntityNature> Game::validEntities {EntityNature::BABA, EntityNature::FLAG, EntityNature::GRASS, EntityNature::METAL, EntityNature::ROCK, EntityNature::WALL, EntityNature::WATER, EntityNature::LAVA};

Game::Game() : currentLevel{0}, board{LevelLoader::levelLoad(0) } {
    scanRule();
}

void Game::constructLevel(int num){
    currentLevel = num;
    this->board = LevelLoader::levelLoad(num);
    scanRule();
    notifyObservers();
}

void Game::scanRule() {
    rules.clear();
    Rule limitRule{EntityNature::LIMIT, EntityNature::IS, EntityNature::STOP};
    rules.push_back(limitRule);

    for (int i = 1; i < board.getHeight() - 1; ++i) {
        for (int j = 1; j < board.getWidth() - 1; ++j) {
            Position pos{i, j};
            vector<Entity> entities{board.getEntities(pos)};

            for (int k = 0; k < entities.size(); ++k) {
                if (entities[k].getNature() == EntityNature::IS) {
                    checkVerticalRule(pos);
                    checkHorizontalRule(pos);
                }
            }
        }
    }
}

void Game::checkVerticalRule(const Position& pos) {
    Position posUp{pos.next(Direction::UP)};
    vector<Entity> entitiesUp{board.getEntities(posUp)};

    for (Entity entityUp : entitiesUp) {
        if (entityUp.getType() == EntityType::TEXT && count(validEntities.begin(), validEntities.end(), entityUp.getNature())) {
            Position posDown{pos.next(Direction::DOWN)};
            vector<Entity> entitiesDown{board.getEntities(posDown)};

            for (Entity entityDown : entitiesDown) {
                if (entityDown.getType() == EntityType::TEXT && !(entityDown.getNature() == EntityNature::IS)) {
                    Rule rule {entityUp.getNature(), EntityNature::IS, entityDown.getNature()};
                    rules.push_back(rule);
                }
            }
        }
    }
}

void Game::checkHorizontalRule(const Position& pos) {
    Position posLeft{pos.next(Direction::LEFT)};
    vector<Entity> entitiesLeft{board.getEntities(posLeft)};

    for (Entity entityLeft : entitiesLeft) {
        if (entityLeft.getType() == EntityType::TEXT && count(validEntities.begin(), validEntities.end(), entityLeft.getNature())) {
            Position posRight{pos.next(Direction::RIGHT)};
            vector<Entity> entitiesRight{board.getEntities(posRight)};

            for (Entity entityRight : entitiesRight) {
                if (entityRight.getType() == EntityType::TEXT && !(entityRight.getNature() == EntityNature::IS)) {
                    Rule rule {entityLeft.getNature(), EntityNature::IS, entityRight.getNature()};
                    rules.push_back(rule);
                }
            }
        }
    }
}

void Game::move(Direction dir){
    vector<EntityNature> entitiesPlayer,entitiesPush, entitiesStop;
    bool hasBeenFound = false;
    //going through each rule
    for(const Rule & rule : rules){
        if(rule.getObject() == EntityNature::YOU){
            //get all the entities that represents the actual player
            entitiesPlayer.push_back(rule.getSubject());
            hasBeenFound = true;
        }
        else if(rule.getObject() == EntityNature::STOP){
            //get all the entities that stops all the entities
            entitiesStop.push_back(rule.getSubject());
        }
        else if(rule.getObject() == EntityNature::PUSH){
            //get all the entities that are pushable
            entitiesPush.push_back(rule.getSubject());
        }
    }
    if(hasBeenFound){
        //go through the whole board to find an element playable
        vector<pair<Entity,Position>> movePlayers;
        for (int i = 1; i < board.getHeight()-1; ++i) {
            for (int j = 1; j < board.getWidth()-1; ++j) {

                Position pos {i,j};
                vector<Entity> entities = board.getEntities(pos);

                for (Entity entity : entities) {
                    if(entity.getType()==EntityType::ELEMENT && count(entitiesPlayer.begin(), entitiesPlayer.end(), entity.getNature())){
                        //stop the move
                        bool stop = false;
                        //valid the move
                        bool ok = false;
                        //index of the free square if there are elements to push
                        int cpt = 1;
                        Position next{pos.next(dir)};
                        while(!stop && !ok){
                            vector<Entity> nextEntities = board.getEntities(next);
                            if(!nextEntities.empty()){
                                for (Entity nextEntity : nextEntities) {
                                    if(count(entitiesStop.begin(),entitiesStop.end(),nextEntity.getNature()) && !(nextEntity.getType()==EntityType::TEXT)){
                                        stop = true;
                                    }
                                    else if(count(entitiesPush.begin(),entitiesPush.end(),nextEntity.getNature())==0 && !(nextEntity.getType()==EntityType::TEXT)){
                                        ok = true;
                                    }
                                    else{
                                        next = next.next(dir);
                                        cpt++;
                                    }
                                }
                            }else{
                                ok = true;
                            }
                        }
                        //if you are not blocked
                        if(!stop){
                            while (cpt>1) {
                                Position pos1 = pos;
                                for (int k = 0; k < cpt; ++k) {
                                    pos1 = pos1.next(dir);
                                }
                                Position pos2 = pos;
                                for (int k = 0; k < cpt-1; ++k) {
                                    pos2 = pos2.next(dir);
                                }
                                vector<Entity> lol = board.getEntities(pos2);
                                for (Entity l : lol) {
                                    if(count(entitiesPush.begin(),entitiesPush.end(),l.getNature()) || l.getType()==EntityType::TEXT){
                                        board.addEntity(pos1,l);
                                        board.dropEntity(pos2,l);
                                    }
                                }
                                cpt--;
                            }
                            //move the player later
                            movePlayers.push_back(make_pair(entity,pos));
                        }
                    }
                }
            }
        }
        //move the player
        if(dir==Direction::LEFT || dir==Direction::UP){
            for (int i = 0; i < movePlayers.size(); ++i) {
                pair<Entity,Position> mp = movePlayers[i];
                board.addEntity(mp.second.next(dir),mp.first);
                board.dropEntity(mp.second,mp.first);
            }
        }
        if(dir==Direction::RIGHT || dir==Direction::DOWN){
            for (int i = movePlayers.size()-1; i >= 0; --i) {
                pair<Entity,Position> mp = movePlayers[i];
                board.addEntity(mp.second.next(dir),mp.first);
                board.dropEntity(mp.second,mp.first);
            }
        }
        //verify the rules (create, or delete)
        scanRule();
        transformation();
        isSink();
        isKill();
        notifyObservers();
    }
}

void Game::transformation(){
    //the entities that aren't eligble to be transformed
    static vector<EntityNature> exceptEntities {EntityNature::IS,EntityNature::KILL,EntityNature::PUSH,EntityNature::STOP,EntityNature::YOU,EntityNature::SINK,EntityNature::WIN};
    //going through each active rule
    for (Rule rule : rules) {
        if(count(exceptEntities.begin(),exceptEntities.end(),rule.getObject())==0){
            for (int i = 0; i < board.getHeight(); ++i) {
                for (int j = 0; j < board.getWidth(); ++j) {
                    Position pos{i,j};
                    vector<Entity> entities = board.getEntities(pos);
                    for (Entity entity : entities) {
                        if(entity.getType()==EntityType::ELEMENT && entity.getNature()==rule.getSubject()){
                            //replace each transformed element to his new nature
                            board.dropEntity(pos,entity);
                            board.addEntity(pos,Entity{rule.getObject(),EntityType::ELEMENT});
                        }
                    }
                }
            }
        }
    }
}

void Game::isSink(){
    vector<EntityNature> entitiesSink;
    bool foundSink = false;
    for(Rule rule : rules){
        if(rule.getObject() == EntityNature::SINK){
            entitiesSink.push_back(rule.getSubject());
            foundSink = true;
        }
    }
    if(foundSink){
        for (int i = 1; i < board.getHeight()-1; ++i) {
            for (int j = 1; j < board.getWidth()-1; ++j) {
                Position pos{i,j};
                vector<Entity> entities = board.getEntities(pos);
                bool drown{false};
                for (int k = 0; k < entities.size() && !drown; ++k) {
                    drown = entities[k].getType()==EntityType::ELEMENT
                            && count(entitiesSink.begin(),entitiesSink.end(),entities[k].getNature())
                            && entities.size()>1;
                }
                if(drown){
                    for (Entity entity : entities) {
                        //when an element comes in contact with a element with the active sink rule
                        //the elements disappear
                        board.dropEntity(pos,entity);
                    }
                }
            }
        }
    }
}

void Game::isKill(){
    vector<EntityNature> entitiesPlayer,entitiesKill;
    bool foundPlayers = false;
    bool foundKill = false;
    //check if there is an active rule about killing
    for(Rule rule : rules){
        if(rule.getObject() == EntityNature::YOU){
            entitiesPlayer.push_back(rule.getSubject());
            foundPlayers = true;
        }
        else if(rule.getObject() == EntityNature::KILL){
            entitiesKill.push_back(rule.getSubject());
            foundKill = true;
        }
    }
    //if there is an active rule about killing and that there is also playable elements
    //go through the whole board
    if(foundPlayers && foundKill){
        for (int i = 1; i < board.getHeight()-1; ++i) {
            for (int j = 1; j < board.getWidth()-1; ++j) {
                Position pos{i,j};
                vector<Entity> entities = board.getEntities(pos);
                bool kill = false;                
                for (int k = 0; k < entities.size() && !kill; ++k) {
                    kill = entities[k].getType()==EntityType::ELEMENT
                            && count(entitiesKill.begin(),entitiesKill.end(),entities[k].getNature());
                }
                if(kill){
                    for (Entity entity : entities) {
                        if(entity.getType()==EntityType::ELEMENT
                                && count(entitiesPlayer.begin(),entitiesPlayer.end(),entity.getNature())){
                            board.dropEntity(pos,entity);
                        }
                    }
                }
            }
        }
    }
}

bool Game::isWin(){
    bool res = false;
    vector<EntityNature> entitiesPlayer,entitiesWin;
    bool foundPlayers = false;
    bool foundWin = false;
    //check if there is an active rule about winning
    for(Rule rule : rules){
        if(rule.getObject() == EntityNature::YOU){
            entitiesPlayer.push_back(rule.getSubject());
            foundPlayers = true;
        }
        else if(rule.getObject() == EntityNature::WIN){
            entitiesWin.push_back(rule.getSubject());
            foundWin = true;
        }
    }
    //if there is an active rule about winning and that there is also playable elements
    //go through the whole board
    if(foundPlayers && foundWin){
        for (int i = 1; i < board.getHeight()-1 && !res; ++i) {
            for (int j = 1; j < board.getWidth()-1 && !res; ++j) {
                Position pos{i,j};
                vector<Entity> entities = board.getEntities(pos);
                bool ok1 = false;
                bool ok2 = false;
                //check each element on each box of the board
                for (Entity entity : entities) {
                    //if he finds that the nature of the element is equal to the element nature eligble
                    //for the win boolean goes true
                    if(entity.getType()==EntityType::ELEMENT && count(entitiesPlayer.begin(),entitiesPlayer.end(),entity.getNature())){
                        ok1=true;
                    }
                    //if he finds that the playable element is on the nature of the element causing the
                    //win, then the boolean goes true
                    if(entity.getType()==EntityType::ELEMENT && count(entitiesWin.begin(),entitiesWin.end(),entity.getNature())){
                        ok2=true;
                    }
                }
                res = ok1 && ok2;
            }
        }
    }
    return res;
}


void Game::saveLevel(){
    LevelLoader::saveLevel(board,currentLevel);
}

void Game::reloadLevel(){
    pair<Board,int> p = LevelLoader::reloadLevel();
    board = p.first;
    currentLevel = p.second;
    scanRule();
    notifyObservers();
}

void Game::restartLevel(){
    constructLevel(currentLevel);
    notifyObservers();
}

int Game::getCurrentLevel() const{
    return currentLevel;
}

int Game::getBoardHeight() const{
    return board.getHeight();
}
int Game::getBoardWidth() const{
    return board.getWidth();
}
const vector<Entity>& Game::getBoardEntities(Position pos) const{
    return board.getEntities(pos);
}
