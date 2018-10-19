#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <process.h>
#include <windows.h>
#include <vector>

#define x_length 10
#define y_length 25

using namespace std;

char map_game[x_length][y_length];
char mov;
bool end_game;
bool pause_game;
int prv_record = 0;
char vald_mov;
string user;

typedef struct BOT
{
	int yhead;
	int xhead;

	vector<BOT>tails;
	int size;
	int score;
	string user;
	char head_piece;
	char piece;
	int follow;
}BOT;

typedef struct 
{
	int x_pos;
	int y_pos;
	char food;
}FOOD;

BOT Snake;
FOOD point;

void new_food()
{
	int random_x;
	int random_y;

	srand( (unsigned)time(NULL));
	do
	{
		random_x = rand()%(x_length);
		random_y = rand()%(y_length);

		if((( random_y == 0 || random_y == y_length-1)) || ((random_x == 0) || (random_x == x_length-1)))
		{
			random_x = Snake.xhead;
			random_y = Snake.yhead;
		}

		for(int i = 0; i < Snake.tails.size(); i++)
		{
			if(Snake.tails.at(i).xhead == random_x && Snake.tails.at(i).yhead == random_y)
			{
				random_x = Snake.xhead;
				random_y = Snake.yhead;				
			}
		}

	}while((Snake.xhead == random_x) && (Snake.yhead == random_y));
	point.x_pos = random_x;
	point.y_pos = random_y;	
}

void generate_food()
{
	int random_x;
	int random_y;

	srand( (unsigned)time(NULL));
	do
	{
		random_x = rand()%(x_length);
		random_y = rand()%(y_length);

		if((( random_y == 0 || random_y == y_length-1)) || ((random_x == 0) || (random_x == x_length-1)))
		{
			random_x = Snake.xhead;
			random_y = Snake.yhead;
		}

	}while((Snake.yhead == random_y) && (Snake.xhead == random_x));

	point.x_pos = random_x;
	point.y_pos = random_y;
}

void tail_follow()
{
	if(Snake.tails.size() != 0)
	{
		for(int i = Snake.tails.size()-1; i >= 0; i--)
		{
			if(Snake.tails.at(i).follow != 0)
			{
				 Snake.tails.at(i).follow--;
			}

			if(i == 0)
			{
				Snake.tails.at(i).xhead = Snake.xhead;
				Snake.tails.at(i).yhead = Snake.yhead;
			}
			else
			{
				Snake.tails.at(i).xhead = Snake.tails.at(i-1).xhead;
				Snake.tails.at(i).yhead = Snake.tails.at(i-1).yhead;
			}		
		}
	}
}

void tail_create()
{
	if(Snake.tails.size() == 0)
	{
		BOT new_tail;

		new_tail.xhead = Snake.xhead;
		new_tail.yhead = Snake.yhead;
		new_tail.follow = Snake.size;

		Snake.tails.push_back(new_tail);
	}
	else
	{
		BOT new_tail;

		new_tail.xhead = Snake.tails.at(Snake.tails.size()-1).xhead;
		new_tail.yhead = Snake.tails.at(Snake.tails.size()-1).yhead;
		new_tail.follow = Snake.size;

		Snake.tails.push_back(new_tail);		
	}
}

bool tail_colision(int pos_x, int pos_y)
{
	if(Snake.tails.size() != 0)
	{
		for(int x = 0; x < Snake.tails.size(); x++)
		{
			if((Snake.tails.at(x).xhead == pos_x) && (Snake.tails.at(x).yhead == pos_y))
			{
				return true;
			}
		}
		return false;	
	}
	else
	{
		return false;
	}
}

bool print_tails(int i, int j)
{
	if(Snake.tails.size() != 0)
	{
		for(int x = 0; x < Snake.tails.size(); x++)
		{
			if(((Snake.tails.at(x).xhead == i) && (Snake.tails.at(x).yhead == j)) && Snake.tails.at(x).follow == 0)
			{
					cout << Snake.piece;
					return true;
			}
			if(Snake.tails.at(x).follow != 0)
			{
				return false;
			}
		}		
	}
	return false;
}

