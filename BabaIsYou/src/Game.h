#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Observable.h"
#include "Observer.h"
#include "Position.h"
#include "Rule.h"
#include <map>

class Game : public Observable{
private:
    Board board;
    vector<Rule> rules;
    int currentLevel;
    vector<Observer *> observers;

    void scanRule();
    void isSink();
    void transformation();
    void isKill();
public:
    Game();
    void constructLevel(int num);
    void move(Direction dir);
    bool isLevelOver();
    void saveLevel();
    void reloadLevel();
    void restartLevel();
    int getCurrentLevel() const;
    int getBoardHeight() const;
    int getBoardWidth() const;
    vector<Entity> getBoardEntities(Position pos);
};

#endif // GAME_H
