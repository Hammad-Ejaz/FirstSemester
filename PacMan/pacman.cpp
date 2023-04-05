#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <windows.h>
using namespace std;

// Global Variable
const int mazeRows = 24;
const int mazeCols = 71;
char maze[mazeRows][mazeCols] = {
    {"##################################################################### "},
    {"||o. .....................................................  ......  ||"},
    {"||.. %%%%%%%%%%%%%%%%        ...     %%%%%%%%%%%%%%  |%|..   %%%%   ||"},
    {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
    {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
    {"||..        %%%%%%%%  . . |%|...     %%%%%%%%%%%%%%     ..   %%%%.  ||"},
    {"||..        |%|       . . |%|...    ...........o... |%| ..       .  ||"},
    {"||..        %%%%%%%%%%. . |%|...    %%%%%%%%%%%%    |%| ..   %%%%.  ||"},
    {"||..   Y           |%|.             |%|......       |%| ..    |%|.  ||"},
    {"||..     ....o.... |%|.        P    |%|......|%|        ..    |%|.  ||"},
    {"||..|%|  |%|%%%|%|.|%|. |%|            ......|%|        ..|%| |%|.  ||"},
    {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|         .|%|.      ||"},
    {"||..|%|  |%|   |%|..           ...|%|     %%%%%%        . |%|.      ||"},
    {"||..|%|            .           ...|%|               |%| ..|%|.      ||"},
    {"||..|%|  %%%%%%%%%%%%%%        ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
    {"||......g........................................   |%| ........o.  ||"},
    {"||   .............................X..............          .......  ||"},
    {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|    |%| ..|%|.      ||"},
    {"||..|%|  |%|   |%|..           ...|%|     %%%%%%    |%| ..|%|.      ||"},
    {"||..|%|            .     G     ...|%|               |%| ..|%|.      ||"},
    {"||..|%|  %%%%%%%%%%%%%%        ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
    {"||...............................................   |%| ..........  ||"},
    {"||  ..................................o..........          .......  ||"}, 
    {"##################################################################### "}
};

int pacmanX = 9;  // X Coordinate of Pacman
int pacmanY = 31; // Y Coordinate of Pacman
int score = 0;

int ghost1X = 19;  // X Coordinate of Ghost1
int ghost1Y = 25;  // Y Coordinate of Ghost1
int ghost2X = 15;  // X Coordinate of Ghost1
int ghost2Y = 8;  // Y Coordinate of Ghost1
int ghost3X = 8;  // X Coordinate of Ghost1
int ghost3Y = 7;  // Y Coordinate of Ghost1
int ghost4X = 16;  // X Coordinate of Ghost1
int ghost4Y = 34;  // Y Coordinate of Ghost1
int randomMove3 = 1;
int randomMove4 = 1;
char previousItem1 = ' ';
char previousItem2 = '.';
char previousItem3 = ' ';
char previousItem4 = '.';
int previousMove = -1;
int lifes = 3;
int energizerIterations = 0;

void loadMaze();
void saveMaze();
void printMaze();
bool ghost1Movement();
bool ghost2Movement();
bool ghost3Movement();
bool ghost4Movement();
void printScore();
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
void resetPacMan();
double dist(int, int, int, int);
int getMinIndex(double [], int);

// Main Function
main()
{
    loadMaze();
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD destCoord;
    destCoord.X = 0;
    destCoord.Y = 0;
    bool gameRunning = true;
    system("cls");
    while (gameRunning || lifes > 0)
    {
        Sleep(100);
        // system("CLS");
        SetConsoleCursorPosition(hStdout, destCoord);
        printMaze();
        gameRunning = ghost1Movement() && ghost2Movement() && ghost3Movement() && ghost4Movement();
        printScore();
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePacmanLeft(); // Function call to move Pacman towards left
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePacmanRight(); // Function call to move Pacman towards right
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePacmanUp(); // Function call to move Pacman towards up
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePacmanDown(); // Function call to move Pacman towards down
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gameRunning = false; // Stop the game
        }
        saveMaze();
        energizerIterations--;
    }
}

void printMaze()
{
    for (int row = 0; row < 24; row = row + 1)
    {
        for (int col = 0; col < 71; col = col + 1)
        {
            cout << maze[row][col];
        }
        cout << endl;
    }
}

void calculateScore()
{
    score = score + 1;
    if(maze[pacmanX][pacmanY] == 'o') energizerIterations = 30;
}

void printScore()
{
    cout << endl << "Score: " << score << endl;
    cout << "Lifes: " << lifes << endl;
}

void movePacmanLeft()
{
    if (maze[pacmanX][pacmanY - 1] == ' ' || maze[pacmanX][pacmanY - 1] == '.' || maze[pacmanX][pacmanY - 1] == 'o')
    {
                  
        maze[pacmanX][pacmanY] = ' ';
        pacmanY = pacmanY - 1;
        if (maze[pacmanX][pacmanY] == '.' || maze[pacmanX][pacmanY] == 'o')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}

void movePacmanRight()
{
    if (maze[pacmanX][pacmanY + 1] == ' ' || maze[pacmanX][pacmanY + 1] == '.' || maze[pacmanX][pacmanY + 1] == 'o')
    {
        maze[pacmanX][pacmanY] = ' ';
        pacmanY = pacmanY + 1;
        if (maze[pacmanX][pacmanY] == '.' || maze[pacmanX][pacmanY] == 'o')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}

void movePacmanUp()
{
    if (maze[pacmanX - 1][pacmanY] == ' ' || maze[pacmanX - 1][pacmanY] == '.' || maze[pacmanX - 1][pacmanY] == 'o')
    {
        maze[pacmanX][pacmanY] = ' ';
        pacmanX = pacmanX - 1;
        if (maze[pacmanX][pacmanY] == '.' || maze[pacmanX][pacmanY] == 'o')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}

void movePacmanDown()
{
    if (maze[pacmanX + 1][pacmanY] == ' ' || maze[pacmanX + 1][pacmanY] == '.' || maze[pacmanX + 1][pacmanY] == 'o')
    {
        maze[pacmanX][pacmanY] = ' ';
        pacmanX = pacmanX + 1;
        if (maze[pacmanX][pacmanY] == '.' || maze[pacmanX][pacmanY] == 'o')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}

int ghost1Direction()
{
    // srand(time(0));
    // int result = 1 + (rand() % 4);
    // return result;

    double distances[4] = {99999999, 99999999, 99999999, 99999999};

    // Can move up?
    if(maze[ghost1X][ghost1Y - 1] == ' ' || maze[ghost1X][ghost1Y - 1] == '.' || maze[ghost1X][ghost1Y - 1] == 'P' || maze[ghost1X][ghost1Y - 1] == 'o'){
        distances[0] = dist(pacmanX, pacmanY, ghost1X, ghost1Y - 1);
    } 
    // Can move down?
    if(maze[ghost1X][ghost1Y + 1] == ' ' || maze[ghost1X][ghost1Y + 1] == '.' || maze[ghost1X][ghost1Y + 1] == 'P' || maze[ghost1X][ghost1Y + 1] == 'o'){
        distances[1] = dist(pacmanX, pacmanY, ghost1X, ghost1Y + 1);
    }
    // Can move left?
    if(maze[ghost1X - 1][ghost1Y] == ' ' || maze[ghost1X - 1][ghost1Y] == '.' || maze[ghost1X - 1][ghost1Y] == 'P' || maze[ghost1X - 1][ghost1Y] == 'o'){
        distances[2] = dist(pacmanX, pacmanY, ghost1X - 1, ghost1Y);
    }
    // Can move right?
    if(maze[ghost1X + 1][ghost1Y] == ' ' || maze[ghost1X + 1][ghost1Y] == '.' || maze[ghost1X + 1][ghost1Y] == 'P' || maze[ghost1X + 1][ghost1Y] == 'o'){
        distances[3] = dist(pacmanX, pacmanY, ghost1X + 1, ghost1Y);
    }

    int m = getMinIndex(distances, previousMove);
    previousMove = m;

    return m + 1;
}

bool ghost1Movement()
{
    int value = ghost1Direction();
    if (value == 1) // UP
    {
        if (maze[ghost1X][ghost1Y - 1] == ' ' || maze[ghost1X][ghost1Y - 1] == '.' || maze[ghost1X][ghost1Y - 1] == 'P' || maze[ghost1X][ghost1Y - 1] == 'o')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            ghost1Y = ghost1Y - 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (previousItem1 == 'P')
            {
                previousItem1 = ' ';
                lifes--;
                resetPacMan();
                return 0;
            }
            maze[ghost1X][ghost1Y] = 'G';
        }
    }
    if (value == 2) // DOWN
    {
        if (maze[ghost1X][ghost1Y + 1] == ' ' || maze[ghost1X][ghost1Y + 1] == '.' || maze[ghost1X][ghost1Y + 1] == 'P' || maze[ghost1X][ghost1Y + 1] == 'o')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            ghost1Y = ghost1Y + 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (previousItem1 == 'P')
            {
                previousItem1 = ' ';
                lifes--;
                resetPacMan();
                return 0;
            }
            maze[ghost1X][ghost1Y] = 'G';
        }
    }
    if (value == 3) // LEFT
    {
        if (maze[ghost1X - 1][ghost1Y] == ' ' || maze[ghost1X - 1][ghost1Y] == '.' || maze[ghost1X - 1][ghost1Y] == 'P' || maze[ghost1X - 1][ghost1Y] == 'o')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            ghost1X = ghost1X - 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (previousItem1 == 'P')
            {
                previousItem1 = ' ';
                lifes--;
                resetPacMan();
                return 0;
            }
            maze[ghost1X][ghost1Y] = 'G';
        }
    }
    if (value == 4) // RIGHT
    {
        if (maze[ghost1X + 1][ghost1Y] == ' ' || maze[ghost1X + 1][ghost1Y] == '.' || maze[ghost1X + 1][ghost1Y] == 'P' || maze[ghost1X + 1][ghost1Y] == 'o')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            ghost1X = ghost1X + 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (previousItem1 == 'P')
            {
                previousItem1 = ' ';
                lifes--;
                resetPacMan();
                return 0;
            }
            maze[ghost1X][ghost1Y] = 'G';
        }
    }
    return 1;
}

int ghost2Direction()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}

bool ghost2Movement()
{
    int value = ghost2Direction();
    if (value == 1) // UP
    {
        if (maze[ghost2X][ghost2Y - 1] == ' ' || maze[ghost2X][ghost2Y - 1] == '.' || maze[ghost2X][ghost2Y - 1] == 'P' || maze[ghost2X][ghost2Y - 1] == 'o')
        {
            maze[ghost2X][ghost2Y] = previousItem2;
            ghost2Y = ghost2Y - 1;
            previousItem2 = maze[ghost2X][ghost2Y];
            if (previousItem2 == 'P')
            {
                previousItem2 = ' ';
                lifes--;
                resetPacMan();
                return 0;
            }
            maze[ghost2X][ghost2Y] = 'g';
        }
    }
    if (value == 2) // DOWN
    {
        if (maze[ghost2X][ghost2Y + 1] == ' ' || maze[ghost2X][ghost2Y + 1] == '.' || maze[ghost2X][ghost2Y + 1] == 'P' || maze[ghost2X][ghost2Y + 1] == 'o')
        {
            maze[ghost2X][ghost2Y] = previousItem2;
            ghost2Y = ghost2Y + 1;
            previousItem2 = maze[ghost2X][ghost2Y];
            if (previousItem2 == 'P')
            {
                previousItem2 = ' ';
                lifes--;
                resetPacMan();
                return 0;
            }
            maze[ghost2X][ghost2Y] = 'g';
        }
    }
    if (value == 3) // LEFT
    {
        if (maze[ghost2X - 1][ghost2Y] == ' ' || maze[ghost2X - 1][ghost2Y] == '.' || maze[ghost2X - 1][ghost2Y] == 'P' || maze[ghost2X - 1][ghost2Y] == 'o')
        {
            maze[ghost2X][ghost2Y] = previousItem2;
            ghost2X = ghost2X - 1;
            previousItem2 = maze[ghost2X][ghost2Y];
            if (previousItem2 == 'P')
            {
                previousItem2 = ' ';
                lifes--;
                resetPacMan();
                return 0;
            }
            maze[ghost2X][ghost2Y] = 'g';
        }
    }
    if (value == 4) // RIGHT
    {
        if (maze[ghost2X + 1][ghost2Y] == ' ' || maze[ghost2X + 1][ghost2Y] == '.' || maze[ghost2X + 1][ghost2Y] == 'P' || maze[ghost2X + 1][ghost2Y] == 'o')
        {
            maze[ghost2X][ghost2Y] = previousItem2;
            ghost2X = ghost2X + 1;
            previousItem2 = maze[ghost2X][ghost2Y];
            if (previousItem2 == 'P')
            {
                previousItem2 = ' ';
                lifes--;
                resetPacMan();
                return 0;
            }
            maze[ghost2X][ghost2Y] = 'g';
        }
    }
    return 1;
}

bool ghost3Movement(){ // Vertically
    if(ghost3X > 0 && ghost3X < 23){
        if(maze[ghost3X + randomMove3][ghost3Y] != ' ' && maze[ghost3X + randomMove3][ghost3Y] != '.' && maze[ghost3X + randomMove3][ghost3Y] != 'P' && maze[ghost3X + randomMove3][ghost3Y] != 'o'){
            randomMove3 *= -1;
        }
        else {
            maze[ghost3X][ghost3Y] = previousItem3;
            ghost3X = ghost3X + randomMove3;
            previousItem3 = maze[ghost3X][ghost3Y];
            if(previousItem3 == 'P'){
                previousItem3 = ' ';
                lifes--;
                resetPacMan();
                return false;
            }
            maze[ghost3X][ghost3Y] = 'Y';
        }
    }

    return true;
}

bool ghost4Movement(){ // Horizontally
    if(ghost4Y > 1 && ghost4Y < 69){
        if(maze[ghost4X][ghost4Y + randomMove4] != ' ' && maze[ghost4X][ghost4Y + randomMove4] != '.' && maze[ghost4X][ghost4Y + randomMove4] != 'P' && maze[ghost4X][ghost4Y + randomMove4] != 'o'){
            randomMove4 *= -1;
        }
        else {
            maze[ghost4X][ghost4Y] = previousItem4;
            ghost4Y = ghost4Y + randomMove4;
            previousItem4 = maze[ghost4X][ghost4Y];
            if(previousItem4 == 'P'){
                previousItem4 = ' ';
                lifes--;
                resetPacMan();
                return false;
            }
            maze[ghost4X][ghost4Y] = 'X';
        }
    }

    return true;
}

void loadMaze(){
    fstream file;
    string line;
    int i = 0;

    file.open("maze.txt", ios::in);
    while(!file.eof() && i < mazeRows){
        getline(file, line);

        for(int j = 0; j < mazeCols; j++){
            maze[i][j] = line[j];

            if(line[j] == 'P'){
                pacmanX = i;
                pacmanY = j;
            }
            else if(line[j] == 'G'){
                ghost1X = i;
                ghost1Y = j;
            }
            else if(line[j] == 'g'){
                ghost2X = i;
                ghost2Y = j;
            }
            else if(line[j] == 'Y'){
                ghost3X = i;
                ghost3Y = j;
            }
            else if(line[j] == 'X'){
                ghost4X = i;
                ghost4Y = j;
            }
        }
        i++;
    }
    file >> score >> lifes >> energizerIterations;
    file.close();
}

void saveMaze(){
    fstream file;

    file.open("maze.txt", ios::out);
    for(int i = 0; i < mazeRows; i++){
        for(int j = 0; j < mazeCols; j++){
            file << maze[i][j];
        }
        file << endl;
    }
    file << score << " " << lifes << " " << energizerIterations;
    file.close();
}

double dist(int x1, int y1, int x2, int y2){
    int s = pow(x1 - x2, 2) + pow(y1 - y2, 2);
    return sqrt(s);
}

int getMinIndex(double arr[], int skip){
    int min = 0;
    if(skip == 0) min = 1;

    for(int i = min + 1; i < 4; i++){
        if(i == skip) continue;
        if(arr[i] < arr[min]){
            min = i;
        }
    }

    if(arr[min] == 99999999){
        min = skip;
    }

    return min;
}

void resetPacMan(){
    if(energizerIterations <= 0){
        pacmanX = 9;
        pacmanY = 31;
        maze[pacmanX][pacmanY] = 'P';
    }
    else {
        lifes++;
    }
}
