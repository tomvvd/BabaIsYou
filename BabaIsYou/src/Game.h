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
        inline int getBoardHeight() const;
        inline int getBoardWidth() const;
        inline vector<Entity> getBoardEntities(Position pos);
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
    vector<EntityNature> entitiesPlayer,entitiesPush, entitiesStop;
    bool hasBeenFound = false;
    for(Rule rule : rules){
        if(rule.getObject() == EntityNature::YOU){
            entitiesPlayer.push_back(rule.getSubject());
            hasBeenFound = true;
        }
        else if(rule.getObject() == EntityNature::STOP){
            entitiesStop.push_back(rule.getSubject());
        }
        else if(rule.getObject() == EntityNature::PUSH){
            entitiesPush.push_back(rule.getSubject());
        }
    }
    if(hasBeenFound){
        vector<pair<Entity,Position>> movePlayers;
        for (int i = 1; i < board.getHeight()-1; ++i) {
            for (int j = 1; j < board.getWidth()-1; ++j) {
                Position pos {i,j};
                vector<Entity> entities = board.getEntities(pos);
                for (EntityNature player:entitiesPlayer) {
                    for (Entity entity : entities) {
                        if(entity.getType()==EntityType::ELEMENT && entity.getNature()==player){
                            bool stop = false;
                            bool ok = false;
                            int cpt = 1;
                            Position next{pos.next(dir)};
                            while(!stop && !ok){
                                vector<Entity> nextEntities = board.getEntities(next);
                                if(!nextEntities.empty()){
                                    for (Entity nextEntity : nextEntities) {
                                        if(count(entitiesStop.begin(),entitiesStop.end(),nextEntity.getNature())){
                                            stop = true;
                                        }
                                        else if(count(entitiesPush.begin(),entitiesPush.end(),nextEntity.getNature())==0){
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
                                        if(count(entitiesPush.begin(),entitiesPush.end(),l.getNature())){
                                            board.addEntity(pos1,l);
                                            board.dropEntity(pos2,l);
                                        }
                                    }
                                    cpt--;
                                }
                                movePlayers.push_back(make_pair(entity,pos));
                            }
                        }
                    }
                }
            }
        }
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

int Game::getBoardHeight() const{
    return board.getHeight();
}
int Game::getBoardWidth() const{
    return board.getWidth();
}
vector<Entity> Game::getBoardEntities(Position pos){
    return board.getEntities(pos);
}

#endif // GAME_H
