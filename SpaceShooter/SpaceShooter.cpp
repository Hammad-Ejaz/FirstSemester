/*Space shooter source code
          group members 
ahmad,ahmad zia ,ahmad jaleel and kamran*/
  //including basic header files
#include <iostream>  
//#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;
char username[30];  //takes user name of the user
const int row = 20; //horizontal lines in the frame
const int col = 25; // vertical lines in the frame
char dynamic[row][col]; // array for te game
char bullet = 186; // bullet fired by spaceship
char enemy = 157; //enemy character
int  life = 3/*total lifes*/, kills = 0/*will count kills*/, score = 0/*compute score*/, countenimies = 0/*count no. of enemies left*/;
int  level = 01;//initial level
bool gameplay = 1/*will hold gameplay*/ , one_time = 1/*becomes false after first try*/ ;
int  changeclr = 1;//to change color 
int  posx[20]; //hold position value of enemy at x axis
int  posy[20];//hold position value of enemy at y axis
int  x = 0;//variable to pass position value of enemy at x axis
int  y = 0;//variable to pass position value of enemy at y axis
int  tries = 01;//will count number of tries the game will be played
int  scorerange[50]={0};// used to find max score in n values of tries
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //to get a handle at console
void welcome();//includes welcome like messages
void instructions();//will display instructions from a file named as Instruction.txt
void hideCursor(); //will hide the cursor on the console
void frame();// generate a frame in which game will be played
void printing();//print dynamic array
void birthofaliens(int level); //will generate aliens according to level
void rgb();  //will change the color of console 
void movealiens(int level); //will move the aliens
void fire(int row, int mov); //for firing and also death of enemies
void movementupdate(int& horizon, int& mov); // will uppdate position of space ship
void dead(); //will decrease one life if enemy reached dotted line
void reset(); // reset the positions 
void gameover(); //gameover message
void reset1(); //will start again the game
void champion(); //display a message when the usr pass all 5 levels
int largest(int arr[], int n);  // find max score in score range array
void record(char name[],int score); // save the record for each user
int main()  // start 
{
	welcome();  // welcome message
	system("cls");  // clear the screen 
	if(one_time)   // check if user is playing for its first try
	{
		instructions();  // display instruction
	    _getch(); // press any key to continue
	    system("cls"); // clear screen
        cout << "Please enter your name first \n"; // username prompt
	    cin.getline(username,30); // storing user name 
	}
	system("cls"); // clear the screen
	hideCursor(); // hide console cursor
	frame(); // make a frame in the array
	dynamic[row - 2][col / 2] = 143;//spaceship placement
	printing(); // printing frame with spaceship
	int mov; // to store the movement
	int  horizon = col / 2; //current movement at y axis
	mov = horizon; 
	birthofaliens(level); //generating aliens
	printing(); // printing updated screen
	while (gameplay)  // run only if gameplay is true
	{	
		char key = _getch();  // takes input key
		switch (key)  // use of switch case
		{
			case 75:  //left arraw
			if (mov <= 1) // limiting the movement
				  break;
			if (mov == 2) // change colour if the spaceship touches frame
				rgb(); 
			mov--; //updated position
			break;	
		    case 77:  // right arrow key
			if (mov >= col - 2) // limiting the movement
				break;
			if (mov >= col - 3)  // changing color if spaceship touches the frame
				rgb();
			mov++; //update position
			break;
		    case 32: // space bar
			Beep(1500, 100); // generate a beep of 1500 for 100ms
			if (level > 4) //doubling the movement if level == 5
				movealiens(level);
			fire(row, mov);// fire function
			movealiens(level); // moving aliens
			break; 
		}
		movementupdate(horizon, mov);// for movement of spaceship
		printing();
		dead();
		if ((countenimies == 0) && level<=5) //level up condition
		{	
			level += 1;
			reset();
			birthofaliens(level);
		}
		if (life < 1) // game over condition
		{	
			scorerange[tries-1]=score;
			gameplay = false; 
			system("cls");
			gameover();
			cout << "Your score is " << score;
			char temp;
			cout << "\nDO YOU WANT TO PLAY AGAIN\nENTER 'Y' IF YES OR 'N' IF NO \n";
			cin>>temp;
			if (temp == 'y' || temp == 'Y') // asking for another try 
			{
				tries++;
				system("cls");	 

				gameplay = true;
				one_time = false;  // as one time is done so assigning it to 0 i.e false
				reset1(); // reseting values at it was for level 1
				main(); // calling main function
			}
			else  
			{
				scorerange[tries-1]=score; // storing scores
			    record(username,largest(scorerange, tries));	// here largest function will store the max value
			}
		}
		if (level > 5) // champ condition
		{
			scorerange[tries-1]=score;	 // saving scoe
			tries++; 
			char temp;
			gameplay = false;
			system("cls");
			champion();
			cout << "\nDO YOU WANT TO PLAY AGAIN\nENTER 'Y' IF YES OR 'N' IF NO \n";
			cin >> temp;
			if (temp == 'y' || temp == 'Y')
			{
				system("cls");
				gameplay = true;
				one_time = false;
				reset1();  // setting values as the values were for level 1
				main();
			}
			else
			{
				scorerange[tries-1]=score;  // storing scores
			    record(username,largest(scorerange, tries));
			}
		}
	}
}
void welcome()
{
	char name[] = { "SPACESHOOTER" };
	SetConsoleCursorPosition(hStdOut, { 0 , 7 });
	for (int i = 0; i < 12; i++)
	{
		Beep(400, 70);
		cout << "\t\t\t\t\t" << name[i] << "\n";
		rgb();
		Sleep(300);
	}
}
void instructions()
{
	ifstream inFile;
	inFile.open("Instruction.txt");
	char typer;
	while(!inFile.eof())
	{
		inFile.get(typer);
		
		if(!inFile.eof())
		{
			if(typer==32)
			    rgb();
			if(typer!=32)
			    Beep(303,100);
			cout<<typer;
		}
	}
	cout<<endl;
	inFile.close();	
}
void hideCursor()
{
	CONSOLE_CURSOR_INFO cci; 
	cci.dwSize = 1; // size = 1
	cci.bVisible = FALSE; // visibility false
	SetConsoleCursorInfo(hStdOut, &cci); // hide cursor
}
void frame()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == 0)
				dynamic[i][j] = 178;

			else if (i == row - 1)
				dynamic[i][j] = 178;
			else if (j == 0)
				dynamic[i][j] = 178;
			else  if (j == col - 1)
				dynamic[i][j] = 178;
			else if (i == row - 4)
				dynamic[i][j] = '.';
			else
				dynamic[i][j] = 32;
		}
	}
}
void printing()
{
	SetConsoleCursorPosition(hStdOut, { 24 , 0 });
	cout << char(143) << char(143) << char(143) << " S p A c E  S h o O t E r: " << char(143) << char(143) << char(143) << endl;
	cout << "S c O r E  " << score << endl;
	cout << "T O T A L   K I L L S    " << kills << endl;
	cout << "T O T A L   L I v e s    " << life << endl;
	cout << "L E V E L                " << level << endl;
	SetConsoleCursorPosition(hStdOut, { 0 , 7 });
	for (int i = 0; i < row; i++)
	{
		cout << "\t";
		cout << "\t";
		cout << "\t";
		for (int j = 0; j < col; j++)
		{
			cout << dynamic[i][j];
		}
		cout << endl;
	}
}
void birthofaliens(int level)
{  
	for (int j = 0; j < level + 2; j++)
	{
		
		countenimies = level + 2;
		x = rand() % 5 + 2;
		y = rand() % (col - 4) + 2;
		dynamic[x][y] = enemy;
		posx[j] = x;
		posy[j] = y;

		
}
 }
