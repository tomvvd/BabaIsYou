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
        ss << "../levels/level_" << nb << ".txt"; //chemin commençant à l'endroit de l'exécutable
        string filename = ss.str();

        ifstream file(filename); // ouverture du fichier en mode lecture

        if (file.is_open()) { // vérifie si le fichier est ouvert
            string line;
            while (getline(file, line)) { // lit chaque ligne du fichier
                cout << line << endl; // affiche la ligne lue
            }
            file.close(); // fermeture du fichier
        }

        else {
            cerr << "Impossible d'ouvrir le fichier " << filename << endl;
        }

        return Board{2,4}; //pour pas que le compilateur casse les ****
    }
};

#endif // LEVELLOADER_H
