#include "boardobserver.h"
#include <QLabel>
#include <QPainter>

std::map<std::string, QString> BoardObserver::entityImagePathMap = {
    {"B", "../sprites/baba.png"},
    {"F", "../sprites/flag.png"},
    {"G", "../sprites/grass.png"},
    {"M", "../sprites/metal.png"},
    {"X", "../sprites/limit.png"},
    {"R", "../sprites/rock.png"},
    {"W", "../sprites/wall.png"},
    {"#", "../sprites/water.png"},
    {"L", "../sprites/lava.png"},
    {"BABA", "../sprites/babatext.png"},
    {"FLAG", "../sprites/flagtext.png"},
    {"GRASS", "../sprites/grasstext.png"},
    {"METAL", "../sprites/metaltext.png"},
    {"ROCK", "../sprites/rocktext.png"},
    {"WALL", "../sprites/walltext.png"},
    {"WATER", "../sprites/watertext.png"},
    {"LAVA", "../sprites/lavatext.png"},
    {"IS", "../sprites/istext.png"},
    {"KILL", "../sprites/killtext.png"},
    {"PUSH", "../sprites/pushtext.png"},
    {"SINK", "../sprites/sinktext.png"},
    {"STOP", "../sprites/stoptext.png"},
    {"YOU", "../sprites/youtext.png"},
    {"WIN", "../sprites/wintext.png"}
};

BoardObserver::BoardObserver(Game& game, QWidget* parent) : QGridLayout(parent), game_{game} {
    game_.registerObserver(this);

    this->setSpacing(0);

    for (int row = 0; row < game.getBoardHeight(); ++row) {
        for (int col = 0; col < game.getBoardWidth(); ++col) {
            // Get the entities at the current position
            vector<Entity> entities = game.getBoardEntities(Position{row, col});

            QLabel* label = new QLabel();

            QImage baseImage("../sprites/transparent.png");
            QPainter painter(&baseImage);

            for (const Entity& entity : entities) {
                // Load the image for the entity
                QImage image(entityImagePathMap[entity.to_string()]);

                // Overlay
                painter.drawImage(0, 0, image);
            }
            painter.end();
            label->setPixmap(QPixmap::fromImage(baseImage));
            this->addWidget(label, row, col);
        }
    }
}

void BoardObserver::update(const Observable* subject) {
    // Check that the subject of observation is indeed a Game type object
    const Game* gameSubject = dynamic_cast<const Game*>(subject);
    if (gameSubject == nullptr) {
        return;
    }

    // Delete all widgets from the layout
    QLayoutItem* item;
    while ((item = this->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for (int row = 0; row < gameSubject->getBoardHeight(); ++row) {
        for (int col = 0; col < gameSubject->getBoardWidth(); ++col) {
            // Get the entities at the current position
            vector<Entity> entities = gameSubject->getBoardEntities(Position{ row, col });

            QLabel* label = new QLabel();

            QImage baseImage("../sprites/transparent.png");
            QPainter painter(&baseImage);

            for (const Entity& entity : entities) {
                // Load the image for the entity
                QImage image(entityImagePathMap[entity.to_string()]);

                // Overlay
                painter.drawImage(0, 0, image);
            }
            painter.end();
            label->setPixmap(QPixmap::fromImage(baseImage));
            this->addWidget(label, row, col);
        }
    }
}

BoardObserver::~BoardObserver()
{
    game_.unregisterObserver(this);
}