void rgb()
{
	SetConsoleTextAttribute(hStdOut, changeclr);
	changeclr += 1;
	if (changeclr > 15)
		changeclr = 1;
}
void movealiens(int level)
{
	for (int j = 0; j < level + 2; j++)
	{
		int prev;
		prev = posx[j];
		if ((dynamic[prev][posy[j]] != 32) && (posx[j] < row - 4))
		{
			posx[j] += 1;
			dynamic[posx[j]][posy[j]] = enemy;
			dynamic[prev][posy[j]] = 32;
		}
	}
}
void fire(int row, int mov)
{
	for (int i = row - 3; i >= 0; i--)
	{
		dynamic[i][mov] = bullet;
		if (i + 1 != row - 2)
		{
			dynamic[i + 1][mov] = 32;
		}
		//touching condition
		if ((dynamic[i - 1][mov] == enemy))

		{
			score += 10;
			kills += 1;
			countenimies -= 1;
			Beep(300,100);
			printing();
			dynamic[i - 1][mov] = char(176);
			Sleep(50);
			printing();
			Sleep(50);
			rgb();
			dynamic[i - 1][mov] = 32;
			dynamic[i][mov] = 32;
			printing();
			dynamic[row - 4][mov] = '.';
			break;
		}
		if(dynamic[row - 5][mov]==bullet)
		{
			dynamic[row - 4][mov] = '.';
			printing();
		}
		if (i == 0)
		{	
			dynamic[i][mov] = 178;
			printing();
			dynamic[i + 1][mov] = char(176);
			printing();
			rgb();
			Beep(300,100);
			Sleep(50);
           	dynamic[i + 1][mov] = char(32);
			
			   }
		printing();
	} 
}
void movementupdate(int& horizon, int& mov)//spaceship update
{
	dynamic[row - 2][horizon] = char(32);
	dynamic[row - 2][mov] = char(143);
	horizon = mov;
}
void dead()
{
	for (int i = 0; i < col; i++)
	{
		if (dynamic[row - 4][i] == enemy)
		{
			life -= 1;
			countenimies -= 1;
			dynamic[row - 4][i] = '.';
		}
	}
}
void reset()
{
	for (int i = 0; i < 20; i++)
	{
		posx[i] = 0;
		posy[i] = 0;
	}
}
void gameover()
{
	char name[] = { " GAME OVER " };
	SetConsoleCursorPosition(hStdOut, { 0 , 7 });
	for (int i = 0; i < 11; i++)
	{
		if (name[i] != 32)
		     Beep(400,70);
		cout << "\t\t\t\t\t" << name[i] << "\n";
		Sleep(300);
		rgb();
	}
	system("cls");	
}
void reset1()
{
	life = 3, kills = 0, score = 0, countenimies = 0;
	level = 1;
}
void champion()
{
	cout << "YOU ARE A CHAMP\n" ;
	cout << "You completed all the levels of the game\n";
	cout << "YOUR TOTAL SCORE IS " << score;
}
int largest(int arr[], int n)
{
    int i; 
    int max = arr[0]; 
    for (i = 1; i < n; i++)
      {
	  if (arr[i] > max)
            max = arr[i];
         }	
	return max;
}
void record(char name[],int score)
{
	ofstream file;
	file.open("Record.txt",ios::app );
	file << username << "\t" << score << "\n";
	file.close();
}
