#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Position.h"
#include "LevelLoader.h"
#include "Rule.h"
#include <map>

class Game{
    private:
        Board board;
        vector<Rule> rules;
        bool levelOver;
        bool gameOver;
        int currentLevel;

        inline string entityToString(Entity entity);
        inline void scanRule();
    public:
        inline Game();
        inline void constructLevel(int num);
        inline void move(Direction dir);
        inline bool isGameOver();
        inline bool isLevelOver();
        inline void saveLevel();
        inline void reloadLevel();
        inline bool isBlocking(Position pos);
        inline Board getBoard();
};

Game::Game() : currentLevel{0}, board{LevelLoader::levelLoad(0)}, levelOver{false}, gameOver{false} {
    scanRule();
}

void Game::constructLevel(int num){
    currentLevel = num;
    levelOver = false;
    this->board = LevelLoader::levelLoad(num);
    scanRule();
}
void Game::move(Direction dir){
    EntityNature player;
    bool hasBeenFound = false;
    for(Rule rule : rules){
        if(rule.getObject() == EntityNature::YOU && !hasBeenFound){
            player = rule.getSubject();
            hasBeenFound = true;
        }
    }
    if(hasBeenFound){
        for (int i = 1; i < board.getHeight()-1; ++i) {
            for (int j = 1; j < board.getWidth()-1; ++j) {
                Position pos {i,j};
                Position nextPos = pos.next(dir);
                vector<Entity> entities = board.getEntities(pos);
                for(Entity entity : entities){
                    if(entity.getType() == EntityType::ELEMENT && entity.getNature() == player){
                        vector<Entity> nextEntities = board.getEntities(nextPos);
                        vector<pair<Entity, Position>> moovable;
                        if(isBlocking(nextPos)){
                            break;
                        } else {
                            moovable.push_back(pair<Entity, Position> {entity, pos});
                            while (!nextEntities.empty()) {
                                if(!isBlocking(nextPos)){
                                    bool pushable = false;
                                    for (Entity nextEntity : nextEntities) {
                                        for(Rule rule : rules){
                                            if(nextEntity.getType() == EntityType::TEXT
                                                    || (rule.getSubject() == nextEntity.getNature()
                                                        && rule.getObject() == EntityNature::PUSH)){
                                                pushable = true;
                                                nextPos = nextPos.next(dir);
                                                nextEntities = board.getEntities(nextPos);
                                                switch(dir){
                                                case Direction::DOWN:
                                                    moovable.push_back(pair<Entity, Position> {nextEntity, nextPos.next(Direction::UP)});
                                                    break;
                                                case Direction::UP:
                                                    moovable.push_back(pair<Entity, Position> {nextEntity, nextPos.next(Direction::DOWN)});
                                                    break;
                                                case Direction::LEFT:
                                                    moovable.push_back(pair<Entity, Position> {nextEntity, nextPos.next(Direction::RIGHT)});
                                                    break;
                                                case Direction::RIGHT:
                                                    moovable.push_back(pair<Entity, Position> {nextEntity, nextPos.next(Direction::LEFT)});
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    if(!pushable){
                                        for (pair<Entity, Position> pair : moovable) {
                                            board.dropEntity(pair.second, pair.first);
                                            Position pos = pair.second;
                                            board.addEntity(pos.next(dir), pair.first);
                                        }
                                        break;
                                    }
                                } else{
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
bool Game::isGameOver(){
    return this->gameOver;
}
bool Game::isLevelOver(){
    return this->levelOver;
}

void Game::scanRule(){
    rules.clear();
    Rule limitRule{EntityNature::LIMIT,EntityNature::IS,EntityNature::STOP};
    rules.push_back(limitRule);
    for (int i = 1; i < board.getHeight()-1; ++i) {
        for (int j = 1; j < board.getWidth()-1; ++j) {
            Position pos{i,j};
            vector<Entity> entities{board.getEntities(pos)};
            for (int k = 0; k < entities.size(); ++k) {
                if(entities[k].getNature()==EntityNature::IS){
                    Position posUp{pos.next(Direction::UP)};
                    vector<Entity> entitiesUp{board.getEntities(posUp)};
                    for (Entity entityUp : entitiesUp) {
                        if(entityUp.getType()==EntityType::TEXT){
                            vector<EntityNature> valide {EntityNature::BABA,EntityNature::FLAG,EntityNature::GRASS,EntityNature::METAL,EntityNature::ROCK,EntityNature::WALL,EntityNature::WATER};
                            if(count(valide.begin(),valide.end(),entityUp.getNature())){
                                Position posDown{pos.next(Direction::DOWN)};
                                vector<Entity> entitiesDown{board.getEntities(posDown)};
                                for(Entity entityDown : entitiesDown){
                                    if(entityDown.getType()==EntityType::TEXT){
                                        Rule rule {entityUp.getNature(),EntityNature::IS,entityDown.getNature()};
                                        rules.push_back(rule);
                                    }
                                }
                            }
                        }
                    }
                    Position posLeft{pos.next(Direction::LEFT)};
                    vector<Entity> entitiesLeft{board.getEntities(posLeft)};
                    for (Entity entityLeft : entitiesLeft) {
                        if(entityLeft.getType()==EntityType::TEXT){
                            vector<EntityNature> valide {EntityNature::BABA,EntityNature::FLAG,EntityNature::GRASS,EntityNature::METAL,EntityNature::ROCK,EntityNature::WALL,EntityNature::WATER};
                            if(count(valide.begin(),valide.end(),entityLeft.getNature())){
                                Position posRight{pos.next(Direction::RIGHT)};
                                vector<Entity> entitiesRight{board.getEntities(posRight)};
                                for(Entity entityRight : entitiesRight){
                                    if(entityRight.getType()==EntityType::TEXT){
                                        Rule rule {entityLeft.getNature(),EntityNature::IS,entityRight.getNature()};
                                        rules.push_back(rule);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Game::saveLevel(){
    vector<string> res;
    res.push_back(to_string(currentLevel));
    int height = board.getHeight();
    int width = board.getWidth();
    stringstream ss;
    ss << to_string(width) << " " << to_string(height);
    res.push_back(ss.str());
    for (int i = 1; i < height-1; ++i) {
        for (int j = 1; j < width-1; ++j) {
            Position pos{i,j};
            vector<Entity> entities = board.getEntities(pos);
            for (int k = 0; k < entities.size(); ++k) {
                stringstream ss2;
                ss2 << entityToString(entities[k]) << " " << to_string(j) << " " << to_string(i);
                res.push_back(ss2.str());
            }
        }
    }
    ofstream myFile("../levels/backup.txt", ios::out | ios::trunc);

    if (myFile.is_open()) {
        for (const auto& str : res) {
            myFile.write(str.c_str(), str.length());
            myFile.write("\n", 1);
        }
        myFile.close();
    }
    else {
        cout << "Unable to open file";
    }
}

string Game::entityToString(Entity entity){
    EntityType entityType = entity.getType();
    EntityNature entityNature = entity.getNature();
    string res;
    if(entityType==EntityType::ELEMENT){
        if (entityNature == EntityNature::BABA) {
            res = "baba";
        }
        else if (entityNature == EntityNature::FLAG) {
            res = "flag";
        }
        else if (entityNature == EntityNature::GRASS) {
            res = "grass";
        }
        else if (entityNature == EntityNature::METAL) {
            res = "metal";
        }
        else if (entityNature == EntityNature::ROCK) {
            res = "rock";
        }
        else if (entityNature == EntityNature::WALL) {
            res = "wall";
        }
        else if (entityNature == EntityNature::WATER) {
            res = "water";
        }
    }
    else {
        if (entityNature == EntityNature::BABA) {
            res = "text_baba";
        }
        else if (entityNature == EntityNature::FLAG) {
            res = "text_flag";
        }
        else if (entityNature == EntityNature::GRASS) {
            res = "text_grass";
        }
        else if (entityNature == EntityNature::METAL) {
            res = "text_metal";
        }
        else if (entityNature == EntityNature::ROCK) {
            res = "text_rock";
        }
        else if (entityNature == EntityNature::WALL) {
            res = "text_wall";
        }
        else if (entityNature == EntityNature::WATER) {
            res = "text_water";
        }
        else if (entityNature == EntityNature::IS) {
            res = "is";
        }
        else if (entityNature == EntityNature::KILL) {
            res = "kill";
        }
        else if (entityNature == EntityNature::PUSH) {
            res = "push";
        }
        else if (entityNature == EntityNature::SINK) {
            res = "sink";
        }
        else if (entityNature == EntityNature::STOP) {
            res = "stop";
        }
        else if (entityNature == EntityNature::YOU) {
            res = "you";
        }
        else if (entityNature == EntityNature::WIN) {
            res = "win";
        }
    }
    return res;
}

void Game::reloadLevel(){
    //to do
}

/*
 * Méthode qui va chercher si à la position donnée un élément est bloqueur
 */
bool Game::isBlocking(Position pos){
    vector<Entity> entities = board.getEntities(pos);
    for(Entity entity : entities){
        for(Rule rule : rules){
            if(rule.getSubject() == entity.getNature() && rule.getObject() == EntityNature::STOP){
                return true;
            }
        }
    }
    return false;
}

Board Game::getBoard(){
    return this->board;
}

#endif // GAME_H
