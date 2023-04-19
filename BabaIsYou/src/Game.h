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

        inline void scanRule();
    public:
        inline Game();
        inline void constructLevel(int num);
        inline void move(Direction dir);
        inline bool isGameOver();
        inline bool isLevelOver();
        inline void saveLevel();
        inline void reloadLevel();
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
    /*EntityNature player;
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
                    }
                }
            }
        }
    }*/
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
    //to do
}

void Game::reloadLevel(){
    //to do
}

#endif // GAME_H
