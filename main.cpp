#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h> // To make spawn value more random


using namespace std;


bool gameOver;

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100];

int nTail;

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};

eDirecton dir;

// Initialize the game.
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    // clear the screen.
    system("cls"); //system("clear");

    cout << endl;

    // create the map.

    cout << " ";
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << " #";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    cout << " ";

    for (int i = 0; i < width+2; i++)
        cout << "#";

    cout << endl;

    // show score count on Screen
    cout << " Score:" << score << endl;
}
void Input()
{
    // check for keyboard key hit
    if (_kbhit())
    {
        // update the snake's direction by specific keyboard (WASD)
        switch (_getch())
        {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            default:
                break;
        }
    }
}
void Logic()
{
    // initialize the tails.
    int prevX = tailX[0];

    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;

    tailY[0] = y;

    // keep track of the each moving tail.
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    // check for current moving direction of the snake.
    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    // check if the player collided with the bound of map.
    if (x > width || x < 0 || y > height || y < 0)
      gameOver = true;

    // check if the player collided to one of it's tails.
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        srand(time(0)); // Random seed value for rand based on time

        score += 10; // add to score.

        // draw the next fruit position.
        fruitX = rand() % width;
        fruitY = rand() % height;

        // increase the tail length by one unit of character.
        nTail++;
    }
}

// Programs Entry point.
int main()
{
    //Will make character output much faster. it's a basic form of an character output operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Fix the resolution width & height
    system("MODE con cols=24 lines=25");

    // Initialize the game.
    Setup();

    // the Game Loop
    while (!gameOver)
    {
        // Draw the games graphics.
        Draw();

        // Check for Inputs
        Input();

        // Update the World according to the input.
        Logic();

        // Control the games speed.
        Sleep(150); //sleep(10);
    }

    return 0;
}
