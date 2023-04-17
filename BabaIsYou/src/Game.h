#include "Board.h"
#include "Position.h"
#include "Rule.h"

#ifndef GAME_H
#define GAME_H

class Game{
    private:
        Board board;
        Position playerPosition;
        vector<Rule> rules;
        bool levelOver;
        bool gameOver;

        inline void addRule(EntityNature subject, EntityNature operation, EntityNature object);
        inline EntityNature applyRule(EntityNature subject);
        inline void deleteRules(Position pos);
    public:
        Game();
        inline void constructLevel(int num);
        inline void move(Direction dir);
        inline bool isGameOver();
        inline bool isLevelOver();
};

void Game::addRule(EntityNature subject, EntityNature operation, EntityNature object){
    //TODO
}
EntityNature Game::applyRule(EntityNature subject){
    //TODO
}
void Game::deleteRules(Position pos){
    //TODO
}
void Game::constructLevel(int num){
    //TODO
}
void Game::move(Direction dir){
    //TODO
}
bool Game::isGameOver(){
    return this->gameOver;
}
bool Game::isLevelOver(){
    return this->levelOver;
}


#endif // GAME_H
