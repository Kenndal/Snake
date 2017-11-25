#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

struct body  // must be global ?
{
    int x,y;
};
int main()
{
    int vertical, horizontal;
    vertical=8;
    horizontal=20;
    int mapa[vertical][horizontal];

    // vector snake
    vector<body> snake;
    // starting position
    snake.push_back(body());
    snake[0].x = vertical/2;
    snake[0].y = horizontal/2;

    // creating map
    // 1 -> game place
    // 2 -> end of map
    for(int j=0; j<horizontal; j++)
    {
        mapa[0][j]=2;
    }
    for (int i=1; i<vertical-1; i++)
    {
        mapa[i][0]=2;
        for(int j=1; j<horizontal-1; j++)
        {
            mapa[i][j]=1;
        }
        mapa[i][horizontal-1]=2;
    }
    for (int j=0; j<horizontal; j++)
    {
        mapa[vertical-1][j]=2;
    }




    // Game
    char direction, earlier_direction=0;
    //0 -> snake
    mapa[snake[0].x][snake[0].y] = 0;
    int x_position_of_apple=0;
    int y_position_of_apple=0;
    bool true_apple;
    srand(time(NULL));
    mapa[rand()%(vertical-2)+1][rand()%(horizontal-2)+1] = 3; // generate first apple, 3 -> apple
    //starting display
    for (int i=0; i<vertical; i++)
    {
        for(int j=0; j<horizontal; j++)
        {
            if(mapa[i][j]==0)
                cout << "O";
            if(mapa[i][j]==1)
                cout << " ";
            if(mapa[i][j]==2)
                cout << "*";
            if(mapa[i][j]==3)
                cout << "a";
        }
        cout << endl;
    }
    direction = getch();
    system("cls"); // fix double map bug

    while(direction !=27)
    {
        if (kbhit()) // change direction
        {
            direction = getch();
        }
        if((direction ==97  && earlier_direction!=100) || (direction ==100 && earlier_direction!=97) || (direction==115 && earlier_direction!=119) || (direction==119 && earlier_direction!=115)) // display bug fixing
        {
            if(direction==97 && earlier_direction!=100) // left direction
            {
                mapa[snake.back().x][snake.back().y]=1 ; // O -> "
                for(int i=snake.size()-1; i>0; i--)
                {
                    snake[i].x = snake[i-1].x;
                    snake[i].y = snake[i-1].y;
                }
                snake[0].y = snake[0].y-1;
                if(mapa[snake[0].x][snake[0].y]!=0)
                {
                    if(mapa[snake[0].x][snake[0].y]!=2)
                    {
                        if(mapa[snake[0].x][snake[0].y]==3)
                        {
                            mapa[snake[0].x][snake[0].y]=0; // a -> O
                            snake.push_back(body());
                            true_apple = true;
                            while(true_apple)
                            {
                                x_position_of_apple = rand()%(vertical-2)+1;
                                y_position_of_apple = rand()%(horizontal-2)+1;
                                for (int i=0; i<snake.size(); i++)
                                {
                                    if (snake[i].x!=x_position_of_apple || snake[i].y!=y_position_of_apple)
                                    {
                                        true_apple = false;
                                    }
                                    else
                                    {
                                        true_apple = true;
                                        break;
                                    }
                                }
                            }
                            mapa[x_position_of_apple][y_position_of_apple] = 3; // generate next apple
                        }
                        else
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                    }
                    else
                    {
                        if(mapa[(snake[0].x)][horizontal-2]!=3)
                        {
                            snake[0].y = horizontal-2;
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                            mapa[snake[0].x][0] = 2;
                            mapa[snake[0].x][horizontal-1]=2;
                        }
                        else
                        {
                            mapa[snake[0].x][snake[0].y]=0; // a -> O
                            true_apple = true;
                            snake.push_back(body());
                            while(true_apple)
                            {
                                x_position_of_apple = rand()%(vertical-2)+1;
                                y_position_of_apple = rand()%(horizontal-2)+1;
                                for (int i=0; i<snake.size(); i++)
                                {
                                    if (snake[i].x!=x_position_of_apple || snake[i].y!=y_position_of_apple)
                                    {
                                        true_apple = false;
                                    }
                                    else
                                    {
                                        true_apple = true;
                                        break;
                                    }
                                }
                            }
                            snake[0].y = horizontal-2;
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                            mapa[snake[0].x][0] = 2;
                            mapa[snake[0].x][horizontal-1]=2;
                            mapa[x_position_of_apple][y_position_of_apple] = 3; // generate next apple
                        }
                    }
                }
                else break;

                mapa[0][0]=2; // fix " " bug

                for (int i=0; i<vertical; i++)
                {
                    for(int j=0; j<horizontal; j++)
                    {
                        if(mapa[i][j]==0)
                            cout << "O";
                        if(mapa[i][j]==1)
                            cout << " ";
                        if(mapa[i][j]==2)
                            cout << "*";
                        if(mapa[i][j]==3)
                            cout << "a";
                    }
                    cout << endl;
                }
            }

            if(direction==119 && earlier_direction!=115) // up direction
            {
                mapa[snake.back().x][snake.back().y]=1 ; // O -> " "
                for(int i=snake.size()-1; i>0; i--)
                {
                    snake[i].x = snake[i-1].x;
                    snake[i].y = snake[i-1].y;
                }
                snake[0].x = snake[0].x-1;
                if(mapa[snake[0].x][snake[0].y]!=0)
                {
                    if(mapa[snake[0].x][snake[0].y]!=2)
                    {
                        if(mapa[snake[0].x][snake[0].y]==3)
                        {
                            mapa[snake[0].x][snake[0].y]=0; // a -> O
                            true_apple = true;
                            snake.push_back(body());
                            while(true_apple)
                            {
                                x_position_of_apple = rand()%(vertical-2)+1;
                                y_position_of_apple = rand()%(horizontal-2)+1;
                                for (int i=0; i<snake.size(); i++)
                                {
                                    if (snake[i].x!=x_position_of_apple || snake[i].y!=y_position_of_apple)
                                        true_apple = false;
                                    else
                                    {
                                        true_apple = true;
                                        break;
                                    }
                                }
                            }
                            mapa[x_position_of_apple][y_position_of_apple] = 3; // generate next apple
                        }
                        else
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                    }
                    else
                    {
                        if(mapa[(vertical-2)][snake[0].y]!=3)
                        {
                            mapa[snake[0].x][snake[0].y] = mapa[vertical-1][snake[0].y];
                            snake[0].x = vertical-2;
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                            mapa[0][snake[0].y] = 2;
                            mapa[vertical-1][snake[0].y]=2;
                        }
                        else
                        {
                            mapa[snake[0].x][snake[0].y]=0; // a -> O
                            true_apple = true;
                            snake.push_back(body());
                            while(true_apple)
                            {
                                cout << "g";
                                x_position_of_apple = rand()%(vertical-2)+1;
                                y_position_of_apple = rand()%(horizontal-2)+1;
                                for (int i=0; i<snake.size(); i++)
                                {
                                    if (snake[i].x!=x_position_of_apple || snake[i].y!=y_position_of_apple)
                                    {
                                        true_apple = false;
                                    }
                                    else
                                    {
                                        true_apple = true;
                                        break;
                                    }
                                }
                            }
                            snake[0].x = vertical-2;
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                            mapa[0][snake[0].y] = 2;
                            mapa[vertical-1][snake[0].y]=2;
                            mapa[x_position_of_apple][y_position_of_apple] = 3; // generate next apple

                        }
                    }
                }
                else break;

                mapa[0][0]=2; // fix " " bug

                for (int i=0; i<vertical; i++)
                {
                    for(int j=0; j<horizontal; j++)
                    {
                        if(mapa[i][j]==0)
                            cout << "O";
                        if(mapa[i][j]==1)
                            cout << " ";
                        if(mapa[i][j]==2)
                            cout << "*";
                        if(mapa[i][j]==3)
                            cout << "a";
                    }
                    cout << endl;
                }
            }

            if(direction==115 && earlier_direction!=119) // down direction
            {
                mapa[snake.back().x][snake.back().y]=1 ; // O -> " "
                for(int i=snake.size()-1; i>0; i--)
                {
                    snake[i].x = snake[i-1].x;
                    snake[i].y = snake[i-1].y;
                }
                snake[0].x = snake[0].x+1;
                if(mapa[snake[0].x][snake[0].y]!=0)
                {
                    if(mapa[snake[0].x][snake[0].y]!=2)
                    {
                        if(mapa[snake[0].x][snake[0].y]==3)
                        {
                            mapa[snake[0].x][snake[0].y]=0; // a -> O
                            true_apple = true;
                            snake.push_back(body());
                            while(true_apple)
                            {
                                x_position_of_apple = rand()%(vertical-2)+1;
                                y_position_of_apple = rand()%(horizontal-2)+1;
                                for (int i=0; i<snake.size(); i++)
                                {
                                    if (snake[i].x!=x_position_of_apple || snake[i].y!=y_position_of_apple)
                                        true_apple = false;
                                    else
                                    {
                                        true_apple = true;
                                        break;
                                    }
                                }
                            }
                            mapa[x_position_of_apple][y_position_of_apple] = 3; // generate next apple
                        }
                        else
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                    }
                    else
                    {
                        if(mapa[1][snake[0].y]!=3)
                        {
                            mapa[snake[0].x][snake[0].y] = mapa[1][snake[0].y];
                            snake[0].x = 1;
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                            mapa[0][snake[0].y] = 2;
                            mapa[vertical-1][snake[0].y]=2;
                        }
                        else
                        {
                            mapa[snake[0].x][snake[0].y]=0; // a -> O
                            true_apple = true;
                            snake.push_back(body());
                            while(true_apple)
                            {
                                cout << "g";
                                x_position_of_apple = rand()%(vertical-2)+1;
                                y_position_of_apple = rand()%(horizontal-2)+1;
                                for (int i=0; i<snake.size(); i++)
                                {
                                    if (snake[i].x!=x_position_of_apple || snake[i].y!=y_position_of_apple)
                                    {
                                        cout <<  "h";
                                        true_apple = false;
                                    }
                                    else
                                    {
                                        true_apple = true;
                                        break;
                                    }
                                }
                            }
                            snake[0].x = 1;
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                            mapa[0][snake[0].y] = 2;
                            mapa[vertical-1][snake[0].y]=2;
                            mapa[x_position_of_apple][y_position_of_apple] = 3; // generate next apple

                        }
                    }
                }
                else break;

                mapa[0][0]=2; // fix " " bug

                for (int i=0; i<vertical; i++)
                {
                    for(int j=0; j<horizontal; j++)
                    {
                        if(mapa[i][j]==0)
                            cout << "O";
                        if(mapa[i][j]==1)
                            cout << " ";
                        if(mapa[i][j]==2)
                            cout << "*";
                        if(mapa[i][j]==3)
                            cout << "a";
                    }
                    cout << endl;
                }
            }

            if(direction==100 && earlier_direction!=97) // right direction
            {
                mapa[snake.back().x][snake.back().y]=1 ; // O -> " "
                for(int i=snake.size()-1; i>0; i--)
                {
                    snake[i].x = snake[i-1].x;
                    snake[i].y = snake[i-1].y;
                }
                snake[0].y = snake[0].y+1;
                if(mapa[snake[0].x][snake[0].y]!=0)
                {
                    if(mapa[snake[0].x][snake[0].y]!=2)
                    {
                        if(mapa[snake[0].x][snake[0].y]==3)
                        {
                            mapa[snake[0].x][snake[0].y]=0; // a -> O
                            true_apple = true;
                            snake.push_back(body());
                            while(true_apple)
                            {
                                x_position_of_apple = rand()%(vertical-2)+1;
                                y_position_of_apple = rand()%(horizontal-2)+1;
                                for (int i=0; i<snake.size(); i++)
                                {
                                    if (snake[i].x!=x_position_of_apple || snake[i].y!=y_position_of_apple)
                                        true_apple = false;
                                    else
                                    {
                                        true_apple = true;
                                        break;
                                    }
                                }
                            }
                            mapa[x_position_of_apple][y_position_of_apple] = 3; // generate next apple
                        }
                        else
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                    }
                    else
                    {
                        if(mapa[(snake[0].x)][1]!=3)
                        {
                            mapa[snake[0].x][snake[0].y] = mapa[(snake[0].x)][1];
                            snake[0].y = 1;
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                            mapa[snake[0].x][horizontal-1] = 2;
                            mapa[snake[0].x][0]=2;
                        }
                        else
                        {
                            mapa[snake[0].x][snake[0].y]=0; // a -> O
                            true_apple = true;
                            snake.push_back(body());
                            while(true_apple)
                            {
                                x_position_of_apple = rand()%(vertical-2)+1;
                                y_position_of_apple = rand()%(horizontal-2)+1;
                                for (int i=0; i<snake.size(); i++)
                                {
                                    if (snake[i].x!=x_position_of_apple || snake[i].y!=y_position_of_apple)
                                    {
                                        true_apple = false;
                                    }
                                    else
                                    {
                                        true_apple = true;
                                        break;
                                    }
                                }
                            }
                            snake[0].y = 1;
                            mapa[snake[0].x][snake[0].y]=0; // " " -> O
                            mapa[snake[0].x][horizontal-1] = 2;
                            mapa[snake[0].x][0]=2;
                            mapa[vertical-1][snake[0].y]=2;
                            mapa[x_position_of_apple][y_position_of_apple] = 3; // generate next apple
                        }
                    }
                }
                else break;

                mapa[0][0]=2; // fix " " bug

                for (int i=0; i<vertical; i++)
                {
                    for(int j=0; j<horizontal; j++)
                    {
                        if(mapa[i][j]==0)
                            cout << "O";
                        if(mapa[i][j]==1)
                            cout << " ";
                        if(mapa[i][j]==2)
                            cout << "*";
                        if(mapa[i][j]==3)
                            cout << "a";
                    }
                    cout << endl;
                }
            }

            if(direction==97 || direction==100 || direction==115 || direction==119) // direction must have those value
                earlier_direction = direction;

            _sleep(200);
            system("cls");
        }
        else
        {
            if((earlier_direction==97 && earlier_direction!=100) || (earlier_direction==100 && earlier_direction!=97) || (earlier_direction==115 && earlier_direction!=119) || (earlier_direction==119 &&  earlier_direction!=115)) // earlier_direction must have those value
                direction = earlier_direction; // still going on good direction

            if (kbhit())
            {
                direction = getch();
                earlier_direction = direction;
            }
        }
    }

    cout << "GAME OVER";

    return 0;
}

