#ifndef MWBABA_H
#define MWBABA_H

#include <QMainWindow>
#include "../game/Game.h"

namespace Ui {
class MWBaba;
}

class MWBaba : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWBaba(Game & game,QWidget *parent = nullptr);
    ~MWBaba();

private:
    Ui::MWBaba *ui;
    Game & game;

    void connexion();

private slots:
    void restart();
    void save();
    void reload();
};

#endif // MWBABA_H
