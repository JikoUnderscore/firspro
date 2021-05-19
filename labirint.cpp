#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;


void zaredi_karta(char labirint[8][8]) {
    ifstream mapFile;
    string lineOfFIle;

    // chose a map
    int chosenLevel;
    string levelname;

    while (true) {
        cout << "-----------------------------\n";
        cout << "Chose a map from the list:\n";
        cout << "-----------------------------\n"
                "[0] Level 1\n"
                "[1] Level 2\n";
        cout << "-----------------------------\n";
        cin >> chosenLevel;
        if (chosenLevel == 1 || chosenLevel == 0) {
            break;
        }
    }

    switch (chosenLevel) {
        case 1:
            levelname = "../maps/simple88.txt"; // cheat ssssddwdwwwddsssssaa
            break;
        case 0:
            levelname = "../maps/old88.txt"; // cheat sssssddddwwdw
            break;
        default:
            levelname = "../maps/old88.txt";
    }

    int kolona = 0;

    mapFile.open(levelname);
        while (getline(mapFile, lineOfFIle)) {
            for (int red = 0; red < lineOfFIle.length(); ++red) {
                // cout << red << " |" << lineOfFIle[red] << "| " << kolona << endl;
                labirint[kolona][red] = lineOfFIle[red];
            }
            kolona++;
        }
    mapFile.close();


}


char LABIRINT[8][8] = {
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'}
};


void show_map(int posOfCharacerX, int posOfCharecterY, int losX, int losY) {
    char ig = '@';
    char labirint[8][8];

    // make a copy of the LABIRINT
    for (int red = 0; red < 8; red++) {
        for (int colona = 0; colona < 8; colona++) {
            labirint[red][colona] = LABIRINT[red][colona];
        }
    }

    // plase charecter in labirint
    labirint[posOfCharecterY + 1][posOfCharacerX + 1] = ig;

    // print out the Line of sight of the charekter
    // prints the labirint
    for (int x = 0 + posOfCharecterY; x < losX; x++) {
        for (int y = 0 + posOfCharacerX; y < losY; y++) {
            cout << " " << labirint[x][y] << " ";
        }
        cout << "\n";
    }
}


int main() {
    zaredi_karta(LABIRINT);
    // full map
    // show_map(0, 0, 8, 8);

    int numberOfLives = 1;
    int movex = 0, movey = 0;
    char move;
    cout << endl;

    // shot the starting posision
    show_map(0, 0, 3, 3);

    int lives = 35;
    while (numberOfLives < lives) {

        cout << "Use 'wasd' and 'Enter' to move!\n";
        cin >> move;
        if (move == 'w') {
            movey -= 1;
        }
        else if (move == 's') {
            movey += 1;
        }
        else if (move == 'a') {
            movex -= 1;
        }
        else if (move == 'd') {
            movex += 1;
        }
        else {
            cout << move << " is not a valid movement\n";
        }

        cout << "moves left " << lives - numberOfLives - 1 << endl;

        if (LABIRINT[movey + 1][movex + 1] == '|' ||
            LABIRINT[movey + 1][movex + 1] == '-' ||
            LABIRINT[movey + 1][movex + 1] == '+' ||
            LABIRINT[movey + 1][movex + 1] == 'S') {
            cout << ">>>>> YOU CAN NOT MOVE THERE!!! <<<<<\n";

            // enters the wall and needs to return to the last posision
            if (move == 'w') {
                movey += 1;
            }
            else if (move == 's') {
                movey -= 1;
            }
            else if (move == 'a') {
                movex += 1;
            }
            else if (move == 'd') {
                movex -= 1;
            }
        }
        else if (LABIRINT[movey + 1][movex + 1] == 'F') {
            cout << "YOU FOIND THE EXIT\n";
            break;
        }
        show_map(movex, movey, 3 + movey, 3 + movex);

        numberOfLives++;
    }

    if (lives - numberOfLives - 1 <= 1) {
        cout << " you lost!!\n";
    }


}
