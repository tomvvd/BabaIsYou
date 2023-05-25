#ifndef MWBABA_H
#define MWBABA_H

#include <QMainWindow>
#include "../game/Game.h"
#include "boardobserver.h"
#include <QKeyEvent>

namespace Ui {
class MWBaba;
}

class MWBaba : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWBaba(Game & game,QWidget *parent = nullptr);
    ~MWBaba();


protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MWBaba *ui;

    Game & game_;

    BoardObserver *boardobserver_;

    void connexion();

private slots:
    void restart();
    void save();
    void reload();
};

#endif // MWBABA_H