void printar_mapa()
{
	cout << "Player " << Snake.user << "\nScore " << Snake.score << endl;
	if(pause_game != true)
	{
		for(int i = 0; i < x_length; i++)
		{
			for(int j = 0; j < y_length; j++)
			{
				if(i == Snake.xhead && j == Snake.yhead)
				{
					cout << Snake.head_piece;
				}
				else if(i == point.x_pos && j == point.y_pos)
				{
					cout << point.food;
				}
				else if(print_tails(i, j) == false)
				{
					cout << map_game[i][j];		
				}
			}
			cout << endl;
		}
	}
	else
	{
		for(int i = 0; i < x_length; i++)
		{
			for(int j = 0; j < y_length; j++)
			{
				if((i == 4 && j == 10) || (i == 4 && j == 11)|| (i == 4 && j == 12)|| (i == 4 && j == 13)|| (i == 4 && j == 14))
				{
					if(j == 10)
					{
						cout << "P";	
					}
					else if(j == 11)
					{	
						cout << "A";
					}
					else if(j == 12)
					{
						cout << "U";
					}
					else if(j == 13)
					{
						cout << "S";
					}
					else if(j == 14)
					{
						cout << "E";
					}
				}
				else if(i == Snake.xhead && j == Snake.yhead)
				{
					cout << Snake.head_piece;
				}
				else if(i == point.x_pos && j == point.y_pos)
				{
					cout << point.food;
				}
				else if(print_tails(i, j) == false)
				{
					cout << map_game[i][j];		
				}
			}
			cout << endl;
		}		
	}
}

void prompt_clear()
{

	cout << string(6, '\n');
}

void apresentacao_regras()
{
	cout << "Insira o nome do Player 1 >> ";
	getline(cin, user);

	string message = "Ola " + user + " bem vindo(a) ao Snake Game.cpp!";
	for(int i = 0; i < message.size(); i++)
	{
		cout << message[i];
		Sleep(100);
	}
	cout << endl;
	Sleep(1500);
	message.clear();

	prompt_clear();
	message = "Controles:\nSetas direcionas: W A S D\nPause: P ( Para continuar, tecle qualquer tecla )\nBoa Sorte " + user + " !\n";
	for(int i = 0; i < message.size(); i++)
	{
		cout << message[i];
		Sleep(100);
	}
	Sleep(2000);
	prompt_clear();
}

void generate_map()
{
	for(int i = 0; i < x_length; i++)
	{
		for(int j = 0; j < y_length; j++)
		{
			if((i == 0 || i == x_length-1))
			{
				map_game[i][j] = '@';
			}
			else if(j == 0 || j == y_length-1)
			{
				map_game[i][j] = '@';
			}
			else
			{
				map_game[i][j] = ' ';
			}
		}
	}
}

void game_over()
{
	prompt_clear();
	string game_over  = "Game Over!\n" + Snake.user + ": Score ";
	for(int i = 0; i < game_over.size(); i++)
	{
		cout << game_over[i];
		Sleep(150);
	}
	cout << Snake.score << endl;
	
	if(Snake.score > prv_record)
	{
		cout << "New Highscore!" << endl;
		prv_record = Snake.score;
	}
	game_over.clear(); 
	Sleep(1000);
	end_game = false;
}

