#include <iostream>
#include <fstream>
using namespace std;
const int grid = 3;

char board[grid][grid] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

void store();
int load();
void configuration();
void game();
void swapper();
char winner();
bool place_marker(int slot);


int current_player;
char current_marker;




main()
{
    load();
    game();
    // store();
}



void configuration()
{
    cout << board[0][0] << "\t\t|" << board[0][1] << "\t\t|" << board[0][2] << endl;
    cout << "_________________________________________          " << endl;
    cout << board[1][0] << "\t\t|" << board[1][1] << "\t\t|" << board[1][2] << endl;
    cout << "_________________________________________          " << endl;
    cout << board[2][0] << "\t\t|" << board[2][1] << "\t\t|" << board[2][2] << endl;
}

bool place_marker(int slot)
{
    int row = slot / 3;
    int col;

    if (slot % 3 == 0)
    {
        row = row - 1;
        col = 2;
    }
    else
    {
        col = (slot % 3) - 1;
    }
    if (board[row][col] != 'X' && board[row][col] != 'O')
    {
        board[row][col] = current_marker;
        return true;
    }

    else{
        return false;
    }
}
char winner()
{
    for (int i = 0; i < 3; i++) // H O R I Z O N T A L     C H E C K
    {
        if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
        {
            return current_player;
        }
    }

    for (int i = 0; i < 3; i++) // V E R T I C A L     C H E C K
    {
        if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
        {
            return current_player;
        }
    }

    if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))  // D I A G O N A L     C H E C K
    {

        return current_player;
    }
    if ((board[2][0] == board[1][1]) && (board[1][1] == board[0][2]))
    {

        return current_player;
    }

    return 0;
}

void game()
{
    char marker_p1; // Player 1 marker
    cout << "Player 1,Choose your symbol:";
    cin >> marker_p1;
    while(!(marker_p1 == 'X' || marker_p1 == 'O')) // Condition for making only X and O VALID players
    {
        cout<<"Invalid Player\n"<<endl;
        cout<<"Enter again...";
        cin>>marker_p1;
        cout<<"\n\n";
    }
    
    char option;
    int i = load();
    if (i != 0)
    {
        cout<<"Do you want to continue previous game.(Y/N)"<<endl;
        cin>>option;
        if(option == 'N'){
            for (int  i = 0; i < grid; i++)
            {
                for (int j = 0; j < grid; j++)
                {
                    board[i][j] = i* grid + j + 1 + 48;
                }
                
            }
            i = 0;   
        }
    }
    
    current_player = 1;
    current_marker = marker_p1;

    configuration();
    int player_won;

    for (; i < 9; i++)
    {
        int slot;
        cout << "\n\n";
        cout << "It's player" << current_player << "'s turn.Enter your slot:";
    
        cin >> slot;
        cout << "\n\n";
        if (slot < 1 || slot > 9)                                                                  //Condition so that user enters number only between 1 and 9
        {
            cout<<"Invalid Slot";
            i--;
            continue;
        }
        
        if(!place_marker(slot)){                                                                 // Condition to check if the slot user entered is occupied
            cout<<"The position you entered is already occupied! Try another slot";
            i--;
            continue;
        };
        configuration();

        player_won = winner();

        if (player_won == 1)
        {
            cout << "Player one WON! Congratulations!";
            return;
        }

        if (player_won == 2)
        {
            cout << "Player two WON! Congratulations!";
            return;
        }

        swapper();
        
    }

    player_won = winner();

    if (player_won == 1)
    {
        cout << "Player one WON! Congratulations!";
    }

    if (player_won == 2)
    {
        cout << "Player two WON! Congratulations!";
    }

    if (player_won == 0)
    {
        cout << "Its a TIE";
    }
}

void swapper()                          //S W A P S player and marker,I've made two decision variables because user can choose either of X or O as player 1
{
    if (current_marker == 'X')
    {
        current_marker = 'O';
    }
    else
    {
        current_marker = 'X';
    }

    if (current_player == 1)
    {
        current_player = 2;
    }
    else
    {
        current_player = 1;
    }
}
void store(){
    fstream file;
    file.open("save_game.txt",ios::out);
    for (int  i = 0; i < grid; i++)
    {
        for (int j = 0; j < grid; j++)
        {
            file<<board[i][j];
        }
        file<<endl;
    }
    
    file.close();
}

int load(){
    int count = 0;
    string line;
    fstream file;
    file.open("save_game.txt",ios::in);
    for (int i = 0; i < grid; i++)
    {   
        getline(file,line);
        for (int j = 0; j < grid; j++)
        {
            board[i][j] = line[j];
            if (board[i][j] == 'X' || board[i][j] == 'O')
            {
                count++;
            }
            
        }
        
    }
    file.close();
    
    return count;
}