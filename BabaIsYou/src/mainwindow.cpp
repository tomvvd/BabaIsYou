#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Game.h"
#include <QtWidgets/qlabel.h>
#include <map>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _grid(this)
{
    ui->setupUi(this);

    Game game{};

    for (int row = 0; row < game.getBoardHeight(); ++row) {
        for (int col = 0; col < game.getBoardWidth(); ++col) {

            vector<Entity> entities = game.getBoardEntities(Position{row,col});

            map<string,QString> entityImagePathMap;
            entityImagePathMap["B"] = "../sprites/baba.png";
            entityImagePathMap["F"] = "../sprites/flag.png";
            entityImagePathMap["G"] = "../sprites/grass.png";
            entityImagePathMap["M"] = "../sprites/metal.png";
            entityImagePathMap["X"] = "../sprites/limit.png";
            entityImagePathMap["R"] = "../sprites/rock.png";
            entityImagePathMap["W"] = "../sprites/wall.png";
            entityImagePathMap["#"] = "../sprites/water.png";
            entityImagePathMap["L"] = "../sprites/lava.png";
            entityImagePathMap["BABA"] = "../sprites/babatext.png";
            entityImagePathMap["FLAG"] = "../sprites/flagtext.png";
            entityImagePathMap["GRASS"] = "../sprites/grasstext.png";
            entityImagePathMap["METAL"] = "../sprites/metaltext.png";
            entityImagePathMap["ROCK"] = "../sprites/rocktext.png";
            entityImagePathMap["WALL"] = "../sprites/walltext.png";
            entityImagePathMap["WATER"] = "../sprites/watertext.png";
            entityImagePathMap["LAVA"] = "../sprites/lavatext.png";
            entityImagePathMap["IS"] = "../sprites/istext.png";
            entityImagePathMap["KILL"] = "../sprites/killtext.png";
            entityImagePathMap["PUSH"] = "../sprites/pushtext.png";
            entityImagePathMap["SINK"] = "../sprites/sinktext.png";
            entityImagePathMap["STOP"] = "../sprites/stoptext.png";
            entityImagePathMap["YOU"] = "../sprites/youtext.png";
            entityImagePathMap["WIN"] = "../sprites/wintext.png";

            QLabel* label = new QLabel();
            QVBoxLayout* layout = new QVBoxLayout(label);

            for (const Entity & entity : entities) {
                QString imagePath = entityImagePathMap.at(entity.to_string());
                QPixmap pixmap(imagePath);
                QLabel* imageLabel = new QLabel();
                imageLabel->setPixmap(pixmap);
                layout->addWidget(imageLabel);
            }

            _grid.addWidget(label,row,col);
        }
    }

    ui->centralwidget->setLayout(&_grid);
}

MainWindow::~MainWindow()
{
    delete ui;
}
