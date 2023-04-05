#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string array[3][3] = {{"-", "-", "-"},
                      {"-", "-", "-"},
                      {"-", "-", "-"}};
void display();
void print_options();
void taking_input(int h);
string parsedata(string a, int f);
void store();
int load();
void input(int g);
bool winner();
int main_menue();
int check_resume();
void start_game();
void header();
char c = ' ';
string a;
int count = 0, i, j;
int count1 = 0  , players = 0;
bool flag = false ;
int h = 0;

main()
{   
    bool check;
    a = load();
    int s = 0;
    for (int i = 0 ; i < 3 ; i++)
    {
       s = main_menue();
        if (s == 1)
        {

            start_game();
            count++;
            taking_input(h);
        }
        
        if (s == 2)
        {
            
            count++;
            h = check_resume();
            taking_input(h);
            // if (check == false)
                // {
                //     cout << "TIE";
                // }
        }
        if (count == 9)
        {
            cout << "GAME OVER" << endl;
            ;
            break;
        }
        if (s == 3)
        {

            store();
            break;
        }
    
    }
}


bool winner()
{   
    bool flag = false;  
    for (int i = 0 ; i < 3 ; i++)
    {
        if (array[0][i] == "X"  && array[1][i] == "X" && array[2][i] == "X")
        {
            cout << "player 1 is winner"<<endl;
            flag = true;
            break;
        }
        if (array[0][i] == "O"  && array[1][i] == "O" && array[2][i] == "O")
        {
            cout << "player 2 is winner"<<endl;
            flag = true;
            break;
        }
    }
    for (int i = 0 ; i < 3 ; i++)
    {
        if (array[i][0] == "X"  && array[i][1] == "X" && array[i][2] == "X")
        {
            cout << "player 1 is winner"<<endl;
            flag = true;
            break;
        }
        if (array[i][0] == "O"  && array[i][1] == "O" && array[i][2] == "O")
        {
            cout << "player 2 is winner"<<endl;
            flag = true;
            break;
        }
    }
    if (array[0][0] == "X"  && array[1][1] == "X" && array[2][2] == "X")
    {
        cout << "player 1 is winner"<<endl;
        flag = true;
    }
    if (array[0][2] == "X"  && array[1][1] == "X"  && array[2][0] == "X")
    {
        cout << "player 1 is winner"<<endl;
        flag = true;
    }
    if (array[0][0] == "O" && array[1][1] == "O" && array[2][2] == "O")
    {
        cout << "player 2 is winner"<<endl;
        flag = true;
    }
    if (array[0][2] == "O" && array[1][1] == "O" && array[2][0] == "O")
    {
        cout << "player 2 is winner"<<endl;
        flag = true;
    }
    return flag;
}

void display()
{   cout << "\n\n\n";
    cout << "\t\t" << "                                 " << endl;
    cout << "\t\t" << "                                 " << endl;
    cout << "\t\t" << "            A       B       C    " << endl;
    cout << "\t\t" << "         _______ _______ _______ " << endl;
    cout << "\t\t" << "        |       |       |       |" << endl;
    cout << "\t\t" << "    1   |    " << array[0][0] << "  |   " << array[0][1] << "   |   " << array[0][2] << "   |" << endl;
    cout << "\t\t" << "        |_______|_______|_______|" << endl;
    cout << "\t\t" << "        |       |       |       |" << endl;
    cout << "\t\t" << "    2   |    " << array[1][0] << "  |   " << array[1][1] << "   |   " << array[1][2] << "   |" << endl;
    cout << "\t\t" << "        |_______|_______|_______|" << endl;
    cout << "\t\t" << "        |       |       |       |" << endl;
    cout << "\t\t" << "    3   |    " << array[2][0] << "  |   " << array[2][1] << "   |   " << array[2][2] << "   |" << endl;
    cout << "\t\t" << "        |_______|_______|_______|" << endl;
    cout << "\n\n\n";
}

