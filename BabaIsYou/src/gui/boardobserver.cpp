#include "boardobserver.h"
#include <QLabel>

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

    //réduire les espaces entre les éléments
    //this->setSpacing(0);

    for (int row = 0; row < game.getBoardHeight(); ++row) {
        for (int col = 0; col < game.getBoardWidth(); ++col) {
            // Get the entities at the current position
            vector<Entity> entities = game.getBoardEntities(Position{row, col});

            // Create a container widget to hold the labels for multiple entities at the same position
            QWidget* entityWidget = new QWidget();
            QHBoxLayout* entityLayout = new QHBoxLayout(entityWidget);
            entityLayout->setSpacing(0);

            // Add a label for each entity at the current position
            for (const Entity& entity : entities) {
                QLabel* label = new QLabel();
                QString imagePath = entityImagePathMap[entity.to_string()];
                QPixmap pixmap(imagePath);
                label->setPixmap(pixmap);
                entityLayout->addWidget(label);
            }

            // Add the entity widget to the grid layout
            this->addWidget(entityWidget, row, col);
        }
    }
}

void BoardObserver::update(const Observable* subject) {
    // Vérifier que le sujet d'observation est bien un objet de type Game
    const Game* gameSubject = dynamic_cast<const Game*>(subject);
    if (gameSubject == nullptr) {
        // Le sujet d'observation n'est pas du bon type, on ne fait rien
        return;
    }

    // Effacer tous les widgets du layout
    QLayoutItem* item;
    while ((item = this->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for (int row = 0; row < gameSubject->getBoardHeight(); ++row) {
        for (int col = 0; col < gameSubject->getBoardWidth(); ++col) {
            // Get the entities at the current position
            vector<Entity> entities = gameSubject->getBoardEntities(Position{ row, col });

            // Create a container widget to hold the labels for multiple entities at the same position
            QWidget* entityWidget = new QWidget();
            QHBoxLayout* entityLayout = new QHBoxLayout(entityWidget);
            entityLayout->setSpacing(0);

            // Add a label for each entity at the current position
            for (const Entity& entity : entities) {
                QLabel* label = new QLabel();
                QString imagePath = entityImagePathMap[entity.to_string()];
                QPixmap pixmap(imagePath);
                label->setPixmap(pixmap);
                entityLayout->addWidget(label);
            }

            // Add the entity widget to the grid layout
            this->addWidget(entityWidget, row, col);
        }
    }
}

BoardObserver::~BoardObserver()
{
    // Détacher l'observateur du sujet d'observation
    game_.unregisterObserver(this);
    // Le destructeur de QGridLayout sera appelé automatiquement
}
