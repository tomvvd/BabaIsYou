#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Position.h"
#include "LevelLoader.h"
#include "Rule.h"

class Game{
    private:
        Board board;
        vector<Rule> rules;
        bool levelOver;
        bool gameOver;
        int currentLevel;

        inline void addRule(EntityNature subject, EntityNature operation, EntityNature object);
        inline void scan();
    public:
        inline Game();
        inline void constructLevel(int num);
        inline void move(Direction dir);
        inline bool isGameOver();
        inline bool isLevelOver();
};

Game::Game() : currentLevel{0}, board{LevelLoader::levelLoad(0)}, levelOver{false}, gameOver{false} {
    scan();
}

void Game::constructLevel(int num){
    currentLevel = num;
    levelOver = false;
    this->board = LevelLoader::levelLoad(num);
    scan();
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
                        while (!nextEntities.empty()) {
                            Position nextTarget = nextPos.next(dir);

                            if(nextEntities.empty()){
                                board.dropEntity(pos,entity);
                                board.addEntity(nextPos,entity);
                            }
                            else{
                                vector<Entity> nextTargetEntities = board.getEntities(nextTarget);
                                for(Entity nextEntity : nextTargetEntities){
                                    if(nextEntity.getType() == EntityType::TEXT){
                                        board.dropEntity(pos, entity);
                                        board.addEntity(nextPos, entity);
                                        nextEntities = board.getEntities()
                                    } else {

                                    }
                                }
                            }
                        }
                        /*
                        if(nextEntities.empty()){
                            board.dropEntity(pos,entity);
                            board.addEntity(nextPos,entity);
                        }
                        else{
                            Position nextNextPos = nextPos.next(dir);
                            vector<Entity> nextNextEntities = board.getEntities(nextNextPos);
                            for(Entity nextEntity : nextEntities){
                                if(nextEntity.getType() == EntityType::TEXT){
                                    if(nextNextEntities.empty()){
                                        board.dropEntity(pos,entity);
                                        board.addEntity(nextPos,entity);
                                        board.dropEntity(nextPos,nextEntity);
                                        board.addEntity(nextNextPos,nextEntity);
                                    }
                                    else{

                                    }
                                }
                            }


                            /*
                            Position nextNextPos = nextPos.next(dir);
                            vector<Entity> nextNextEntities = board.getEntities(nextNextPos);
                            for(Entity nextEntity : nextEntities){
                                if(nextEntity.getType() == EntityType::TEXT){
                                    if(nextNextEntities.empty()){
                                        board.dropEntity(pos,entity);
                                        board.addEntity(nextPos,entity);
                                        board.dropEntity(nextPos,nextEntity);
                                        board.addEntity(nextNextPos,nextEntity);
                                    }
                                    else{
                                        while (!nextNextEntities.empty()) {
                                            Position nextTarget = nextNextPos.next(dir);
                                            nextNextEntities = board.getEntities(nextTarget);

                                            bool isMovable{true};
                                            for (Entity nextNextEntity : nextNextEntities) {
                                                Position nextNextNextPos = nextNextPos.next(dir);
                                                vector<Entity> nextNextNextEntities = board.getEntities(nextNextNextPos);
                                                if(nextNextNextEntities.empty()){
                                                    board.dropEntity(nextNextPos,entity);
                                                    board.addEntity(nextPos,entity);
                                                    board.dropEntity(nextPos,nextEntity);
                                                    board.addEntity(nextNextPos,nextEntity);
                                                }
                                                for (Rule rule : rules) {
                                                    if(rule.getSubject()==nextNextEntity.getNature()){
                                                        if(rule.getObject()==EntityNature::)
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }*/
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

void Game::scan(){
    rules.clear();
    for (int i = 1; i < board.getHeight()-1; ++i) {
        for (int j = 1; j < board.getWidth()-1; ++j) {
            Position pos{i,j};
            vector<Entity> entities{board.getEntities(pos)};
            for (int k = 0; k < entities.size(); ++k) {
                if(entities[k].getNature()==EntityNature::IS){
                    Position posN{pos.next(Direction::UP)};
                    vector<Entity> entitiesN{board.getEntities(posN)};
                    if(entitiesN.size()==1){
                        Entity entityN = entitiesN[0];
                        if(entityN.getType()==EntityType::TEXT){
                            vector<EntityNature> valide {EntityNature::BABA,EntityNature::FLAG,EntityNature::GRASS,EntityNature::METAL,EntityNature::ROCK,EntityNature::WALL,EntityNature::WATER};
                            if(count(valide.begin(),valide.end(),entityN.getNature())){
                                Position posS{pos.next(Direction::DOWN)};
                                vector<Entity> entitiesS{board.getEntities(posN)};
                                if(entitiesS.size()==1){
                                    Entity entityS = entitiesS[0];
                                    if(entityS.getType()==EntityType::TEXT){
                                        Rule rule {entityN.getNature(),entities[k].getNature(),entityS.getNature()};
                                        rules.push_back(rule);
                                    }
                                }
                            }
                        }
                    }
                    Position posW{pos.next(Direction::LEFT)};
                    vector<Entity> entitiesW{board.getEntities(posW)};
                    if(entitiesW.size()==1){
                        Entity entityW = entitiesW[0];
                        if(entityW.getType()==EntityType::TEXT){
                            vector<EntityNature> valide {EntityNature::BABA,EntityNature::FLAG,EntityNature::GRASS,EntityNature::METAL,EntityNature::ROCK,EntityNature::WALL,EntityNature::WATER};
                            if(count(valide.begin(),valide.end(),entityW.getNature())){
                                Position posE{pos.next(Direction::RIGHT)};
                                vector<Entity> entitiesE{board.getEntities(posE)};
                                if(entitiesE.size()==1){
                                    Entity entityE = entitiesE[0];
                                    if(entityE.getType()==EntityType::TEXT){
                                        Rule rule {entityW.getNature(),entities[k].getNature(),entityE.getNature()};
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


#endif // GAME_H
