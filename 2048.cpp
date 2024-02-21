#include <iostream>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <iomanip>
#include <fstream>
#include <ncurses.h>
using namespace std;
struct Player
{
    string Name;
    int BestScore;
};
char MyGetch()
{
    char ch;
    struct termios oldt, newt;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Set the terminal to non-canonical mode and turn off echo
    newt.c_lflag &= ~(ICANON | ECHO);

    // Apply the new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read a single character
    ch = getchar();

    // Restore the original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
int RandomNum()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomNum = rand() % 4;
    if (randomNum == 0 || randomNum == 1 || randomNum == 2)
    {
        return 2;
    }
    else
    {
        return 4;
    }
}
void Start(int **&board)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = 0;
        }
    }
    board[rand() % 4][rand() % 4] = RandomNum();
    board[(rand() % 4 + 1) % 4][(rand() % 4 + 3) % 4] = RandomNum();
}
void WMove(int **&board)
{
    for (int j = 0; j < 4; j++)
    {
        for (int k = 1; k <= 3; k++)
        {
            for (int i = 1; i < 4; i++)
            {
                if (board[i - 1][j] == 0)
                {
                    board[i - 1][j] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
    }
}
void WSum(int **&board, int &score)
{
    WMove(board);
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][j] == board[i + 1][j])
            {
                board[i][j] = board[i][j] + board[i + 1][j];
                score = score + board[i][j];
                board[i + 1][j] = 0;
            }
        }
    }
    WMove(board);
}
void DMove(int **&board)
{
    for (int i = 0; i < 4; i++)
    {
        for (int k = 1; k <= 3; k++)
        {
            for (int j = 2; j >= 0; j--)
            {
                if (board[i][j + 1] == 0)
                {
                    board[i][j + 1] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
    }
}
void DSum(int **&board, int &score)
{
    DMove(board);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j > 0; j--)
        {
            if (board[i][j] == board[i][j - 1])
            {
                board[i][j] = board[i][j] + board[i][j - 1];
                score = score + board[i][j];
                board[i][j - 1] = 0;
            }
        }
    }
    DMove(board);
}
void AMove(int **&board)
{
    for (int i = 0; i < 4; i++)
    {
        for (int k = 1; k <= 3; k++)
        {
            for (int j = 1; j < 4; j++)
            {
                if (board[i][j - 1] == 0)
                {
                    board[i][j - 1] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
    }
}
void ASum(int **&board, int &score)
{
    AMove(board);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == board[i][j + 1])
            {
                board[i][j] = board[i][j] + board[i][j + 1];
                score = score + board[i][j];
                board[i][j + 1] = 0;
            }
        }
    }
    AMove(board);
}
void SMove(int **&board)
{
    for (int j = 0; j < 4; j++)
    {
        for (int k = 1; k <= 3; k++)
        {
            for (int i = 2; i >= 0; i--)
            {
                if (board[i + 1][j] == 0)
                {
                    board[i + 1][j] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
    }
}
void SSum(int **&board, int &score)
{
    SMove(board);
    for (int j = 0; j < 4; j++)
    {
        for (int i = 3; i > 0; i--)
        {
            if (board[i][j] == board[i - 1][j])
            {
                board[i][j] = board[i][j] + board[i - 1][j];
                score = score + board[i][j];
                board[i - 1][j] = 0;
            }
        }
    }
    SMove(board);
}
int ZeroCount(int **&board)
{
    int zerocount = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
                zerocount++;
        }
    }
    return zerocount;
}
void RandomFill(int **&board)
{
    int i, j;
    if (ZeroCount(board) != 0)
    {
        do
        {
            i = rand() % 4;
            j = rand() % 4;

        } while (board[i][j] != 0);
        board[i][j] = RandomNum();
    }
}
void PrintBoard(int **&board, int &score)
{
    system("clear");
    cout << "Press \"M\" to Exit " << endl
         << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << "\u256D\u2500\u2500\u2500\u2500\u2500\u256E  \u256D\u2500\u2500\u2500\u2500\u2500\u256E  \u256D\u2500\u2500\u2500\u2500\u2500\u256E  \u256D\u2500\u2500\u2500\u2500\u2500\u256E" << endl;
        for (int j = 0; j < 4; j++)
        {
            cout << "\u2502";
            switch (board[i][j])
            {
            case 0:
                cout << "     ";
                break;
            case 2:
                cout << "\x1b[41m  " + to_string(board[i][j]) + "  \x1b[0m";
                break;
            case 4:
                cout << "\x1b[42m  " + to_string(board[i][j]) + "  \x1b[0m";
                break;
            case 8:
                cout << "\x1b[43m  " + to_string(board[i][j]) + "  \x1b[0m";
                break;
            case 16:
                cout << "\x1b[44m " + to_string(board[i][j]) + "  \x1b[0m";
                break;
            case 32:
                cout << "\x1b[45m " + to_string(board[i][j]) + "  \x1b[0m";
                break;
            case 64:
                cout << "\x1b[46m " + to_string(board[i][j]) + "  \x1b[0m";
                break;
            case 128:
                cout << "\x1b[47m " + to_string(board[i][j]) + " \x1b[0m";
                break;
            case 256:
                cout << "\x1b[48;5;200m " + to_string(board[i][j]) + " \x1b[0m";
                break;
            case 512:
                cout << "\x1b[48;5;88m " + to_string(board[i][j]) + " \x1b[0m";
                break;
            case 1024:
                cout << "\x1b[48;5;20m" + to_string(board[i][j]) + " \x1b[0m";
                break;
            case 2048:
                cout << "\x1b[48;5;255m" + to_string(board[i][j]) + " \x1b[0m";
                break;
            }

            cout << "\u2502  ";
        }
        cout << endl;
        cout << "\u2570\u2500\u2500\u2500\u2500\u2500\u256F  \u2570\u2500\u2500\u2500\u2500\u2500\u256F  \u2570\u2500\u2500\u2500\u2500\u2500\u256F  \u2570\u2500\u2500\u2500\u2500\u2500\u256F  " << endl;
    }
    cout << endl;
    cout << "Score= " << score << endl;
}
bool EndGame(int **&board)
{
    int barabar = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == board[i][j + 1])
            {
                barabar++;
            }
        }
    }
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][j] == board[i + 1][j])
            {
                barabar++;
            }
        }
    }
    if ((ZeroCount(board) == 0) && barabar == 0)
        return false;
    else
        return true;
}
bool Winngame(int **&board)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 2048)
                return true;
        }
    }
    return false;
}
void SorceLeaderBoard(Player *players, int size)
{
    Player players1[size];
    for (int j = 0; j < size; j++)
    {
        int mostscore = 0;
        for (int i = 0; i < size; i++)
        {
            if (j > 0)
            {
                if (players[i].BestScore >= mostscore && players[i].BestScore < players1[j - 1].BestScore)
                {
                    mostscore = players[i].BestScore;
                    players1[j].BestScore = players[i].BestScore;
                    players1[j].Name = players[i].Name;
                }
            }
            else
            {
                if (players[i].BestScore >= mostscore)
                {
                    mostscore = players[i].BestScore;
                    players1[j].BestScore = players[i].BestScore;
                    players1[j].Name = players[i].Name;
                }
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        players[i].BestScore = players1[i].BestScore;
        players[i].Name = players1[i].Name;
    }
}
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

int main()
{
    string name;
    int score;
    int userInput;
    do
    {
        cout << "1- New Game" << endl
             << "2- Leaderboard" << endl
             << "3- Exit" << endl;
        cin >> userInput;
        if (userInput == 1)
        {
            int **board = new int *[4];
            for (int i = 0; i < 4; i++)
            {
                board[i] = new int[4];
            }
            cout << "Enter your name:" << endl;
            cin >> name;
            score = 0;
            Start(board);
            PrintBoard(board, score);
            char value = 'x';
            while (EndGame(board) == true && Winngame(board) == false && value != 'm')
            {

                value = MyGetch();
                if (value == 'w')
                {
                    int test1[4][4];
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            test1[i][j] = board[i][j];
                        }
                    }
                    WSum(board, score);
                    int test2[4][4];
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            test2[i][j] = board[i][j];
                        }
                    }
                    int h = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (test1[i][j] == test2[i][j])
                            {
                                h++;
                            }
                        }
                    }
                    if (h < 16)
                    {
                        RandomFill(board);
                    }
                    PrintBoard(board, score);
                    if (Winngame(board) == true)
                    {
                        cout << "WINNEER" << endl;
                        ofstream file("leaderboard.txt", ios::app);
                        if (file.is_open())
                        {
                            file << name << " " << score << endl;
                            file.close();
                        }
                    }
                    else if (EndGame(board) == false)
                    {
                        ofstream file("leaderboard.txt", ios::app);
                        if (file.is_open())
                        {
                            file << name << " " << score << endl;
                            file.close();
                        }
                        cout << "END GAME" << endl;
                    }
                }
                else if (value == 'd')
                {
                    int test1[4][4];
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            test1[i][j] = board[i][j];
                        }
                    }
                    DSum(board, score);
                    int test2[4][4];
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            test2[i][j] = board[i][j];
                        }
                    }
                    int h = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (test1[i][j] == test2[i][j])
                            {
                                h++;
                            }
                        }
                    }
                    if (h < 16)
                    {
                        RandomFill(board);
                    }
                    PrintBoard(board, score);
                    if (Winngame(board) == true)
                    {
                        cout << "WINNEER" << endl;
                        ofstream file("leaderboard.txt", ios::app);
                        if (file.is_open())
                        {
                            file << name << " " << score << endl;
                            file.close();
                        }
                    }
                    else if (EndGame(board) == false)
                    {
                        ofstream file("leaderboard.txt", ios::app);
                        if (file.is_open())
                        {
                            file << name << " " << score << endl;
                            file.close();
                        }
                        cout << "END GAME\n";
                    }
                }
                else if (value == 's')
                {
                    int test1[4][4];
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            test1[i][j] = board[i][j];
                        }
                    }
                    SSum(board, score);
                    int test2[4][4];
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            test2[i][j] = board[i][j];
                        }
                    }
                    int h = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (test1[i][j] == test2[i][j])
                            {
                                h++;
                            }
                        }
                    }
                    if (h < 16)
                    {
                        RandomFill(board);
                    }
                    PrintBoard(board, score);
                    if (Winngame(board) == true)
                    {
                        cout << "WINNEER" << endl;
                        ofstream file("leaderboard.txt", ios::app);
                        if (file.is_open())
                        {
                            file << name << " " << score << endl;
                            file.close();
                        }
                    }
                    else if (EndGame(board) == false)
                    {
                        ofstream file("leaderboard.txt", ios::app);
                        if (file.is_open())
                        {
                            file << name << " " << score << endl;
                            file.close();
                        }
                        cout << "END GAME\n";
                    }
                }
                else if (value == 'a')
                {
                    int test1[4][4];
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            test1[i][j] = board[i][j];
                        }
                    }
                    ASum(board, score);
                    int test2[4][4];
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            test2[i][j] = board[i][j];
                        }
                    }
                    int h = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (test1[i][j] == test2[i][j])
                            {
                                h++;
                            }
                        }
                    }
                    if (h < 16)
                    {
                        RandomFill(board);
                    }
                    PrintBoard(board, score);
                    if (Winngame(board) == true)
                    {
                        cout << "WINNEER" << endl;
                        ofstream file("leaderboard.txt", ios::app);
                        if (file.is_open())
                        {
                            file << name << " " << score << endl;
                            file.close();
                        }
                    }
                    else if (EndGame(board) == false)
                    {
                        ofstream file("leaderboard.txt", ios::app);
                        if (file.is_open())
                        {
                            file << name << " " << score << endl;
                            file.close();
                        }
                        cout << "END GAME\n";
                    }
                }
            }
        }
        else if (userInput == 2)
        {
            int size = 0;
            ifstream file1("leaderboard.txt", ios::in);
            if (file1.is_open())
            {
                while (file1 >> name >> score)
                {
                    size++;
                }
                file1.close();
            }

            Player players[size];
            int i = 0;
            ifstream file2("leaderboard.txt", ios::in);
            if (file2.is_open())
            {
                while (file2 >> name >> score)
                {
                    players[i].Name = name;
                    players[i].BestScore = score;
                    i++;
                }
                file2.close();
            }
            SorceLeaderBoard(players, size);
            system("clear");
            for (int i = 0; i < size; i++)
            {
                cout << i + 1 << "- " << players[i].Name << endl;
                cout << "Score= " << players[i].BestScore << endl
                     << endl;
            }
        }
    } while (userInput != 3);

    return 0;
}
