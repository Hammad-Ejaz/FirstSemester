using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using EZInput;

namespace SpaceShooter_Classes_
{
    class Program
    {
        public static char[,] space = new char[15, 70] {
{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};
        
        
        class Ship
        {
            public char shape;
            public int x;
            public int y;
            public int health;
            public int lives;
        }
        static bool GameRun = true;
        static Ship Player = new Ship();
        
        static List<Ship> Enemies = new List<Ship>();
        static void Main(string[] args)
        {

            Player.health = 100;
            Player.lives = 3;
            Player.shape = '>';
            FindPosition(Player);
            
            Console.SetCursorPosition(0, 0);
            Display();
            while (GameRun)
            {
                MoveBullets('-', 1);
                Thread.Sleep(25);
                FindPosition(Player);
                if (Keyboard.IsKeyPressed(Key.Space))
                {
                    GenerateBullets(Player.x, Player.y);
                }
                MoveBullets('-', 1);
                MovePlayer();
                MoveEnemies();
                
                GenerateEnemies();
                
            }
        }
        static void MovePlayer()
        {
            if (Keyboard.IsKeyPressed(Key.UpArrow))
            {
                MoveShip(Player, -1, 0);
            }
            if (Keyboard.IsKeyPressed(Key.DownArrow))
            {
                MoveShip(Player, 1, 0);
            }

            if (Keyboard.IsKeyPressed(Key.LeftArrow))
            {
                MoveShip(Player, 0, -1);
            }
            if (Keyboard.IsKeyPressed(Key.RightArrow))
            {
                MoveShip(Player, 0, 1);
            }
        }
        static void MoveEnemies()
        {
            for (int i = 0; i < Enemies.Count; i++)
            {
                if(space[Enemies[i].x, Enemies[i].y-1] == '-')
                {
                    BulletToEnemy(Enemies[i].x, Enemies[i].y);
                }
                else if(Enemies[i].y == 1)
                {
                    space[Enemies[i].x, Enemies[i].y] = ' ';
                    Console.SetCursorPosition(Enemies[i].y,Enemies[i].x);
                    Console.Write(' ');
                    Enemies.RemoveAt(i);
                }
                else
                {
                    MoveShip(Enemies[i], 0, -1);
                }
                
            }
        }
        static void FindPosition(Ship Player)
        {
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 70; j++)
                {
                    if(space[i,j] == Player.shape)
                    {
                        Player.x = i;
                        Player.y = j;
                        break;
                    }
                }
            }
        }
        static void Display()
        {
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 70; j++)
                {
                    Console.Write(space[i, j]);
                }
                Console.Write("\n");
            }
        }
        static void MoveShip(Ship Player, int x, int y)
        {
            if((Player.x + x < 14 && Player.x + x > 0) && (Player.y + y < 69 && Player.y + y > 0))
            {
                space[Player.x, Player.y] = ' ';
                Console.SetCursorPosition(Player.y, Player.x);
                Console.Write(space[Player.x, Player.y]);
                Player.x += x;
                Player.y += y;

                space[Player.x, Player.y] = Player.shape;
                Console.SetCursorPosition(Player.y, Player.x);
                Console.Write(space[Player.x, Player.y]);
            }
        }
        static void GenerateBullets(int x, int y)
        {
            if ((x < 14 && x > 0) && (y < 68&& y > 0))
            {
                space[x, y + 1] = '-';
                Console.SetCursorPosition(y+1, x);
                Console.Write(space[x, y + 1]);
            }
        }
        static void MoveBullets(char Shape, int dir)
        {
            for(int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 70; j++)
                {
                    if(space[i,j] == Shape)
                    {
                        space[i, j] = ' ';
                        Console.SetCursorPosition(j, i);
                        Console.Write(space[i, j]);
                        if (j > 0 && j < 68)
                        {
                            if(Shape == '-' && space[i, j+dir] == '<')
                            {
                                BulletToEnemy(i,j );
                            }
                            if (Shape == '.' && space[i, j + dir] == '>')
                            {
                                BulletToPlayer(i, j);
                            }
                            j += dir;
                            space[i, j] = Shape;
                            Console.SetCursorPosition(j, i);
                            Console.Write(space[i, j]);
                        }
                    }
                }
            }
        }
        static int Rand()
        {
            Random rand = new Random();
            int n = rand.Next(1, 14);
            return n;
        }
        static void GenerateEnemies()
        {
            Ship Enemy = new Ship();
            Enemy.x = Rand();
            Enemy.y = 68;
            Enemy.health = 25;
            Enemy.lives = 1;
            Enemy.shape = '<';

            Enemies.Add(Enemy);

            space[Enemy.x, Enemy.y] = Enemy.shape;
            Console.SetCursorPosition(Enemy.y, Enemy.x);
            Console.Write(space[Enemy.x, Enemy.y]);
        }
        static void BulletToEnemy(int x, int y)
        {
            for(int i = 0; i < Enemies.Count; i++)
            {
                if(Enemies[i].x == x && Enemies[i].y == y)
                {
                    Console.SetCursorPosition(Enemies[i].x, Enemies[i].y);
                    Console.Write(' ');
                    Enemies.RemoveAt(i);
                }
            }
        }
        static void BulletToPlayer(int x, int y)
        {
            if(Player.health > 25)
            {
                Player.health -= 25;
            }
            else
            {
                if(Player.lives > 1)
                {
                    Player.lives--;
                    Player.health = 100;
                }
                else
                {
                    GameRun = false;
                }
            }
        }
    }
}
