#include<bits/stdc++.h>
#define NONE    0
#define USER    1
#define CPU     2
#define TIE     3
#define INF     INT_MAX
using namespace std;

int user_cmd, cpu_cmd;
char arr[15];

void draw_board()
{
    //clearing board
    system("cls");

    // drawing board
    // for each row
    for(int i=7; i>0; i-=3)
    {
        printf("\n\t\t");

        // for each column
        for(int j=i; j<i+3; j++)
            printf("%c  ", arr[j]);
    }
}

int check_game_status()
{
    char c[] = {'X', 'O'};
    int a[] = {USER, CPU};

    for(int i=0; i<2; i++)
    {
        // for each row
        for(int j=1; j<=9; j+=3)
            if(arr[j] == c[i] && arr[j+1] == c[i] && arr[j+2] == c[i]) return a[i];

        // for each column
        for(int j=1; j<=3; j++)
            if(arr[j] == c[i] && arr[j+3] == c[i] && arr[j+6] == c[i]) return a[i];

        // for diagonals
        if(arr[1] == c[i] && arr[5] == c[i] && arr[9] == c[i]) return a[i];
        if(arr[3] == c[i] && arr[5] == c[i] && arr[7] == c[i]) return a[i];
    }

    // for each cell
    for(int i=1; i<=9; i++)
        if(arr[i] == '-') return NONE;

    return TIE;
}

int minimax(int turn, int level)
{
    int res, val, stat, store;
    stat = check_game_status();
    if(stat == CPU) return 1;
    if(stat == TIE) return 0;
    if(stat == USER) return -1;

    if(turn == CPU)     // CPU tries to maximize
    {
        res = -INF;

        // for each individual cell
        for(int i=1; i<=9; i++)
        {
            // if the cell is empty
            if(arr[i] == '-')
            {
                arr[i] = 'O';
                val = minimax(USER, level+1);
                arr[i] = '-';

                if(val >= res)
                {
                    res = val;
                    if(level == 0) cpu_cmd = i;
                }
            }
        }
    }
    else            // USER tries to minimize
    {
        res = INF;

        // for each individual cell
        for(int i=1; i<=9; i++)
        {
            // if the cell is empty
            if(arr[i] == '-')
            {
                arr[i] = 'X';
                val = minimax(CPU, level+1);
                arr[i] = '-';

                if(val <= res) res = val;
            }
        }
    }

    return res;
}

int main()
{
    int turn, stat;
    turn = USER;
    stat = NONE;

    // '-' means empty cell
    for(int i=1; i<=9; i++) arr[i] = '-';

    while(stat == NONE)
    {
        draw_board();

        if(turn == USER)
        {
            printf("\n\nEnter next move [1-9]:  ");
            scanf("%d", &user_cmd);

            if(arr[user_cmd] != '-') continue;
            else arr[user_cmd] = 'X';

            turn = CPU;
        }
        else
        {
            minimax(CPU, 0);
            arr[cpu_cmd] = 'O';

            turn = USER;
        }

        stat = check_game_status();
    }

    draw_board();
    printf("\n\n\t\t");
    if(stat == USER) printf("USER WON!!");
    if(stat == CPU) printf("CPU WON!!");
    if(stat == TIE) printf(" TIE!!");
    printf("\n\n");

    return 0;
}
