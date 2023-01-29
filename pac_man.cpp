#include <iostream>
#include <fstream>
#include <conio.h>
#include <cmath>
#include <iomanip>
#include <windows.h>
#include <time.h>
using namespace std;
char maze[24][71]; //={
//                    {"#####################################################################"},
//                    {"||.. .....................................................  ......  ||"},
//                    {"||.. %%%%%%%%%%%%%%%%        ...     %%%%%%%%%%%%%%  |%|..   %%%%   ||"},
//                    {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
//                    {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
//                    {"||..        %%%%%%%%  . . |%|...     %%%%%%%%%%%%%%     ..   %%%%.  ||"},
//                    {"||..        |%|       . . |%|...    ............... |%| ..       .  ||"},
//                    {"||..        %%%%%%%%%%. . |%|...    %%%%%%%%%%%%    |%| ..   %%%%.  ||"},
//                    {"||..               |%|.             |%|......       |%| ..    |%|.  ||"},
//                    {"||..     ......... |%|.             |%|......|%|        ..    |%|.  ||"},
//                    {"||..|%|  |%|%%%|%|.|%|. |%|            ......|%|        ..|%| |%|.  ||"},
//                    {"||..|%|  |%|   |%|..     %%%%%%%%%%%%  ......|%|         .|%|.      ||"},
//                    {"||..|%|  |%|   |%|..           ...|%|     %%%%%%        . |%|.      ||"},
//                    {"||..|%|            .           ...|%|               |%| ..|%|.      ||"},
//                    {"||..|%|  %%%%%%%%%%%%%         ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
//                    {"||...............................................   |%| ..........  ||"},
//                    {"||   ............................................          .......  ||"},
//                    {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|    |%| ..|%|.      ||"},
//                    {"||..|%|  |%|   |%|..           ...|%|     %%%%%%    |%| ..|%|.      ||"},
//                    {"||..|%|            .           ...|%|               |%| ..|%|.      ||"},
//                    {"||..|%|  %%%%%%%%%%%%%         ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
//                    {"||...............................................   |%| ..........  ||"},
//                    {"||  .............................................          .......  ||"},
//                    {" #####################################################################"}};
/// global variables////////
int pacmanX = 9;
int pacmanY = 31;
int score = 0;
char g_item = ' ';

int ghostX = 19;
int ghostY = 25;
int ghostX2 = 19; // Chasing Pacman
int ghostX3 = 14; // verticle
int ghostY2 = 25; // Chasing Pacman
int ghostY3 = 22; // verticle
int ghostX4 = 16; // horizontal
int ghostY4 = 50; // horizontal
char pre_item = ' ';
char g_item2 = ' ';
char g_item3 = ' ';
char g_item4 = ' ';
int lives = 3;
bool GotEnergizer = false;
int energizerCount = 0;

int direction = 0;
int direction1 = 0;
float Distance[4] = {10000, 10000, 10000, 10000};

///////////prototypes////////////
void display_maze();
void calculate_score();
void print_result();
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
int ghost_direction();
bool ghost_movement();
void storeMazeIntofile();
void loadMazeIntoArray();
void gotoxy(int x, int y);
bool ghost3movement();
bool ghost4movement();
bool ghost2movement();
int Smallestdistance();
void total_lives();
void timer();
main()
{
    loadMazeIntoArray();
    bool gameRunning1 = true;
    bool gameRunning2 = true;
    bool gameRunning3 = true;
    bool gameRunning4 = true;
    system("CLS");
    display_maze();

    gotoxy(pacmanY, pacmanX);
    cout << "P";
    while (gameRunning1 && gameRunning2 && gameRunning3 && gameRunning4)
    {
        Sleep(50);
        print_result();
        total_lives();
        timer();
        gameRunning1 = ghost_movement();
        gameRunning2 = ghost2movement();
        gameRunning3 = ghost3movement();
        gameRunning4 = ghost4movement();

        if (GetAsyncKeyState(VK_LEFT))
        {
            movePacmanLeft();
        }

        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePacmanRight();
        }

        if (GetAsyncKeyState(VK_UP))
        {
            movePacmanUp();
        }

        if (GetAsyncKeyState(VK_DOWN))
        {
            movePacmanDown();
        }

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gameRunning1 = false; // stop the game
        }
        bool total = gameRunning1 && gameRunning2 && gameRunning3 && gameRunning4;
        if (GotEnergizer && energizerCount != 30)
        {
            energizerCount++;
        }
        else if (energizerCount == 30)
        {
            energizerCount = 0;
            GotEnergizer = false;
        }
        if (!total)
        {
            if (lives != 0)
            {
                gameRunning1 = true;
                gameRunning2 = true;
                gameRunning3 = true;
                gameRunning4 = true;
                gotoxy(pacmanY, pacmanX);
                cout << " ";
                pacmanX = 9;
                pacmanY = 31;
                gotoxy(pacmanY, pacmanX);
                cout << "P";
                lives--;
                // Sleep(1000);
            }
        }
    }

    // storeMazeIntofile();
}

