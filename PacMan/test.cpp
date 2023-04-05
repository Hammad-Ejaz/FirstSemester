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
    {"||.. .....................................................  ......  ||"},
    {"||.. %%%%%%%%%%%%%%%%        ...     %%%%%%%%%%%%%%  |%|..   %%%%   ||"},
    {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
    {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
    {"||..        %%%%%%%%  . . |%|...     %%%%%%%%%%%%%%     ..   %%%%.  ||"},
    {"||..        |%|       . . |%|...    ............... |%| ..       .  ||"},
    {"||..        %%%%%%%%%%. . |%|...    %%%%%%%%%%%%    |%| ..   %%%%.  ||"},
    {"||..               |%|.             |%|......       |%| ..    |%|.  ||"},
    {"||..     ......... |%|.        P    |%|......|%|        ..    |%|.  ||"},
    {"||..|%|  |%|%%%|%|.|%|. |%|            ......|%|        ..|%| |%|.  ||"},
    {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|         .|%|.      ||"},
    {"||..|%|  |%|   |%|..           ...|%|     %%%%%%        . |%|.      ||"},
    {"||..|%|            .           ...|%|               |%| ..|%|.      ||"},
    {"||..|%|  %%%%%%%%%%%%%%        ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
    {"||......g........................................   |%| ..........  ||"},
    {"||   ............................................          .......  ||"},
    {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|    |%| ..|%|.      ||"},
    {"||..|%|  |%|   |%|..           ...|%|     %%%%%%    |%| ..|%|.      ||"},
    {"||..|%|            .     G     ...|%|               |%| ..|%|.      ||"},
    {"||..|%|  %%%%%%%%%%%%%%        ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
    {"||...............................................   |%| ..........  ||"},
    {"||  .............................................          .......  ||"}, 
    {"##################################################################### "}
};

int pacmanX = 9;  // X Coordinate of Pacman
int pacmanY = 31; // Y Coordinate of Pacman
int score = 0;

int ghost1X = 19;  // X Coordinate of Ghost1
int ghost1Y = 25;  // Y Coordinate of Ghost1
int ghost2X = 15;  // X Coordinate of Ghost1
int ghost2Y = 8;  // Y Coordinate of Ghost1
int ghost3X = 19;  // X Coordinate of Ghost1
int ghost3Y = 25;  // Y Coordinate of Ghost1
int ghost4X = 19;  // X Coordinate of Ghost1
int ghost4Y = 25;  // Y Coordinate of Ghost1
int randomMove3 = 1;
int randomMove4 = 1;
char previousItem1 = ' ';
char previousItem2 = '.';
int previousMove = -1;

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
double dist(int, int, int, int);
int getMinIndex(double [], int);

// Main Function
main()
{
    // loadMaze();
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD destCoord;
    destCoord.X = 0;
    destCoord.Y = 0;
    bool gameRunning = true;
    system("cls");
    while (gameRunning)
    {
        Sleep(100);
        // system("CLS");
        SetConsoleCursorPosition(hStdout, destCoord);
        printMaze();
        // gameRunning = ghost1Movement() && ghost2Movement() && ghost3Movement() && ghost4Movement();
        gameRunning = ghost1Movement() && ghost2Movement();
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
}

void printScore()
{
    cout << endl << "Score: " << score << endl;
}

void movePacmanLeft()
{
    if (maze[pacmanX][pacmanY - 1] == ' ' || maze[pacmanX][pacmanY - 1] == '.')
    {
                  
        maze[pacmanX][pacmanY] = ' ';
        pacmanY = pacmanY - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}

void movePacmanRight()
{
    if (maze[pacmanX][pacmanY + 1] == ' ' || maze[pacmanX][pacmanY + 1] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        pacmanY = pacmanY + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}

void movePacmanUp()
{
    if (maze[pacmanX - 1][pacmanY] == ' ' || maze[pacmanX - 1][pacmanY] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        pacmanX = pacmanX - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}

void movePacmanDown()
{
    if (maze[pacmanX + 1][pacmanY] == ' ' || maze[pacmanX + 1][pacmanY] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        pacmanX = pacmanX + 1;
        if (maze[pacmanX][pacmanY] == '.')
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
    if(maze[ghost1X][ghost1Y - 1] == ' ' || maze[ghost1X][ghost1Y - 1] == '.' || maze[ghost1X][ghost1Y - 1] == 'P'){
        distances[0] = dist(pacmanX, pacmanY, ghost1X, ghost1Y - 1);
    } 
    // Can move down?
    if(maze[ghost1X][ghost1Y + 1] == ' ' || maze[ghost1X][ghost1Y + 1] == '.' || maze[ghost1X][ghost1Y + 1] == 'P'){
        distances[1] = dist(pacmanX, pacmanY, ghost1X, ghost1Y + 1);
    }
    // Can move left?
    if(maze[ghost1X - 1][ghost1Y] == ' ' || maze[ghost1X - 1][ghost1Y] == '.' || maze[ghost1X - 1][ghost1Y] == 'P'){
        distances[2] = dist(pacmanX, pacmanY, ghost1X - 1, ghost1Y);
    }
    // Can move right?
    if(maze[ghost1X + 1][ghost1Y] == ' ' || maze[ghost1X + 1][ghost1Y] == '.' || maze[ghost1X + 1][ghost1Y] == 'P'){
        distances[3] = dist(pacmanX, pacmanY, ghost1X + 1, ghost1Y);
    }

    int m = getMinIndex(distances, previousMove) + 1;
    previousMove = m;

    return m;
}

bool ghost1Movement()
{
    int value = ghost1Direction();
    if (value == 1) // UP
    {
        if (maze[ghost1X][ghost1Y - 1] == ' ' || maze[ghost1X][ghost1Y - 1] == '.' || maze[ghost1X][ghost1Y - 1] == 'P')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            ghost1Y = ghost1Y - 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (previousItem1 == 'P')
            {
                return 0;
            }
            maze[ghost1X][ghost1Y] = 'G';
        }
    }
    if (value == 2) // DOWN
    {
        if (maze[ghost1X][ghost1Y + 1] == ' ' || maze[ghost1X][ghost1Y + 1] == '.' || maze[ghost1X][ghost1Y + 1] == 'P')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            ghost1Y = ghost1Y + 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (previousItem1 == 'P')
            {
                return 0;
            }
            maze[ghost1X][ghost1Y] = 'G';
        }
    }
    if (value == 3) // LEFT
    {
        if (maze[ghost1X - 1][ghost1Y] == ' ' || maze[ghost1X - 1][ghost1Y] == '.' || maze[ghost1X - 1][ghost1Y] == 'P')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            ghost1X = ghost1X - 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (previousItem1 == 'P')
            {
                return 0;
            }
            maze[ghost1X][ghost1Y] = 'G';
        }
    }
    if (value == 4) // RIGHT
    {
        if (maze[ghost1X + 1][ghost1Y] == ' ' || maze[ghost1X + 1][ghost1Y] == '.' || maze[ghost1X + 1][ghost1Y] == '.')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            ghost1X = ghost1X + 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (previousItem1 == 'P')
            {
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
        if (maze[ghost2X][ghost2Y - 1] == ' ' || maze[ghost2X][ghost2Y - 1] == '.' || maze[ghost2X][ghost2Y - 1] == 'P')
        {
            maze[ghost2X][ghost2Y] = previousItem2;
            ghost2Y = ghost2Y - 1;
            previousItem2 = maze[ghost2X][ghost2Y];
            if (previousItem2 == 'P')
            {
                return 0;
            }
            maze[ghost2X][ghost2Y] = 'g';
        }
    }
    if (value == 2) // DOWN
    {
        if (maze[ghost2X][ghost2Y + 1] == ' ' || maze[ghost2X][ghost2Y + 1] == '.' || maze[ghost2X][ghost2Y + 1] == 'P')
        {
            maze[ghost2X][ghost2Y] = previousItem2;
            ghost2Y = ghost2Y + 1;
            previousItem2 = maze[ghost2X][ghost2Y];
            if (previousItem2 == 'P')
            {
                return 0;
            }
            maze[ghost2X][ghost2Y] = 'g';
        }
    }
    if (value == 3) // LEFT
    {
        if (maze[ghost2X - 1][ghost2Y] == ' ' || maze[ghost2X - 1][ghost2Y] == '.' || maze[ghost2X - 1][ghost2Y] == 'P')
        {
            maze[ghost2X][ghost2Y] = previousItem2;
            ghost2X = ghost2X - 1;
            previousItem2 = maze[ghost2X][ghost2Y];
            if (previousItem2 == 'P')
            {
                return 0;
            }
            maze[ghost2X][ghost2Y] = 'g';
        }
    }
    if (value == 4) // RIGHT
    {
        if (maze[ghost2X + 1][ghost2Y] == ' ' || maze[ghost2X + 1][ghost2Y] == '.' || maze[ghost2X + 1][ghost2Y] == '.')
        {
            maze[ghost2X][ghost2Y] = previousItem2;
            ghost2X = ghost2X + 1;
            previousItem2 = maze[ghost2X][ghost2Y];
            if (previousItem2 == 'P')
            {
                return 0;
            }
            maze[ghost2X][ghost2Y] = 'g';
        }
    }
    return 1;
}

bool ghost3Movement(){ // Vertically
    if(ghost3X > 0 && ghost3X < 23){
        if(maze[ghost3X + randomMove3][ghost3Y] != ' '){
            randomMove3=randomMove3* -1;
        }
        else {
            maze[ghost3X][ghost3Y] = ' ';
            ghost3X = ghost3X + randomMove3;
            if(maze[ghost3X][ghost3Y] == 'P'){
                return false;
            }
            maze[ghost3X][ghost3Y] = 'G';
        }
    }

    return true;
}

bool ghost4Movement(){ // Horizontally
    if(ghost4Y > 1 && ghost4Y < 69){
        if(maze[ghost4Y][ghost4Y + randomMove4] != ' '){
            randomMove4 *= -1;
        }
        else {
            maze[ghost4X][ghost4Y] = ' ';
            ghost4Y = ghost4Y + randomMove4;
            if(maze[ghost4X][ghost4Y] == 'P'){
                return false;
            }
            maze[ghost4X][ghost4Y] = 'G';
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
        }
        i++;
    }
    file >> score;
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
    file << score;
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
