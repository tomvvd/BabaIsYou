#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "../util/Observable.h"
#include "../util/Observer.h"
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
    void checkVerticalRule(const Position& pos, const vector<EntityNature>& validEntities);
    void checkHorizontalRule(const Position& pos, const vector<EntityNature>& validEntities);
    void isSink();
    void transformation();
    void isKill();
public:
    Game();
    void constructLevel(int num);
    void move(Direction dir);
    bool isWin();
    void saveLevel();
    void reloadLevel();
    void restartLevel();
    int getCurrentLevel() const;
    int getBoardHeight() const;
    int getBoardWidth() const;
    const vector<Entity> &getBoardEntities(Position pos) const;
};

#endif // GAME_H