void taking_input(int h)
{
    count1 = count1 + 1;
    int op ;
    bool check = false;
    for (int k = h ; k < 9 ; k++)
    {
        if (flag == true)
        {
            i--;
            flag = false;
            continue;
        }
        check = winner();
        if (check == true || c == 'b')
        {
            break;
        }
        header();
        display();
        print_options();
        if ( k % 2 == 0)
        {
            cout << "First player turn (X) choose your option : ";
            players = 1;
        }
        else
        {
            cout << "Second player turn (O) choose your option : ";
            players = 2;
        }  
    
    cin >> op;
    if (op == 1)
    {
        i = 0, j = 0;
        input(players);
    }
    if (op == 2)
    {
        i = 0, j = 1;
        input(players);
    }
    if (op == 3)
    {
        i = 0, j = 2;
        input(players);
    }
    if (op == 4)
    {
        i = 1, j = 0;
        input(players);
    }
    if (op == 5)
    {
        i = 1, j = 1;
        input(players);
    }
    if (op == 6)
    {
        i = 1, j = 2;
        input(players);
    }
    if (op == 7)
    {
        i = 2, j = 0;
        input(players);
    }
    if (op == 8)
    {
        i = 2, j = 1;
        input(players);
    }
    if (op == 9)
    {
        i = 2, j = 2;
        input(players);
    }
    }

    if(check == false){
        cout << "It's a TIE" << endl;
    }
}

void print_options()
{
    int c = 0;
    for (int j = 0; j < 3; j++)
    {
        c = c + 1;
        cout << c << "_ " << j + 1 << 'A' << endl;
        c = c + 1;
        cout << c << "_ " << j + 1 << 'B' << endl;
        c = c + 1;
        cout << c << "_ " << j + 1 << 'C' << endl;
    }
}

void store()
{
    fstream file;
    file.open("gamedata.txt", ios::out);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {   
           
                file << array[i][j];
           
        }
            
        file << endl;
    }
       file.close();
    
}


int load()
{   
    int count = 0;
    string line;
    fstream file;
    file.open("gamedata.txt", ios::in);
    for (int i = 0; i < 3; i++)
    {   
        getline(file,line);
        for (int j = 0; j < 3; j++)
        {
            if ( i > 2)
            {
                break;
            }
            if ( i < 3)
            {
                array[i][j] = line[j];
                if (array[i][j] == "X" || array[i][j] == "O")
                {
                    count++;
                }
            }
        }
        
    }
    
    return count;
}

void input( int g )
{
    if (array[i][j] != "-")
    {
        cout << "invalid option this box is already taken" << endl;
        flag = true ;
    }
    else
    {   if ( g == 1)
        {
            array[i][j] = "X";
            players = 0;
        }
        if ( g == 2)
        {
            array[i][j] = "O";
            players = 0;
        }
    }
    
    store();
    cout << "enter e to play another turn and b for back" << endl;
    cin >> c;
    if (count1 == 2)
    {
        count1 = 0;
    }
    system("cls");
    
}

int main_menue()
{   
    header();
    int op = 0;
    cout << "1_ Start New Game " << endl;
    op = check_resume();
    if ( op != 0)
    {
        cout << "2_ Resume Game" << endl;
    }
    cout << "3_ Exit " << endl;
    cin >> op;
    system("cls");
    return op ;
}

int check_resume()
{   
    int k = 0;
    for (int i = 0 ; i < 3 ; i++)
    {
        for (int j = 0 ; j < 3 ; j++)
        {
            if(array[i][j] == "X" || array[i][j] == "O" )
            {
                k++;
            }
        }
    }
    return k ;
}
void start_game()
{ 
    for (int i =0 ; i < 3 ; i++)
    {
        for (int j = 0 ; j < 3 ; j++)
        {
            array[i][j] = "-" ;
        }
    }
}

void header()
{
    cout << "------------------------------------------------------" << endl; 
    cout << ">>>>>>>>>>>>>>>>>>>" << " TIC TAC TOE " << "<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "------------------------------------------------------" << endl;    

}