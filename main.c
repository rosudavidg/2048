/* Rosu Gabriel - David
 * UNIVERSITATEA POLITEHNICA DIN BUCURESTI
 * rosudavidg@gmail.com
 * Aprilie 2017
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

char mygetch(void)
{
 // I don't own this function
    struct termios oldt,newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

void get_enter()
{
	char c = '\0';
	c = getchar();
}

void quit_game()
{
	printf("----------------------------------\n");
	printf("Jocul s-a inchis!\n");
	printf("----------------------------------\n");
}

void wrong_code()
{
	printf("----------------------------------\n");
	printf("Cod gresit! Pentru ajutor asapa \"M\"\n");
	printf("----------------------------------\n");
}

void print_menu()
{
	printf("----------------------------------\n");
	printf("Bine ai venit!\n");
	printf("----------------------------------\n");
	printf("Apasa \"S\" pentru a incepe  jocul!\n");
	printf("Apasa \"Q\" pentru a inchide jocul!\n");
	printf("----------------------------------\n");
}

void print_play()
{
	system("clear");
	int i;
	for(i = 3; i >= 1; i--)
	{
		printf("----------------------------------\n");
		printf("Apasa \"Q\" pentru a inchide jocul!\n");
		printf("----------------------------------\n");
		printf("    Jocul incepe in %d secunde.   \n", i);
		printf("----------------------------------\n");
		system("sleep 1");
		system("clear");
	}
}

void print_numbers(int numbers[4][4], int checked[4][4])
{
	int status = system("clear");
	int i, j;

	for(i = 0; i < 4; i++)
	{
		printf("|");
		for(j = 0; j < 4; j++)
		{
			if(checked[i][j] == 1)
			{
				if(numbers[i][j] < 10)
					printf("   ");
				else
				if(numbers[i][j] < 100)
					printf("  ");
				else
				if(numbers[i][j] < 1000)
					printf(" ");
				printf("%d|", numbers[i][j]);
			}
			else
				printf("    |");
		}
		printf("\n");
	}
}

void error_move(int numbers[4][4], int checked[4][4])
{
	system("clear");
	int i;
	for(i = 3; i >= 1; i--)
	{
		printf("----------------------------------\n");
		printf("               ALEGE\n");
		printf("    8            w            8\n");
		printf(" 4  5  6      a  s  d      4  2  6\n");
		printf("----------------------------------\n");
		printf("                 %d                 \n", i);
		printf("----------------------------------\n");
		system("sleep 1");
		system("clear");
	}

	fflush(stdin);
	fflush(stdout);
	print_numbers(numbers, checked);
}

void move_w(int numbers[4][4], int checked[4][4])
{
	int i, j;
	for(j = 0; j < 4; j++)
		for(i = 1; i < 4; i++)
			if(checked[i][j] == 1)
			{
				int k = i;
				while(k > 0 && checked[k - 1][j] == 0)
				{
					checked[k][j] = 0;
					checked[k - 1][j] = 1;
					numbers[k - 1][j] = numbers[k][j];
				    k--;
				}

				if(k != 0)
					if(numbers[k - 1][j] == numbers[k][j])
					{
						numbers[k - 1][j] *= 2;
						numbers[k][j] = 0;
						checked[k][j] = 0;
					}
			}
}

void move_a(int numbers[4][4], int checked[4][4])
{
	int i, j;
	for(i = 0; i < 4; i++)
		for(j = 1; j < 4; j++)
			if(checked[i][j] == 1)
			{
				int k = j;
				while(k > 0 && checked[i][k - 1] == 0)
				{
					checked[i][k] = 0;
					checked[i][k - 1] = 1;
					numbers[i][k - 1] = numbers[i][k];
				k--;
				}

				if(k != 0)
					if(numbers[i][k - 1] == numbers[i][k])
					{
						numbers[i][k - 1] *= 2;
						numbers[i][k] = 0;
						checked[i][k] = 0;
					}
			}
}

void move_s(int numbers[4][4], int checked[4][4])
{
	int i, j;
	for(j = 0; j < 4; j++)
		for(i = 2; i >= 0; i--)
			if(checked[i][j] == 1)
			{
				int k = i;
				while(k < 3 && checked[k + 1][j] == 0)
				{
					checked[k][j] = 0;
					checked[k + 1][j] = 1;
					numbers[k + 1][j] = numbers[k][j];
				k++;
				}

				if(k != 3)
					if(numbers[k + 1][j] == numbers[k][j])
					{
						numbers[k + 1][j] *= 2;
						numbers[k][j] = 0;
						checked[k][j] = 0;
					}
			}
}

void move_d(int numbers[4][4], int checked[4][4])
{
	int i, j;
	for(i = 0; i < 4; i++)
		for(j = 2; j >= 0; j--)
			if(checked[i][j] == 1)
			{
				int k = j;
				while(k < 3 && checked[i][k + 1] == 0)
				{
					checked[i][k] = 0;
					checked[i][k + 1] = 1;
					numbers[i][k + 1] = numbers[i][k];
				k++;
				}

				if(k != 3)
					if(numbers[i][k + 1] == numbers[i][k])
					{
						numbers[i][k + 1] *= 2;
						numbers[i][k] = 0;
						checked[i][k] = 0;
					}
			}
}

int check_if_exists(int checked[4][4])
{
	int i, j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(checked[i][j] == 0)
				return 1;
	return 0;
}

int compare_numbers(int numbers_1[4][4], int numbers_2[4][4])
{
	int i, j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(numbers_1[i][j] != numbers_2[i][j])
				return 0;
	return 1;
}

int check_lost(int numbers[4][4], int checked[4][4])
{
 //	Returns 1 if game is lost
 //	Else, returns 0
	int numbers_w[4][4];
	int numbers_s[4][4];
	int numbers_a[4][4];
	int numbers_d[4][4];

	int checked_w[4][4];
	int checked_s[4][4];
	int checked_a[4][4];
	int checked_d[4][4];

	int i, j;

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
		{
			numbers_w[i][j] = numbers[i][j];
			numbers_s[i][j] = numbers[i][j];
			numbers_d[i][j] = numbers[i][j];
			numbers_a[i][j] = numbers[i][j];

			checked_w[i][j] = checked[i][j];
			checked_s[i][j] = checked[i][j];
			checked_d[i][j] = checked[i][j];
			checked_a[i][j] = checked[i][j];
		}

	move_w(numbers_w, checked_w);
	if(compare_numbers(numbers_w, numbers) == 0)
		return 0;
	else
	{
		move_s(numbers_s, checked_s);
		if(compare_numbers(numbers_s, numbers) == 0)
			return 0;
		else
		{
			move_a(numbers_a, checked_a);
			if(compare_numbers(numbers_a, numbers) == 0)
				return 0;
			else
			{
				move_d(numbers_d, checked_d);
				if(compare_numbers(numbers_d, numbers) == 0)
					return 0;
				else
					return 1;
			}
		}
	}
}

int check_win(int numbers[4][4])
{
	int i, j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(numbers[i][j] == 2048)
				return 1;
	return 0;
}

struct game_time
{
	int s, m, h;
};
typedef struct game_time Game_time;

void get_time(int sec, Game_time *played_time)
{
	int x, y, z;
	x = sec / 3600;
	z = x * 3600;
	sec = sec - z;
	y = sec / 60;
	z = y * 60;
	sec = sec - z;

	played_time->s = sec;
	played_time->m = y;
	played_time->h = x;
}

void you_win(int numbers[4][4], int checked[4][4], time_t start)
{
	time_t stop = time(NULL);
	int total_sec = (stop - start);
	Game_time played_time;
	get_time(total_sec, &played_time);

	int sum = 0;
	int i, j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(checked[i][j] == 1)
				sum += numbers[i][j];

	system("clear");
	print_numbers(numbers, checked);
	printf("----------------------------------\n");
	printf("            Felicitari !          \n");
	printf("           AI CASTIGAT !          \n");
	printf("----------------------------------\n");
	printf("SCOR:\n%d\n", sum);
	printf("----------------------------------\n");
	printf("TIMP JOC: %d:%d:%d\n", played_time.h, played_time.m, played_time.s);
	printf("----------------------------------\n");
	printf("     Apasa \"M \"pentru meniu     \n");
	printf("----------------------------------\n");
	//system("sleep 3");

	//	Back to menu
	char menu;
	menu = mygetch();
	while(menu != 'M' && menu != 'm')
		menu = mygetch();
	system("clear");
	print_menu();
}

void you_lose(int numbers[4][4], int checked[4][4], time_t start)
{
	time_t stop = time(NULL);
	int total_sec = (stop - start);
	Game_time played_time;
	get_time(total_sec, &played_time);

	int sum = 0;
	int i, j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(checked[i][j] == 1)
				sum += numbers[i][j];

	system("clear");
	print_numbers(numbers, checked);
	printf("----------------------------------\n");
	printf("            Din pacate,           \n");
	printf("           Ai pierdut !          \n");
	printf("----------------------------------\n");
	printf("SCOR:\n%d\n", sum);
	printf("----------------------------------\n");
	printf("TIMP JOC: %d:%d:%d\n", played_time.h, played_time.m, played_time.s);
	printf("----------------------------------\n");
	printf("     Apasa \"M \"pentru meniu     \n");
	printf("----------------------------------\n");
	//system("sleep 3");

 //	Back to menu
	char menu;
	menu = mygetch();
	while(menu != 'M' && menu != 'm')
		menu = mygetch();
	system("clear");
	print_menu();

}

void play_game()
{
	time_t start = time(NULL);
	print_play();

	int numbers[4][4];
	int checked[4][4];

//	Initializare joc
	int i, j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
		{
			numbers[i][j] = 0;
			checked[i][j] = 0;
		}

//	Initializare variabile random
	int rnd_no_1, rnd_no_2;
	int rnd_i_1, rnd_j_1;
	int rnd_i_2, rnd_j_2;
	int rnd_perc;

	srand ( time(NULL) );

	rnd_perc = rand() % 2;

	if(rnd_perc == 1)
	{
		rnd_perc = rand() %100;
		if(rnd_perc < 90)
			rnd_no_2 = 2;
		else
			rnd_no_2 = 4;

		rnd_i_2 = rand() % 4;
		rnd_j_2 = rand() % 4;

		checked[rnd_i_2][rnd_j_2] = 1;
		numbers[rnd_i_2][rnd_j_2] = rnd_no_2;
	}

	rnd_perc = rand() %100;
	if(rnd_perc < 90)
		rnd_no_1 = 2;
	else
		rnd_no_1 = 4;

	rnd_i_1 = rand() % 4;
	rnd_j_1 = rand() % 4;

	checked[rnd_i_1][rnd_j_1] = 1;
	numbers[rnd_i_1][rnd_j_1] = rnd_no_1;

//	Sfarsit initializare variabile random

	print_numbers(numbers, checked);

	int lose = 0;
//	in game:   lose = 0
//	lost game: lose = 1
//	win game:  lose = 2

	while(lose == 0)
	{

//	Verificare pierdere
		if(check_lost(numbers, checked) == 1)
		{
			lose = 1;
			you_lose(numbers, checked, start);
			break;
		}
//	Verificare castig
		if(check_win(numbers) == 1)
		{
			lose = 2;
			you_win(numbers, checked, start);
			break;
		}

//	GET INPUT
	//INPUT FOR ARROW KEYS
		char move;
        int wrong_key = 0;
		move = mygetch();
		move = mygetch();
		move = mygetch();

		if(move == 'q')
			move = 'Q';
		if(move == 65)
			move = 'w';
		if(move == 66)
			move = 's';
		if(move == 68)
			move = 'a';
		if(move == 67)
			move = 'd';

		switch(move)
		{
			case 'w':
				move_w(numbers, checked);
				break;
			case 's':
				move_s(numbers, checked);
				break;
			case 'a':
				move_a(numbers, checked);
				break;
			case 'd':
				move_d(numbers, checked);
				break;
			case 'Q':
				you_lose(numbers, checked, start);
				lose = 1;
				break;
			default:
                wrong_key = 1;
	//			fflush(stdin);
    //			fflush(stdout);
	//			error_move(numbers, checked);
				break;
		}
        if(wrong_key != 1)
        {
       		if(lose == 1)
       			break;
       //	Adaugare numar nou random
       		if(check_if_exists(checked) == 1)
       		{

       			rnd_perc = rand() % 100;
       			if(rnd_perc < 90)
       				rnd_no_1 = 2;
       			else
       				rnd_no_1 = 4;

       			rnd_i_1 = rand() % 4;
       			rnd_j_1 = rand() % 4;


       			while(checked[rnd_i_1][rnd_j_1] == 1)
       			{
       				rnd_i_1 = rand() % 4;
       				rnd_j_1 = rand() % 4;
       			}

       			checked[rnd_i_1][rnd_j_1] = 1;
       			numbers[rnd_i_1][rnd_j_1] = rnd_no_1;
       		}

       //	Afisare tabla de joc
       		print_numbers(numbers, checked);
        }
	}
}

int main()
{
	system("clear");
	print_menu();
	char cod_menu = '\0';

	while(cod_menu != 'Q')
	{
		//cod_menu = getchar();
		cod_menu = mygetch();
		//get_enter();

		if(cod_menu == 's')
			cod_menu = 'S';
		if(cod_menu == 'q')
			cod_menu = 'Q';
		if(cod_menu == 'm')
			cod_menu = 'M';

		if( cod_menu == 'Q' || cod_menu == 'S' ||
			cod_menu == 'M' )
			system("clear");

		switch(cod_menu)
		{
			case 'S':
				play_game();
				break;
			case 'Q':
				quit_game();
				break;
			case 'M':
				print_menu();
				break;
			case '2':
				break;
			case '4':
				break;
			case '6':
				break;
			case '8':
				break;
			case '5':
				break;
			default:
				system("clear");
				print_menu();
				wrong_code();
		}
	}
	return 0;
}