void movimento()
{
	if(mov == 'D' || mov == 'd')
	{
		if(tail_colision(Snake.xhead, Snake.yhead+1) == false)
		{	
			tail_follow();
			Snake.yhead++;
		}
		else if(tail_colision(Snake.xhead, Snake.yhead+1))
		{
			game_over();
		}

		if(map_game[Snake.xhead][Snake.yhead] == '@') 
		{
			Snake.yhead = 1;
		}

		if((Snake.xhead == point.x_pos) && (Snake.yhead == point.y_pos)) 
		{
			tail_create();
			Snake.score += 10;
			Snake.size++;
			new_food();
		}
	}
	else if(mov == 'W' || mov == 'w')
	{
		if(tail_colision(Snake.xhead-1, Snake.yhead) == false)
		{
			tail_follow();
			Snake.xhead--;
		}
		else if(tail_colision(Snake.xhead-1, Snake.yhead))
		{
			game_over();
		}

		if(map_game[Snake.xhead][Snake.yhead] == '@')
		{
			Snake.xhead = x_length-2;
		}

		if((Snake.xhead == point.x_pos) && (Snake.yhead == point.y_pos))
		{
			tail_create();
			Snake.score += 10;
			Snake.size++;
			new_food();
		}
	}
	else if(mov == 'A' || mov == 'a')
	{
		if(tail_colision(Snake.xhead, Snake.yhead-1) == false)
		{
			tail_follow();
			Snake.yhead--;
		}
		else if(tail_colision(Snake.xhead, Snake.yhead-1))
		{
			game_over();
		}

		if(map_game[Snake.xhead][Snake.yhead]  == '@' )
		{
			Snake.yhead = y_length-2;
		}


		if((Snake.xhead == point.x_pos) && (Snake.yhead == point.y_pos))
		{
			tail_create();
			Snake.score += 10;
			Snake.size++;
			new_food();
		}
	}
	else if(mov == 'S' || mov == 's')
	{
		if(tail_colision(Snake.xhead+1, Snake.yhead) == false)
		{
			tail_follow();
			Snake.xhead++;
		}
		else if(tail_colision(Snake.xhead+1, Snake.yhead))
		{
			game_over();
		}

		if(map_game[Snake.xhead][Snake.yhead] == '@')
		{
			Snake.xhead = 1;
		}


		if((Snake.xhead == point.x_pos) && (Snake.yhead == point.y_pos))
		{
			tail_create();
			Snake.score += 10;
			Snake.size++;
			new_food();
		}	
	}
}

void configs()
{
	{ // Inicializacao da cobra
		Snake.size = 1;
		Snake.yhead = 5;
		Snake.xhead = 5;
		Snake.follow = 0;
		Snake.head_piece = 'C';
		Snake.piece = 'O';
		Snake.tails.clear();
		Snake.score = 0;
		Snake.user = user;
	}

	{ // Gerando o mapa e comandos gerais
		generate_map();
		generate_food();
		
		end_game = true;

		point.food = '*';
	}
}

void inicio_jogo()
{
	char trash;
	configs();
	while(end_game) // Comecar jogo
	{
		printar_mapa();

		if(kbhit()!=0)
		{
			vald_mov = getch();
			if(vald_mov == 'W' || vald_mov == 'w')
			{
				mov = vald_mov;
			}
			if(vald_mov == 'A' || vald_mov == 'a')
			{
				mov = vald_mov;
			}
			if(vald_mov == 'S' || vald_mov == 's')
			{
				mov = vald_mov;
			}
			if(vald_mov == 'D' || vald_mov == 'd')
			{
				mov = vald_mov;
			}
			if(vald_mov == 'P' || vald_mov == 'p')
			{
				pause_game = true;
				prompt_clear();
				prompt_clear();
				printar_mapa();
				trash = getch();
				pause_game = false;
			}
		}

		movimento();
		prompt_clear();
		Sleep(150);
	}		
}

int main()
{
	char novamente;
	apresentacao_regras();
	do
	{
		inicio_jogo();
		cout << "Deseja jogar novamente ? (S/N)";
		cin >> novamente;
		if(novamente == 'S')
		{
			prompt_clear();
		}
		else
		{
			cout << "Fim de jogo :)" << endl;
		}
	}while(novamente == 'S');
}