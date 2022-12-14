#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <cstdlib>

using namespace std;
 
int score = 30;
int fruit_y, fruit_x;
int t_raw = 1, t_column = 1;
int gameOver = 0;

vector <char> direction{ 'd' ,'d' };

void displayArray(char arr[20][20]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void fruit_coordinates(char arr[20][20]) {
    srand(static_cast<unsigned int>(time(0)));
    fruit_x = rand() % 20;
    if (fruit_x == 0) fruit_x++;
    else if (fruit_x == 19) fruit_x--;

    fruit_y = rand() % 20;
    if (fruit_y == 0) fruit_y++;
    else if (fruit_y == 19) fruit_y--;

    if (arr[fruit_x][fruit_y] != ' ') fruit_coordinates(arr);

}
void tailCoordinates(char arr[20][20]) {
    switch (direction[0]) {
    case 'd':
        t_column++;
        break;
    case 'a':
        t_column--;
        break;
    case 'w':
        t_raw--;
        break;
    case 's':
        t_raw++;
        break;
    }
    direction.erase(direction.begin());
}

void upMovement(char arr[20][20], int* raw, int* column) {
    if (arr[*raw - 1][*column] == arr[fruit_x][fruit_y]) {
        score += 10;
        fruit_coordinates(arr);
    }
    else {
        arr[t_raw][t_column] = ' ';
        tailCoordinates(arr);
    }
    if (arr[*raw - 1][*column] != '*') {
        arr[*raw - 1][*column] = '*';
        *raw = *raw - 1;
    }
    else gameOver = 1;
}
void downMovement(char arr[20][20], int* raw, int* column) {
    if (arr[*raw + 1][*column] == arr[fruit_x][fruit_y]) {
        score += 10;
        fruit_coordinates(arr);
    }
    else {
        arr[t_raw][t_column] = ' ';
        tailCoordinates(arr);
    }
    if (arr[*raw + 1][*column] != '*') {
        arr[*raw + 1][*column] = '*';
        *raw = *raw + 1;
    }
    else gameOver = 1;
}
void leftMovement(char arr[20][20], int* raw, int* column) {
    if (arr[*raw][*column - 1] == arr[fruit_x][fruit_y]) {
        score += 10;
        fruit_coordinates(arr);
    }
    else {
        arr[t_raw][t_column] = ' ';
        tailCoordinates(arr);
    }
    if (arr[*raw][*column - 1] != '*') {
        arr[*raw][*column - 1] = '*';
        *column = *column - 1;
    }
    else gameOver = 1;
}
void rightMovement(char arr[20][20], int* raw, int* column) {
    if (arr[*raw][*column + 1] == arr[fruit_x][fruit_y]) {
        score += 10;
        fruit_coordinates(arr);
    }
    else {
        arr[t_raw][t_column] = ' ';
        tailCoordinates(arr);
    }
    if (arr[*raw][*column + 1] != '*') {
        arr[*raw][*column + 1] = '*';
        *column = *column + 1;
    }
    else gameOver = 1;
}


void keypress(char& key) {
    if (_kbhit()) {
        switch (_getch()) {
        case  'a':
            key = 'a';
            break;
        case 's':
            key = 's';
            break;
        case 'w':
            key = 'w';
            break;
        case 'd':
            key = 'd';
            break;
        }
    }
}

void process(char key, char arr[20][20], int* h_raw, int* h_column) {
    direction.push_back(key);
    switch (key) {
    case 'w':
        upMovement(arr, h_raw, h_column);
        break;
    case 's':
        downMovement(arr, h_raw, h_column);
        break;
    case 'a':
        leftMovement(arr, h_raw, h_column);
        break;
    case 'd':
        rightMovement(arr, h_raw, h_column);
        break;
    }

}

int main() {
    char arr[20][20];
    int level,speed;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 0 || i == 19 || j == 0 || j == 19) {
                arr[i][j] = '#';
            }
            else { arr[i][j] = ' '; }
        }
    }
    arr[1][1] = '*'; arr[1][2] = '*'; arr[1][3] = '*';
    cout << "Snake moves with w,a,s,d letters!" << endl
        << "Please select the level of game:" << endl
        << "1) Expert." << "\n2) Hard." << "\n3) Medium." << "\n4) Easy." << endl;
    cin >> level;
    switch (level) {
    case 1:
        speed = 10;
        break;
    case 2:
        speed = 50;
        break;
    case 3:
        speed = 100;
        break;
    case 4:
        speed = 150;
        break;
    }
    int h_raw = 1;
    int h_column = 3;
    char key = 'd';
    fruit_coordinates(arr);
    while (h_raw > 0 && h_column < 19 && h_raw < 19 && h_column > 0 && gameOver == 0) {
        arr[fruit_x][fruit_y] = '0';
        keypress(key);
        Sleep(speed);
        process(key, arr, &h_raw, &h_column);
        system("cls");
        cout << "Y0ur score is: " << score << endl;
        displayArray(arr);

    }

    cout << "\nGame over!\n";
    cout << "Final score:" << score << endl << endl;
    cout << "Press any key in order to exit:";
    _getch();
    return 0;
}
