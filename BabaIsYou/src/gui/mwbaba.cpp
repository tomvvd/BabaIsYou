#include "mwbaba.h"
#include "ui_mwbaba.h"

MWBaba::MWBaba(Game & game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWBaba),
    game{game}
{
    ui->setupUi(this);

    connexion();
}

void MWBaba::connexion(){
    connect(ui->action_Restart, &QAction::triggered,this, &MWBaba::restart);
    connect(ui->action_Save, &QAction::triggered,this, &MWBaba::save);
    connect(ui->action_Reload, &QAction::triggered,this, &MWBaba::reload);
    connect(ui->action_Exit, &QAction::triggered, &QCoreApplication::quit);
}

void MWBaba::restart(){
    game.restartLevel();
}
void MWBaba::save(){
    game.saveLevel();
}
void MWBaba::reload(){
    game.reloadLevel();
}


MWBaba::~MWBaba()
{
    delete ui;
}
