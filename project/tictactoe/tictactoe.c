#include <stdio.h>
#include <limits.h>

void print(char grid[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        printf("-------------\n");
        printf("|");
        for (int j = 0; j < 3; j++)
        {
            printf(" %c |", grid[i][j]);
        }
        printf("\n");
    }
    printf("-------------\n");
}

int check_row(char grid[3][3], char player, int row)
{
    for (int col = 0; col < 3; col++)
    {
        if (grid[row][col] != player)
            return 0;
    }
    return 1;
}

int check_col(char grid[3][3], char player, int col)
{
    for (int row = 0; row < 3; row++)
    {
        if (grid[row][col] != player)
            return 0;
    }
    return 1;
}

int check_diagonal(char grid[3][3], char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][i] != player)
            return 0;
    }
    return 1;
}

int check_anti_diagonal(char grid[3][3], char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][2 - i] != player)
            return 0;
    }
    return 1;
}

int check_win(char grid[3][3], char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (check_row(grid, player, i))
            return 1;
    }

    for (int i = 0; i < 3; i++)
    {
        if (check_col(grid, player, i))
            return 1;
    }

    if (check_diagonal(grid, player))
        return 1;

    if (check_anti_diagonal(grid, player))
        return 1;

    return 0;
}

int full_grid(char grid[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}

int MINIMAX(char grid[3][3], char player)
{
    if (check_win(grid, 'O'))
        return 10;
    if (check_win(grid, 'X'))
        return -10;
    if (full_grid(grid))
        return 0;


    if (player == 'O') {
        int max_val = -INT_MAX;
        int best_move;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ') {
                    grid[i][j] = 'O';
                    int val = MINIMAX(grid, 'X');
                    printf("(O) val: %d(%d)\n", val, i * 3 + j + 1);

                    grid[i][j] = ' ';
                    if (val > max_val)
                        max_val = val;

                        int best_move = i * 3 + j + 1;
                    }
                }
            }

        printf("(O) max_val: %d(%d)\n", max_val, best_move );
        return max_val;

    } else {
        int min_val = INT_MAX;
        int best_move;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ') {
                    grid[i][j] = 'X';
                    int val = MINIMAX(grid, 'O');
                    printf("(X) val: %d(%d)\n", val,  i * 3 + j + 1);

                    grid[i][j] = ' ';
                    if (val < min_val)
                        min_val = val;
                        best_move = i * 3 + j + 1;
                }
            }
        }

        printf("(X) min_val: %d(%d)\n", min_val, best_move);
        return min_val;
    }
}

int findInvincibleMove(char grid[3][3]) {
    int best_val = -INT_MAX;
    int invincible_move;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == ' ') {
                grid[i][j] = 'O';
                int move_val = MINIMAX(grid, 'X');
                grid[i][j] = ' ';
                printf("move_val:%d(%d)\n", move_val, i * 3 + j + 1);

                if (move_val > best_val) {
                    best_val = move_val;
                    invincible_move = i * 3 + j + 1;
                }
            }
        }
    }
    printf("invincible_move:%d(%d)\n", best_val, invincible_move);
    return invincible_move;
}



int main()
{
    char grid[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    printf("Welcome to tictactoe game!\nYou are X, computer is O\n");
    printf("Choose a position from 1 to 9\n");
    print(grid);


    while (1)
    {
        int pos = -1;
        printf("Enter a position: ");
        scanf("%d", &pos);

        if (pos < 1 || pos > 9)
        {
            printf("Position not valid, try again :(\n");
            continue;
        }

        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;

        if (grid[row][col] != ' ')
        {
            printf("Position already occupied, try again :(\n");
            continue;
        }

        grid[row][col] = 'X';

        print(grid);

        if (check_win(grid, 'X'))
        {
            printf("Congratulation! You won!!\n");
            break;
        }
        if (full_grid(grid))
        {
            printf("Draw!");
            break;
        }


        int pc_move = findInvincibleMove(grid);
        row = (pc_move - 1) / 3;
        col = (pc_move - 1) % 3;
        grid[row][col] = 'O';

        print(grid);

        if (check_win(grid, 'O'))
        {
            printf("PC won! Try again\n");
            break;
        }
        if (full_grid(grid))
        {
            printf("Draw!1n");
            break;
        }
    }
}
