#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define BOARDSIZE 8
#define TRUE 1
#define FALSE 0

char board[BOARDSIZE][BOARDSIZE];
char gboard[BOARDSIZE][BOARDSIZE];

void build_board();
void build_gboard();
void print_board();
void print_gboard();
int findnearbymines(int, int);
void flushoutnearbymines(int, int);
void loss();
void win();
int checkforwin();
void playagain();
void start_game();

int main()
{
    printf("lets play........,");
    getch();
    start_game();
    return 0;
}

void print_board()
{
    int i, j;


    printf("  ");
    for(i = 1; i < BOARDSIZE - 1; i++)
        printf("%d ", i);
    printf("\n");

    
    for(i = 0; i < BOARDSIZE; i++)
    {
        for(j = 0; j < BOARDSIZE; j++)
            printf("%c ", board[i][j]);
        if(i > 0 &&  i < BOARDSIZE - 1)
            printf("%d", i);
        printf("\n");
    }
}


void print_gboard()
{
    int i, j;

    printf("  ");
    for(i = 1; i < BOARDSIZE - 1; i++)
        printf("%d ", i);
    printf("\n");

    for(i = 0; i < BOARDSIZE; i++)
        for(j = 0; j < BOARDSIZE; j++)
            if(i == 0 || i == BOARDSIZE - 1)
                gboard[i][j] = ' ';

    for(j = 0; j < BOARDSIZE; j++)
        for(i = 0; i < BOARDSIZE; i++)
            if(j == 0 || j == BOARDSIZE - 1)
                gboard[i][j] = ' ';

    for(i = 0; i < BOARDSIZE; i++)
    {
        for(j = 0; j < BOARDSIZE; j++)
        {
            printf("%c ", gboard[i][j]);
        }
        if(i > 0 &&  i < BOARDSIZE - 1)
            printf("%d", i);
        printf("\n");
    }
}

void build_board()
{
    int i, j;

    
    for(i = 0; i < BOARDSIZE; i++)
        for(j = 0; j < BOARDSIZE; j++)
            board[i][j] = '-';

   
    srand(time(NULL));

    
    for(j = 0; j < BOARDSIZE; j++)
    {
        int random = rand() % (BOARDSIZE - 1) + 1;
        board[random][j] = '*';
    }

    
    for(i = 0; i < BOARDSIZE; i++)
        for(j = 0; j < BOARDSIZE; j++)
            if(i == 0 || i == BOARDSIZE - 1)
                board[i][j] = ' ';

    for(j = 0; j < BOARDSIZE; j++)
        for(i = 0; i < BOARDSIZE; i++)
            if(j == 0 || j == BOARDSIZE - 1)
                board[i][j] = ' ';
}

void build_gboard()
{
    int i, j;

   
    for(i = 0; i < BOARDSIZE; i++)
        for(j = 0; j < BOARDSIZE; j++)
            gboard[i][j] = '-';


   
    for(i = 0; i < BOARDSIZE; i++)
        for(j = 0; j < BOARDSIZE; j++)
            if(i == 0 || i == BOARDSIZE - 1)
                gboard[i][j] = ' ';

    for(j = 0; j < BOARDSIZE; j++)
        for(i = 0; i < BOARDSIZE; i++)
            if(j == 0 || j == BOARDSIZE - 1)
                gboard[i][j] = ' ';
}

int findnearbymines(int row, int col)
{
    int mines = 0;

    
    if(board[row - 1][col] == '*')
        mines++;
    if(board[row + 1][col] == '*')
        mines++;
    if(board[row][col - 1] == '*')
        mines++;
    if(board[row][col + 1] == '*')
        mines++;

    if(board[row - 1][col + 1] == '*')
        mines++;
    if(board[row - 1][col - 1] == '*')
        mines++;
    if(board[row + 1][col + 1] == '*')
        mines++;
    if(board[row + 1][col - 1] == '*')
        mines++;

    return mines;
}


void loss()
{
    char ans;

    printf("\nYou've lost the game!");
    printf("\nWould you like to play again? (y/n) ");
    scanf(" %c", &ans);

    if(toupper(ans) == 'Y')
    {
        system("cls");
        start_game();
    }

    else
        exit(0);
}

void win()
{
    char ans;

    printf("\nYou've won the game");
    printf("\nWould you like to play again? (y/n)");
    scanf(" %c", &ans);

    if(toupper(ans) == 'Y')
    {
        system("cls");
        start_game();
    }

    else
        exit(0);
}


void flushoutnearbymines(int row, int col)
{
    int nearbymines = 0;
    int i = 0;

        nearbymines = findnearbymines(row, col);
        gboard[row][col] = (char)(((int)'0') + nearbymines);

        nearbymines = 0;
        
        while(nearbymines < 1 && i < row)
        {
            nearbymines = findnearbymines(row - i, col);
            gboard[row - i][col] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
      
        while(nearbymines < 1 && row + i < BOARDSIZE - 2)
        {
            nearbymines = findnearbymines(row + i, col);
            gboard[row + i][col] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
        
        while(nearbymines < 1 && i < col)
        {
            nearbymines = findnearbymines(row, col - i);
            gboard[row][col - i] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
      
        while(nearbymines < 1 && col + i < BOARDSIZE - 2)
        {
            nearbymines = findnearbymines(row, col + i);
            gboard[row][col + i] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
        
        while(nearbymines < 1 && col + i < BOARDSIZE - 2 && i < row)
        {
            nearbymines = findnearbymines(row - i, col + i);
            gboard[row + i][col + i] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
        
        while(nearbymines < 1 && i < row && i < row && i < col)
        {
            nearbymines = findnearbymines(row - i, col - i);
            gboard[row - i][col - i] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;

        while(nearbymines < 1 && row + i < BOARDSIZE - 2 && col + i < BOARDSIZE - 2)
        {
            nearbymines = findnearbymines(row + i, col + i);
            gboard[row + i][col + i] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
     
        while(nearbymines < 1 && row + i < BOARDSIZE - 2 && i < col)
        {
            nearbymines = findnearbymines(row + i, col - i);
            gboard[row + i][col - i] = (char)(((int)'0') + nearbymines);
            i++;
        }
}


int checkforwin()
{
    int i, j;

    for(i = 1; i < BOARDSIZE - 1; i++)
        for(j = 1; j < BOARDSIZE - 1; j++) {
            if(gboard[i][j] == '-' && board[i][j] != '*')
                return FALSE;
        }

    return TRUE;
}


void start_game()
{
    int row, col;

    build_board();
    build_gboard();
    print_gboard();

    for(;;)
    {
        do {
        printf("Enter selection:\n");
        printf("Row--> ");
        scanf("%d", &row);
        printf("Col--> ");
        scanf("%d", &col);
        } while(row < 1 || row > BOARDSIZE - 2 || col < 1 || col > BOARDSIZE - 2);


        if(board[row][col] == '*')
        {
            printf("You hit a MINE!\n");
            print_board();
            loss();
        }
        else
            flushoutnearbymines(row, col);

        print_gboard();

        if(checkforwin() == TRUE)
            win();


       
        // print_board();
    }
}

