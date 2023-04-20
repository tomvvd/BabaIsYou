#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class LevelLoader {

    static Entity stringToEntity(string input){
        Entity res{EntityNature::BABA,EntityType::ELEMENT};
        if (input == "baba") {
            res = Entity{EntityNature::BABA,EntityType::ELEMENT};
        }
        else if (input == "text_baba") {
            res = Entity{EntityNature::BABA,EntityType::TEXT};
        }
        else if (input == "flag") {
            res = Entity{EntityNature::FLAG,EntityType::ELEMENT};
        }
        else if (input == "text_flag") {
            res = Entity{EntityNature::FLAG,EntityType::TEXT};
        }
        else if (input == "wall") {
            res = Entity{EntityNature::WALL,EntityType::ELEMENT};
        }
        else if (input == "text_wall") {
            res = Entity{EntityNature::WALL,EntityType::TEXT};
        }
        else if (input == "rock") {
            res = Entity{EntityNature::ROCK,EntityType::ELEMENT};
        }
        else if (input == "text_rock") {
            res = Entity{EntityNature::ROCK,EntityType::TEXT};
        }
        else if (input == "metal") {
            res = Entity{EntityNature::METAL,EntityType::ELEMENT};
        }
        else if (input == "text_metal") {
            res = Entity{EntityNature::METAL,EntityType::TEXT};
        }
        else if (input == "grass") {
            res = Entity{EntityNature::GRASS,EntityType::ELEMENT};
        }
        else if (input == "text_grass") {
            res = Entity{EntityNature::GRASS,EntityType::TEXT};
        }
        else if (input == "water") {
            res = Entity{EntityNature::WATER,EntityType::ELEMENT};
        }
        else if (input == "text_water") {
            res = Entity{EntityNature::WATER,EntityType::TEXT};
        }
        else if (input == "lava") {
            res = Entity{EntityNature::LAVA,EntityType::ELEMENT};
        }
        else if (input == "text_lava") {
            res = Entity{EntityNature::LAVA,EntityType::TEXT};
        }
        else if (input == "is") {
            res = Entity{EntityNature::IS,EntityType::TEXT};
        }
        else if (input == "push") {
            res = Entity{EntityNature::PUSH,EntityType::TEXT};
        }
        else if (input == "stop") {
            res = Entity{EntityNature::STOP,EntityType::TEXT};
        }
        else if (input == "win") {
            res = Entity{EntityNature::WIN,EntityType::TEXT};
        }
        else if (input == "you") {
            res = Entity{EntityNature::YOU,EntityType::TEXT};
        }
        else if (input == "kill") {
            res = Entity{EntityNature::KILL,EntityType::TEXT};
        }
        else if (input == "sink") {
            res = Entity{EntityNature::SINK,EntityType::TEXT};
        }
        return res;
    }

    static string entityToString(Entity entity){
        EntityType entityType = entity.getType();
        EntityNature entityNature = entity.getNature();
        string res;
        if(entityType==EntityType::ELEMENT){
            if (entityNature == EntityNature::BABA) {
                res = "baba";
            }
            else if (entityNature == EntityNature::FLAG) {
                res = "flag";
            }
            else if (entityNature == EntityNature::GRASS) {
                res = "grass";
            }
            else if (entityNature == EntityNature::METAL) {
                res = "metal";
            }
            else if (entityNature == EntityNature::ROCK) {
                res = "rock";
            }
            else if (entityNature == EntityNature::WALL) {
                res = "wall";
            }
            else if (entityNature == EntityNature::WATER) {
                res = "water";
            }
            else if (entityNature == EntityNature::LAVA) {
                res = "lava";
            }
        }
        else {
            if (entityNature == EntityNature::BABA) {
                res = "text_baba";
            }
            else if (entityNature == EntityNature::FLAG) {
                res = "text_flag";
            }
            else if (entityNature == EntityNature::GRASS) {
                res = "text_grass";
            }
            else if (entityNature == EntityNature::METAL) {
                res = "text_metal";
            }
            else if (entityNature == EntityNature::ROCK) {
                res = "text_rock";
            }
            else if (entityNature == EntityNature::WALL) {
                res = "text_wall";
            }
            else if (entityNature == EntityNature::WATER) {
                res = "text_water";
            }
            else if (entityNature == EntityNature::LAVA) {
                res = "text_lava";
            }
            else if (entityNature == EntityNature::IS) {
                res = "is";
            }
            else if (entityNature == EntityNature::KILL) {
                res = "kill";
            }
            else if (entityNature == EntityNature::PUSH) {
                res = "push";
            }
            else if (entityNature == EntityNature::SINK) {
                res = "sink";
            }
            else if (entityNature == EntityNature::STOP) {
                res = "stop";
            }
            else if (entityNature == EntityNature::YOU) {
                res = "you";
            }
            else if (entityNature == EntityNature::WIN) {
                res = "win";
            }
        }
        return res;
    }

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

            board.addEntity(pos,stringToEntity(input));
        }


        return board;
    }

    static void saveLevel(Board board, int currentLevel){
        vector<string> res;
        res.push_back(to_string(currentLevel));
        int height = board.getHeight();
        int width = board.getWidth();
        stringstream ss;
        ss << to_string(width-2) << " " << to_string(height-2);
        res.push_back(ss.str());
        for (int i = 1; i < height-1; ++i) {
            for (int j = 1; j < width-1; ++j) {
                Position pos{i,j};
                vector<Entity> entities = board.getEntities(pos);
                for (int k = 0; k < entities.size(); ++k) {
                    stringstream ss2;
                    ss2 << entityToString(entities[k]) << " " << to_string(j-1) << " " << to_string(i-1);
                    res.push_back(ss2.str());
                }
            }
        }
        ofstream myFile("../levels/backup.txt", ios::out | ios::trunc);

        if (myFile.is_open()) {
            for (const auto& str : res) {
                myFile.write(str.c_str(), str.length());
                myFile.write("\n", 1);
            }
            myFile.close();
        }
        else {
            cout << "Unable to open file";
        }
    }

    static pair<Board,int> reloadLevel(){
        string filename{"../levels/backup.txt"};
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

        int currentLevel{stoi(lines.at(0))};

        //construction du board
        vector<string> sizeBoard;
        stringstream ssBoard{lines.at(1)};
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
        for (int i = 2; i < lines.size(); ++i) {
            vector<string> result;
            stringstream ssResult{lines.at(i)};
            string token;
            while (getline(ssResult, token, ' ')) {
                result.push_back(token);
            }
            Position pos {stoi(result.at(2))+1,stoi(result.at(1))+1};

            string input = result.at(0);

            board.addEntity(pos,stringToEntity(input));
        }


        return make_pair(board,currentLevel);
    }
};

#endif // LEVELLOADER_H
