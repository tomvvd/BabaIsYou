#include "mwbaba.h"
#include "ui_mwbaba.h"
#include "endwindow.h"

MWBaba::MWBaba(Game & game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWBaba),
    game_{game}
{
    ui->setupUi(this);
    connexion();

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    boardobserver_ = new BoardObserver(game);
    ui->centralwidget->setLayout(boardobserver_);
}

void MWBaba::connexion(){
    connect(ui->action_Restart, &QAction::triggered,this, &MWBaba::restart);
    connect(ui->action_Save, &QAction::triggered,this, &MWBaba::save);
    connect(ui->action_Reload, &QAction::triggered,this, &MWBaba::reload);
    connect(ui->action_Exit, &QAction::triggered, &QCoreApplication::quit);
}

void MWBaba::restart(){
    game_.restartLevel();
}
void MWBaba::save(){
    game_.saveLevel();
}
void MWBaba::reload(){
    game_.reloadLevel();
}

void MWBaba::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        game_.move(Direction::LEFT);
    }
    else if (event->key() == Qt::Key_Right) {
        game_.move(Direction::RIGHT);
    }
    else if (event->key() == Qt::Key_Up) {
        game_.move(Direction::UP);
    }
    else if (event->key() == Qt::Key_Down) {
        game_.move(Direction::DOWN);
    }

    if(game_.isWin()){
        if(game_.getCurrentLevel()+1!=5){
            game_.constructLevel(game_.getCurrentLevel()+1);
        }
        else{
            EndWindow *endwindow = new EndWindow();
            this->setCentralWidget(endwindow);
            ui->action_Restart->setEnabled(false);
            ui->action_Reload->setEnabled(false);
            ui->action_Save->setEnabled(false);
        }
    }

    // Appel l'implémentation de la classe de base
    QMainWindow::keyPressEvent(event);
}

MWBaba::~MWBaba()
{
    delete ui;
}
