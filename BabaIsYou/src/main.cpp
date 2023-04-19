#include <iostream>
#include "Direction.h"
#include "LevelLoader.h"
#include "Position.h"
#include "EntityNature.h"
#include "EntityType.h"
#include "View.h"
#include "Game.h"

using namespace std;

int main()
{
    /*Position p1{12,4};
    Position p2 = p1.next(Direction::DOWN);

    cout << "(" << p1.getRow() << "," << p1.getColumn() << ")" << endl;
    cout << "(" << p2.getRow() << "," << p2.getColumn() << ")" << endl;

    EntityNature n {EntityNature::BABA};
    EntityType t {EntityType::ELEMENT};*/

    //Board board {LevelLoader::levelLoad(0)};
    //View::showBoard(board);

    Game game {};
    game.constructLevel(1);
    game.saveLevel();
    int lol{1};
}