void display_maze()
{
    for (int r = 0; r < 24; r++)
    {
        for (int c = 0; c < 71; c++)
        {
            cout << maze[r][c];
        }
        cout << endl;
    }
}

void calculate_score()
{
    score = score + 1;
}

void print_result()
{
    gotoxy(75, 4);
    cout << "Total score: " << score << endl;
}

void movePacmanLeft()
{
    if ((maze[pacmanX][pacmanY - 1] == ' ') || (maze[pacmanX][pacmanY - 1] == '.') || (maze[pacmanX][pacmanY - 1] == 'o'))
    {
        maze[pacmanX][pacmanY] = pre_item;
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY - 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        if (maze[pacmanX][pacmanY] == '.' || maze[pacmanX][pacmanY] == 'o')
        {
            calculate_score();
        }
        if (maze[pacmanX][pacmanY] == 'o')
        {
            GotEnergizer = true;
        }
    }
}

void movePacmanRight()
{
    if ((maze[pacmanX][pacmanY + 1] == ' ') || (maze[pacmanX][pacmanY + 1] == '.') || (maze[pacmanX][pacmanY + 1] == 'o'))
    {
        maze[pacmanX][pacmanY] = pre_item;
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY + 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        if (maze[pacmanX][pacmanY] == '.' || maze[pacmanX][pacmanY] == 'o')
        {
            calculate_score();
        }
        if (maze[pacmanX][pacmanY] == 'o')
        {
            GotEnergizer = true;
        }
    }
}

void movePacmanUp()
{
    if ((maze[pacmanX - 1][pacmanY] == ' ') || (maze[pacmanX - 1][pacmanY] == '.') || (maze[pacmanX - 1][pacmanY] == 'o'))
    {
        maze[pacmanX][pacmanY] = pre_item;
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX - 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        if (maze[pacmanX][pacmanY] == '.' || maze[pacmanX][pacmanY] == 'o')
        {
            calculate_score();
        }
        if (maze[pacmanX][pacmanY] == 'o')
        {
            GotEnergizer = true;
        }
    }
}

void movePacmanDown()
{
    if ((maze[pacmanX + 1][pacmanY] == ' ') || (maze[pacmanX + 1][pacmanY] == '.') || (maze[pacmanX + 1][pacmanY] == 'o'))
    {
        maze[pacmanX][pacmanY] = pre_item;
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX + 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";

        if (maze[pacmanX][pacmanY] == '.' || maze[pacmanX][pacmanY] == 'o')
        {
            calculate_score();
        }
        if (maze[pacmanX][pacmanY] == 'o')
        {
            GotEnergizer = true;
        }
    }
}

int ghost_direction()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}

