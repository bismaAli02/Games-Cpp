#include <iostream>
#include <fstream>
#include <conio.h>
#include <cmath>
#include <iomanip>
using namespace std;

const int SIZE = 3;
string arr[SIZE][SIZE] = {{"A1", "A2", "A3"}, {"B1", "B2", "B3"}, {"C1", "C2", "C3"}};

int User = 1;
int score = 0;
int score1 = 0;
void header()
{

    cout << "\t\t////////////////////////////////////////////////////////////" << endl;
    cout << "\t\t--                    TIC TAC TOE GAME                     --" << endl;
    cout << "\t\t////////////////////////////////////////////////////////////" << endl;
    cout << " " << endl;
    cout << "  Player 1 symbole (X) " << endl;
    cout << "  Player 2 symbole (O) " << endl;
}
void board()
{
    header();
    cout << "\n\n";
    cout << "\t\t********************************************************" << endl;
    cout << "\t\t*                  |                 |                 *" << endl;
    cout << "\t\t*\t " << arr[0][0] << "\t   | "
         << "\t   " << arr[0][1] << "\t     |\t    " << arr[0][2] << "\t       *" << endl;
    cout << "\t\t*                  |                 |                 *" << endl;
    cout << "\t\t********************************************************" << endl;
    cout << "\t\t*                  |                 |                 *" << endl;
    cout << "\t\t*\t " << arr[1][0] << "\t   | "
         << "\t   " << arr[1][1] << "\t     |\t    " << arr[1][2] << "\t       *" << endl;
    cout << "\t\t*                  |                 |                 *" << endl;
    cout << "\t\t********************************************************" << endl;
    cout << "\t\t*                  |                 |                 *" << endl;
    cout << "\t\t*\t " << arr[2][0] << "\t   | "
         << "\t   " << arr[2][1] << "\t     |\t    " << arr[2][2] << "\t       *" << endl;
    cout << "\t\t*                  |                 |                 *" << endl;
    cout << "\t\t********************************************************" << endl;
}

string User_Input()
{

    string Input;
    cout << "Player " << User << " its Your Turn : ";
    if (User == 1)
    {
        cin >> Input;
    }
    else
    {
        cin >> Input;
    }
    return Input;
}

bool checkRows(string symbol)
{

    int count = 0;
    for (int r = 0; r < SIZE; r++)
    {
        count = 0;
        for (int c = 0; c < SIZE; c++)
        {
            if (arr[r][c] == symbol)
            {
                count++;
            }
        }
        if (count == SIZE)
        {
            return 1;
        }
    }
    return 0;
}

bool checkColoms(string symbol)
{
    int count = 0;
    for (int c = 0; c < SIZE; c++)
    {
        count = 0;
        for (int r = 0; r < SIZE; r++)
        {
            if (arr[r][c] == symbol)
            {
                count++;
            }
        }
        if (count == SIZE)
        {
            return 1;
        }
    }
    return 0;
}

bool checkDiagnols(string symbol)
{
    int count = 0;
    for (int idx = 0; idx < SIZE; idx++)
    {
        if (arr[idx][idx] == symbol)
        {
            count++;
        }
    }
    if (count == SIZE)
    {
        return 1;
    }
    count = 0;
    for (int r = 0, c = 2; r < SIZE; r++, c--)
    {
        if (arr[r][c] == symbol)
        {
            count++;
        }
    }
    if (count == SIZE)
    {
        return 1;
    }
    return 0;
}

bool isWinner(string symbol)
{
    if (checkRows(symbol) || checkColoms(symbol) || checkDiagnols(symbol))
    {
        return 1;
    }
    return 0;
}

main()
{
    string input;
    board();
    for (int i = 0; i < 9; i++)
    {
        
        input = User_Input();
        if (input == "A1")
        {
            if (User == 1)
            {
                if (!(arr[0][0] == "O" || arr[0][0] == "X"))
                arr[0][0] = "X";
            }
            else
            {
                if (!(arr[0][0] == "X" || arr[0][0] == "O"))
                arr[0][0] = "O";
            }
        }

        if (input == "A2")
        {
            if (User == 1)
            {
                if (!(arr[0][1] == "O" || arr[0][1] == "X"))
                arr[0][1] = "X";
            }
            else
             {
                if (!(arr[0][1] == "O" || arr[0][1] == "X"))
                arr[0][1] = "O";
             }
        }

        if (input == "A3")
        {
            if (User == 1)
              {
               if (!(arr[0][2] == "O" || arr[0][2] == "X"))
                arr[0][2] = "X";
              }
            else
               {
                if (!(arr[0][2] == "O" || arr[0][2] == "X"))
                arr[0][2] = "O";
               }
        }

        if (input == "B1")
        {
            if (User == 1)
               {
                if (!(arr[1][0] == "O" || arr[1][0] == "X"))
                arr[1][0] = "X";
               }
            else
                {
                if (!(arr[1][0] == "O" || arr[1][0] == "X"))
                arr[1][0] = "O";
                }
        }

        if (input == "B2")
        {
            if (User == 1)
               { 
                if (!(arr[1][1] == "O" || arr[1][1] == "X"))
                arr[1][1] = "X";
               }
            else
               { 
                if (!(arr[1][1] == "O" || arr[1][1] == "X"))
                arr[1][1] = "O";
               }
        }

        if (input == "B3")
        {
            if (User == 1)
               { 
                if (!(arr[1][2] == "O" || arr[1][2] == "X"))
                arr[1][2] = "X";
               }
             else
               { 
                if (!(arr[1][2] == "O" || arr[1][2] == "X"))
                arr[1][2] = "O";
               }
        }

        if (input == "C1")
        {
            if (User == 1)
            {
                if (!(arr[2][0] == "O" || arr[2][0] == "X"))
                arr[2][0] = "X";
            }
            else
            {
              if (!(arr[2][0] == "O" || arr[2][0] == "X"))
                arr[2][0] = "O";
            }       
        }

        if (input == "C2")
        {
            if (User == 1)
             {
              if (!(arr[2][1] == "O" || arr[2][1] == "X"))
                arr[2][1] = "X";
             }
            else
              {
                  if (!(arr[2][1] == "O" || arr[2][1] == "X"))
                arr[2][1] = "O";
              }
        }

        if (input == "C3")
        {
            if (User == 1)
               {
                if (!(arr[2][2] == "O" || arr[2][2] == "X"))
                arr[2][2] = "X";
               }
            else
                {
                if (!(arr[2][2] == "O" || arr[2][2] == "X"))
                arr[2][2] = "O";
                }
        }
        if (User == 1)
        {
            User = 2;
        }
        else
        {
            User = 1;
        }
       system("CLS");
        board();
      if (isWinner("X"))
    {
        cout<<"Player 1 has won!!!!!!!!!"<<endl;
        score=score+1;
        break;
    }
    else if(isWinner("O"))
    {
        cout<<"Player 2 has won!!!!!!!!!!!!"<<endl;
        score1 = score1 + 1;
        break;
    }
    }
    
     if(score == 0 && score1 == 0)
       cout<<"Draw match!!!!!"<<endl;
     cout<<"SCORE OF PLAYER 1 = "<< score<<endl;
     cout<<"SCORE OF PLAYER 2 = "<< score1<<endl;
}