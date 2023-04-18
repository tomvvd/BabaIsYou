#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class LevelLoader {
public:
    static Board levelLoad(int nb) {
        stringstream ss;
        ss << "../levels/level_" << nb << ".txt";
        string filename = ss.str();
        ifstream file(filename);
        vector<string> lines;
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        }
        else {
            cerr << "Impossible d'ouvrir le fichier " << filename << std::endl;
        }

        //construction du board
        vector<string> sizeBoard;
        stringstream ssBoard{lines.at(0)};
        string token;
        while (getline(ssBoard, token, ' ')) {
            sizeBoard.push_back(token);
        }
        int column{stoi(sizeBoard.at(0))+2};
        int row{stoi(sizeBoard.at(1))+2};
        Board board {row,column};

        //remplissage du board
        for (int i = 0; i < column; ++i) {
            Position pos1 {0,i};
            board.addEntity(pos1,Entity{EntityNature::LIMIT,EntityType::ELEMENT});
            Position pos2{row-1,i};
            board.addEntity(pos2,Entity{EntityNature::LIMIT,EntityType::ELEMENT});
        }
        for (int i = 1; i < row-1; ++i) {
            Position pos1 {i,0};
            board.addEntity(pos1,Entity{EntityNature::LIMIT,EntityType::ELEMENT});
            Position pos2{i,column-1};
            board.addEntity(pos2,Entity{EntityNature::LIMIT,EntityType::ELEMENT});
        }
        for (int i = 1; i < lines.size(); ++i) {
            vector<string> result;
            stringstream ssResult{lines.at(i)};
            string token;
            while (getline(ssResult, token, ' ')) {
                result.push_back(token);
            }
            Position pos {stoi(result.at(2))+1,stoi(result.at(1))+1};

            string input = result.at(0);

            if (input == "baba") {
                board.addEntity(pos,Entity{EntityNature::BABA,EntityType::ELEMENT});
            }
            else if (input == "text_baba") {
                board.addEntity(pos,Entity{EntityNature::BABA,EntityType::TEXT});
            }
            else if (input == "flag") {
                board.addEntity(pos,Entity{EntityNature::FLAG,EntityType::ELEMENT});
            }
            else if (input == "text_flag") {
                board.addEntity(pos,Entity{EntityNature::FLAG,EntityType::TEXT});
            }
            else if (input == "wall") {
                board.addEntity(pos,Entity{EntityNature::WALL,EntityType::ELEMENT});
            }
            else if (input == "text_wall") {
                board.addEntity(pos,Entity{EntityNature::WALL,EntityType::TEXT});
            }
            else if (input == "rock") {
                board.addEntity(pos,Entity{EntityNature::ROCK,EntityType::ELEMENT});
            }
            else if (input == "text_rock") {
                board.addEntity(pos,Entity{EntityNature::ROCK,EntityType::TEXT});
            }
            else if (input == "metal") {
                board.addEntity(pos,Entity{EntityNature::METAL,EntityType::ELEMENT});
            }
            else if (input == "text_metal") {
                board.addEntity(pos,Entity{EntityNature::METAL,EntityType::TEXT});
            }
            else if (input == "grass") {
                board.addEntity(pos,Entity{EntityNature::GRASS,EntityType::ELEMENT});
            }
            else if (input == "text_grass") {
                board.addEntity(pos,Entity{EntityNature::GRASS,EntityType::TEXT});
            }
            else if (input == "water") {
                board.addEntity(pos,Entity{EntityNature::WATER,EntityType::ELEMENT});
            }
            else if (input == "text_water") {
                board.addEntity(pos,Entity{EntityNature::WATER,EntityType::TEXT});
            }
            else if (input == "is") {
                board.addEntity(pos,Entity{EntityNature::IS,EntityType::TEXT});
            }
            else if (input == "push") {
                board.addEntity(pos,Entity{EntityNature::PUSH,EntityType::TEXT});
            }
            else if (input == "stop") {
                board.addEntity(pos,Entity{EntityNature::STOP,EntityType::TEXT});
            }
            else if (input == "win") {
                board.addEntity(pos,Entity{EntityNature::WIN,EntityType::TEXT});
            }
            else if (input == "you") {
                board.addEntity(pos,Entity{EntityNature::YOU,EntityType::TEXT});
            }
            else if (input == "kill") {
                board.addEntity(pos,Entity{EntityNature::KILL,EntityType::TEXT});
            }
            else if (input == "sink") {
                board.addEntity(pos,Entity{EntityNature::SINK,EntityType::TEXT});
            }
        }


        return board;
    }
};

#endif // LEVELLOADER_H