bool ghost_movement()
{
    int value = ghost_direction();
    if (value == 1)
    {
        if ((maze[ghostX][ghostY - 1] == ' ') || (maze[ghostX][ghostY - 1] == '.') || (maze[ghostX][ghostY - 1] == 'P') || (maze[ghostX][ghostY - 1] == 'o'))
        {
            maze[ghostX][ghostY] = g_item;
            gotoxy(ghostY, ghostX);
            cout << g_item;
            ghostY = ghostY - 1;
            g_item = maze[ghostX][ghostY];
            gotoxy(ghostY, ghostX);
            cout << "G";
        }
    } // move left

    if (value == 2)
    {
        if ((maze[ghostX][ghostY + 1] == ' ') || (maze[ghostX][ghostY + 1] == '.') || (maze[ghostX][ghostY + 1] == 'P') || (maze[ghostX][ghostY + 1] == 'o'))
        {
            maze[ghostX][ghostY] = g_item;
            gotoxy(ghostY, ghostX);
            cout << g_item;
            ghostY = ghostY + 1;
            g_item = maze[ghostX][ghostY];
            gotoxy(ghostY, ghostX);
            cout << "G";

        } // move right
    }

    if (value == 3)
    {
        if ((maze[ghostX - 1][ghostY] == ' ') || (maze[ghostX - 1][ghostY] == '.') || (maze[ghostX - 1][ghostY] == 'P') || (maze[ghostX - 1][ghostY] == 'o'))
        {
            maze[ghostX][ghostY] = g_item;
            gotoxy(ghostY, ghostX);
            cout << g_item;
            ghostX = ghostX - 1;
            g_item = maze[ghostX][ghostY];
            gotoxy(ghostY, ghostX);
            cout << "G";

        } // move up
    }
    if (value == 4)
    {
        if ((maze[ghostX + 1][ghostY] == ' ') || (maze[ghostX + 1][ghostY] == '.') || (maze[ghostX + 1][ghostY] == 'P') || (maze[ghostX + 1][ghostY] == 'o'))
        {
            maze[ghostX][ghostY] = g_item;
            gotoxy(ghostY, ghostX);
            cout << g_item;
            ghostX = ghostX + 1;
            g_item = maze[ghostX][ghostY];
            gotoxy(ghostY, ghostX);
            cout << "G";
            maze[ghostX][ghostY] = 'G';
        }
    } // move down
    if (pacmanX == ghostX && pacmanY == ghostY && GotEnergizer)
    {
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        ghostX = 19;
        ghostY = 25;
        gotoxy(ghostY, ghostX);
        cout << "G";
        return 1;
    }
    if (pacmanX == ghostX && pacmanY == ghostY)
    {
        gotoxy(ghostY, ghostX);
        cout << "G";
        return 0;
    }
    return 1;
}

void storeMazeIntofile()
{
    fstream file;
    file.open("maze.txt", ios ::out);
    for (int r = 0; r < 24; r++)
    {
        if (r > 0)
        {
            file << endl;
        }
        for (int c = 0; c < 71; c++)
        {
            file << maze[r][c];
        }
    }
    file.close();
}

