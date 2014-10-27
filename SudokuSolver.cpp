
#include <stdio.h>

#define UNASSIGNED 0

#define N 9

#include <stdlib.h>
#include <string.h>

bool FindUnassignedLocation(int grid[N][N], int &row, int &col);

bool isSafe(int grid[N][N], int row, int col, int num);

bool SolveSudoku(int grid[N][N])
{
    int row, col;

    if (!FindUnassignedLocation(grid, row, col))
       return true; // success!


    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;

            if (SolveSudoku(grid))
                return true;

            grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}

bool FindUnassignedLocation(int grid[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

bool UsedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

bool isSafe(int grid[N][N], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) &&
           !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row%3 , col - col%3, num);
}

void printGrid(int grid[N][N])
{
    FILE * Output;
    Output = fopen("data.txt", "a");
    int row,col;
    for (row = 0; row < N; row++)
    {
       for (col = 0; col < N-1; col++)
             {
                    fprintf(Output, "%d",grid[row][col]);
                    fprintf(Output, ",");
             }
        fprintf(Output, "%d",grid[row][col]);
        fprintf(Output, "\n");
             //printf("%2d", grid[row][col]);
        //printf("\n");
    }
    fclose(Output);
}

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");tok && *tok;tok = strtok(NULL, ",\n"))
    {
        // printf("Field 3 would be %s\n", tok);
        if (!--num)
            return tok;
    }
    return NULL;
}

int main()
{


    char line[1024];
    int i=0;
    int grid[N][N];
    for(int j=0;j<9;j++)
    {
        FILE* stream = fopen("input.txt", "r");
        while (fgets(line, 1024, stream))
        {
            char* tmp = strdup(line);
        //    printf("Field 3 would be %s\n", getfield(tmp, j+1));

             grid[i++][j]= atoi(getfield(tmp, j+1));
            free(tmp);
        }
        i=0;
    }
   // printGrid(grid);
   /* int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    */
    if (SolveSudoku(grid) == true)
          printGrid(grid);
    else
         printf("No solution exists");

    return 0;
}
