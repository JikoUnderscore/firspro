#include <iostream>
#include <fstream>
#include <string>

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
                "[0] simple\n"
                "[1] old\n";
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
    system("cls");
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
    bool isWallHit = false;
    char move;


    // shot the starting posision
    show_map(0, 0, 3, 3);

    int lives = 35;
    while (numberOfLives < lives) {
        cout << "moves left " << lives - numberOfLives - 1 << endl;
        cout << "Use 'wasd' and 'Enter' to move!\n";
        if (isWallHit) {
            isWallHit = false;
            cout << ">>>>> YOU CAN NOT MOVE THERE!!! <<<<<\n";
        }
        cout << endl;
        cin >> move;

        switch (move) {
            case 'w':
                movey -= 1;
                break;
            case 's':
                movey += 1;
                break;
            case 'a':
                movex -= 1;
                break;
            case 'd':
                movex += 1;
                break;
            default:
                cout << move << " is not a valid movement\n";
        }


        if (LABIRINT[movey + 1][movex + 1] == '|' ||
            LABIRINT[movey + 1][movex + 1] == '-' ||
            LABIRINT[movey + 1][movex + 1] == '+' ||
            LABIRINT[movey + 1][movex + 1] == 'S') {
            isWallHit = true;

            // enters the wall and needs to return to the last posision
            switch (move) {
                case 'w':
                    movey += 1;
                    break;
                case 's':
                    movey -= 1;
                    break;
                case 'a':
                    movex += 1;
                    break;
                case 'd':
                    movex -= 1;
                    break;
                default:
                    cout << move << " oh-oh";
            }
        } else if (LABIRINT[movey + 1][movex + 1] == 'F') {
            cout << "YOU FOIND THE EXIT\n";
            break;
        }
        show_map(movex, movey, 3 + movey, 3 + movex);

        numberOfLives++;

    }

    if (lives - numberOfLives - 1 <= 1) {
        cout << " you lost!!\n";
    }
    system("pause");

}