void loadMazeIntoArray()
{
    string line;
    fstream file;
    file.open("maze.txt", ios::in);
    for (int r = 0; r < 24; r++)
    {
        getline(file, line);
        for (int c = 0; c < 71; c++)
        {
            maze[r][c] = line[c];
            if (maze[r][c] == 'P')
            {
                pacmanX = r;
                pacmanY = c;
            }
            if (maze[r][c] == 'G')
            {
                ghostX = r;
                ghostY = c;
            }
        }
    }
    file.close();
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

bool ghost3movement()
{
    if (direction == 0)
    {
        if ((maze[ghostX3 - 1][ghostY3] == ' ') || (maze[ghostX3 - 1][ghostY3] == '.') || (maze[ghostX3 - 1][ghostY3] == 'P') || (maze[ghostX3 - 1][ghostY3] == 'o'))
        {
            gotoxy(ghostY3, ghostX3);
            cout << g_item3;
            ghostX3 = ghostX3 - 1;
            g_item3 = maze[ghostX3][ghostY3];
            gotoxy(ghostY3, ghostX3);
            cout << "G";
            // cout<<" ";
        }
        else if (maze[ghostX3 - 1][ghostY3] == '#')
        {
            direction = 1;
        }
    }
    if (direction == 1)
    {
        if ((maze[ghostX3 + 1][ghostY3] == ' ') || (maze[ghostX3 + 1][ghostY3] == '.') || (maze[ghostX3 + 1][ghostY3] == 'P') || (maze[ghostX3 + 1][ghostY3] == 'o'))
        {
            gotoxy(ghostY3, ghostX3);
            cout << g_item3;
            ghostX3 = ghostX3 + 1;
            g_item3 = maze[ghostX3][ghostY3];
            gotoxy(ghostY3, ghostX3);
            cout << "G";
        }
        else if (maze[ghostX3 + 1][ghostY3] == '#')
        {
            direction = 0;
        }
    }
    if (pacmanX == ghostX3 && pacmanY == ghostY3 && GotEnergizer)
    {
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        ghostX3 = 14;
        ghostY3 = 22;
        gotoxy(ghostY3, ghostX3);
        cout << "G";
        return 1;
    }
    if (pacmanX == ghostX3 && pacmanY == ghostY3)
    {
        gotoxy(ghostY3, ghostX3);
        cout << "G";
        return 0;
    }

    return 1;
}

// ghost verticel movement

bool ghost4movement()
{
    if (direction1 == 0)
    {
        if ((maze[ghostX4][ghostY4 - 1] == ' ') || (maze[ghostX4][ghostY4 - 1] == '.') || (maze[ghostX4][ghostY4 - 1] == 'P') || (maze[ghostX4][ghostY4 - 1] == 'o'))
        {
            gotoxy(ghostY4, ghostX4);
            cout << g_item4;
            ghostY4 = ghostY4 - 1;
            g_item4 = maze[ghostX4][ghostY4];
            gotoxy(ghostY4, ghostX4);
            cout << "G";
            // cout<<" ";
        }
        else if (maze[ghostX4][ghostY4 - 1] == '|')
        {
            direction1 = 1;
        }
    }
    else if (direction1 == 1)
    {
        if ((maze[ghostX4][ghostY4 + 1] == ' ') || (maze[ghostX4][ghostY4 + 1] == '.') || (maze[ghostX4][ghostY4 + 1] == 'P') || (maze[ghostX4][ghostY4 + 1] == 'o'))
        {
            gotoxy(ghostY4, ghostX4);
            cout << g_item4;
            ghostY4 = ghostY4 + 1;
            g_item4 = maze[ghostX4][ghostY4];
            gotoxy(ghostY4, ghostX4);
            cout << "G";
        }
        else if (maze[ghostX4][ghostY4 + 1] == '|')
        {
            direction1 = 0;
        }
    }
    if (pacmanX == ghostX4 && pacmanY == ghostY4 && GotEnergizer)
    {
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        ghostX4 = 16;
        ghostY4 = 50;
        gotoxy(ghostY4, ghostX4);
        cout << "G";
        return 1;
    }
    if (pacmanX == ghostX4 && pacmanY == ghostY4)
    {
        gotoxy(ghostY4, ghostX4);
        cout << "G";
        return 0;
    }
    return 1;
}
int Smallestdistance()
{
    float smallest = Distance[0];
    int smallestidx = 0;
    for (int i = 0; i < 4; i++)
    {
        if (smallest > Distance[i])
        {
            smallest = Distance[i];
            smallestidx = i;
        }
    }
    return smallestidx;
}
bool ghost2movement()
{
    Distance[0] = 10000;
    Distance[1] = 10000;
    Distance[2] = 10000;
    Distance[3] = 10000;
    if (maze[ghostX2][ghostY2 - 1] == ' ' || maze[ghostX2][ghostY2 - 1] == '.' || maze[ghostX2][ghostY2 - 1] == 'P')
    { // for LEFT movement
        Distance[0] = sqrt(pow((ghostX2 - pacmanX), 2) + pow((ghostY2 - 1 - pacmanY), 2));
    }
    if (maze[ghostX2][ghostY2 + 1] == ' ' || maze[ghostX2][ghostY2 + 1] == '.' || maze[ghostX2][ghostY2 + 1] == 'P')
    { // for RIGHT movement
        Distance[1] = sqrt(pow((ghostX2 - pacmanX), 2) + pow((ghostY2 + 1 - pacmanY), 2));
    }
    if (maze[ghostX2 - 1][ghostY2] == ' ' || maze[ghostX2 - 1][ghostY2] == '.' || maze[ghostX2 - 1][ghostY2] == 'P')
    { // for upward movement
        Distance[2] = sqrt(pow((ghostX2 - 1 - pacmanX), 2) + pow((ghostY2 - pacmanY), 2));
    }
    if (maze[ghostX2 + 1][ghostY2] == ' ' || maze[ghostX2 + 1][ghostY2] == '.' || maze[ghostX2 + 1][ghostY2] == 'P')
    { // for downward movement
        Distance[3] = sqrt(pow((ghostX2 + 1 - pacmanX), 2) + pow((ghostY2 - pacmanY), 2));
    }
    int smallestidx = Smallestdistance();
    if (smallestidx == 0)
    {
        if (maze[ghostX2][ghostY2 - 1] == ' ' || maze[ghostX2][ghostY2 - 1] == '.' || maze[ghostX2][ghostY2 - 1] == 'P' || maze[ghostX2][ghostY2 - 1] == 'o')
        {
            gotoxy(ghostY2, ghostX2);
            cout << g_item2;
            ghostY2 = ghostY2 - 1;
            g_item2 = maze[ghostX2][ghostY2];
            gotoxy(ghostY2, ghostX2);
            cout << "G";
        }
    }
    else if (smallestidx == 1)
    {
        if (maze[ghostX2][ghostY2 + 1] == ' ' || maze[ghostX2][ghostY2 + 1] == '.' || maze[ghostX2][ghostY2 + 1] == 'P' || maze[ghostX2][ghostY2 + 1] == 'o')
        {
            gotoxy(ghostY2, ghostX2);
            cout << g_item2;
            ghostY2 = ghostY2 + 1;
            g_item2 = maze[ghostX2][ghostY2];
            gotoxy(ghostY2, ghostX2);
            cout << "G";
        }
    }
    else if (smallestidx == 2)
    {
        if (maze[ghostX2 - 1][ghostY2] == ' ' || maze[ghostX2 - 1][ghostY2] == '.' || maze[ghostX2 - 1][ghostY2] == 'P' || maze[ghostX2 - 1][ghostY2] == 'o')
        {
            gotoxy(ghostY2, ghostX2);
            cout << g_item2;
            ghostX2 = ghostX2 - 1;
            g_item2 = maze[ghostX2][ghostY2];
            gotoxy(ghostY2, ghostX2);
            cout << "G";
        }
    }
    else if (smallestidx == 3)
    {
        if (maze[ghostX2 + 1][ghostY2] == ' ' || maze[ghostX2 + 1][ghostY2] == '.' || maze[ghostX2 + 1][ghostY2] == 'P' || maze[ghostX2 + 1][ghostY2] == 'o')
        {
            gotoxy(ghostY2, ghostX2);
            cout << g_item2;
            ghostX2 = ghostX2 + 1;
            g_item2 = maze[ghostX2][ghostY2];
            gotoxy(ghostY2, ghostX2);
            cout << "G";
        }
    }
    if (pacmanX == ghostX2 && pacmanY == ghostY2 && GotEnergizer)
    {
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        ghostX2 = 19;
        ghostY2 = 25;
        gotoxy(ghostY2, ghostX2);
        cout << "G";
        return 1;
    }
    if (ghostX2 == pacmanX && ghostY2 == pacmanY)
    {
        return 0;
    }

    return 1;
}

void total_lives()
{
    gotoxy(75, 0);
    cout << "Total lives: " << lives;
}
void timer()
{
    gotoxy(75, 2);
    cout << "Energizer timer: " << energizerCount;
}