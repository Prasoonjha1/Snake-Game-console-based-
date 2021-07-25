#include <fstream>
#include<iostream>
#include <conio.h>
#include <windows.h>
#include<string>
#include<limits>
#include<string>
#include<iomanip>
using namespace std;
enum type {easy,tough};
type T=tough;
class game
{
private:
    string name;
    enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
    eDirecton dir;
    int x, y, fruitX, fruitY,score;
    int nTail;
    int tailX[100], tailY[100];
public:
    void Inp();
    bool gameOver;
    void Setup();
    void Draw();
    void Input();
    void Logic();
};
const int width = 15;
const int height =15;
void game::Inp()
{
    ofstream file;
    file.open("Output.txt",ios::app);
    string s=to_string(score);
    cout<<"Enter your name:";
    cin>>name;
    file<<name<<"\n"<<s<<"\n";
    file.close();
}
void game::Setup()
{
    cout<<"---------------------------------\n";
    cout<<"         SNAKE GAME\n";
    cout<<"---------------------------------\n";
    nTail=0;
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score=0;
}
void game::Draw()
{
    system("cls");
    cout<<"---------------------------------\n";
    cout<<"         SNAKE GAME";
    cout<<"\n---------------------------------\n";
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
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

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout<<"\n---------------------------------\n";
    cout << "Score:" << score << endl;
}
void game::Input()
{
    if (_kbhit())
    {
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
        }
    }
}
void game::Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
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
    if(T==tough)
    {
        if (x > width || x < 0 || y > height || y < 0)
            gameOver = true;
    }
    else if(T==easy)
    {
        if (x >= width) x = 0; else if (x < 0) x = width - 1;
        if (y >= height) y = 0; else if (y < 0) y = height - 1;
    }

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
void play()
{
    system("cls");
    game player;
    player.Setup();
    while (!player.gameOver)
    {
        player.Draw();
        player.Input();
        player.Logic();
        if(T==tough)
        {
            Sleep(100);
        }
        else
        {
            Sleep(125);
        }
    }
    player.Inp();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Press enter to continue__";
    fgetc(stdin);
}
void rules()
{
    system("cls");
    cout<<"----------------------\n";
    cout<<"     SNAKE GAME\nRules\n";
    cout<<"1. The snake starts at the center of the board.\n";
    cout<<"2. The snake moves at a constant speed.\n";
    cout<<"3. The snake moves only north, south, east, or west (ignore the versions of the game where the snake can move in curves).\n";
    cout<<"4. The snake moves by adding a square to its head and simultaneously deleting a square from the tip of its tail.\n";
    cout<<"5. Fruits appear at random locations.\n";
    cout<<"6. There is always exactly one apple visible at any given time.\n";
    cout<<"7. When the snake eats (runs into) a fruit, it gets longer.\n";
    cout<<"8. The game continues until the snake dies.\n";
    cout<<"9. A snake dies by either (1) running into the edge of the board, or (2) by running into its own tail.\n";
    cout<<"The final score is based on the number of apples eaten by the snake.\n";
    cout<<"Controls:-\n'a' for west\n'd' for east\n'w' for north\n's' for south\n";
    cout<<"Press enter to continue__";
    fgetc(stdin);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void setting()
{
    above:;
    system("cls");
    cout<<"---------------------------------|\n";
    cout<<"         SNAKE GAME              |\n";
    cout<<"---------------------------------|\n";
    cout<<"Settings                         |\n";
    cout<<"1. Tough (default)               |\n";
    cout<<"2. Easy                          |\n";
    cout<<"3. Go back                       |\n";
    cout<<"---------------------------------|\n\n";
    cout<<"Select one of the options given above___";
    int n;
    cin>>n;
    switch(n)
    {
        case 1:T=tough;break;
        case 2:T=easy;break;
        case 3:break;
        default:cout<<"Wrong no. typed!!Type the wright one__";goto above;
    }
}
void hs()
{
    system("cls");
    ifstream file;
    file.open("Output.txt",ios::in);
    string str;
    cout<<"---------------------------------|\n";
    cout<<"         SNAKE GAME              |\n";
    cout<<"---------------------------------|\n";
    cout<<"Player"<<setw(17)<<"Score"<<setw(12)<<"|\n";
    cout<<"---------------------------------|\n";
    while(!file.eof()&&file.is_open())
    {
        getline(file,str);
        cout<<str<<setw(20-str.size());
        getline(file,str);
        cout<<str<<setw(15)<<"|\n";
    }
    cout<<"---------------------------------|\n";
    cout<<"Press enter to continue";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    fgetc(stdin);
}
int main()
{
    start:;
    system("cls");
    //system("color a");
    cout<<"---------------------------------|\n";
    cout<<"         SNAKE GAME              |\n";
    cout<<"---------------------------------|\n";
    cout<<"1. Play Game                     |\n";
    cout<<"2. Settings                      |\n";
    cout<<"3. Rules/How to play             |\n";
    cout<<"4. High Scores                   |\n";
    cout<<"5. Exit                          |\n";
    cout<<"---------------------------------|\n\n";
    cout<<"Choose one of the options________";
    int n;
    cin>>n;
    try{
    switch(n)
    {
        case 1:play();goto start;break;
        case 2:setting();goto start;break;
        case 3:rules();goto start;break;
        case 4:hs();goto start;break;
        case 5:return 0;
        default:if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout<<"You have entered the wrong input:\nPress enter to continue!!";
                    fgetc(stdin);
                    goto start;
                }
                else throw(n);
    }
    }catch(int n)
    {
        cout<<"\nInteger error:\n";
        cout<<"Press enter to go back!!";
        fgetc(stdin);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto start;
    }
    catch(...)
    {
        cout<<"Default Error:\nPress enter to continue!!";
        fgetc(stdin);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto start;
    }
    return 0;
}
