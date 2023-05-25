#ifndef BOARDOBSERVER_H
#define BOARDOBSERVER_H

#include <QGridLayout>
#include "../util/Observer.h"
#include "../game/Game.h"

class BoardObserver : public QGridLayout, public Observer
{
    Game & game_;
    static std::map<std::string, QString> entityImagePathMap;
public:
    BoardObserver(Game & game, QWidget* parent = nullptr);
    ~BoardObserver();
    void update(const Observable * subject) override;
};

#endif // BOARDOBSERVER_H
