#include <stdbool.h>
#include <stdio.h>

#define EMPTY 0
#define SQUARE_SIZE 9

typedef char SquareValT;

bool solve(int row_index, int col_index, SquareValT board[SQUARE_SIZE][SQUARE_SIZE]);
bool valid(int row_index, int col_index, SquareValT board[SQUARE_SIZE][SQUARE_SIZE]);

void print_board(SquareValT board[SQUARE_SIZE][SQUARE_SIZE]);

int main()
{
  SquareValT board[SQUARE_SIZE][SQUARE_SIZE] = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
                                                {6, 0, 0, 1, 9, 5, 0, 0, 0},
                                                {0, 9, 8, 0, 0, 0, 0, 6, 0},
                                                {8, 0, 0, 0, 6, 0, 0, 0, 3},
                                                {4, 0, 0, 8, 0, 3, 0, 0, 1},
                                                {7, 0, 0, 0, 2, 0, 0, 0, 6},
                                                {0, 6, 0, 0, 0, 0, 2, 8, 0},
                                                {0, 0, 0, 4, 1, 9, 0, 0, 5},
                                                {0, 0, 0, 0, 8, 0, 0, 7, 9}};
  
  bool solved = solve(0, 0, board); 
  
  if (solved) 
  {
    printf("Solved\n");
  }
  else
  {
    printf("Not solved\n");
  }

  print_board(board);


  return 0; 
}


bool solve(int row_index, int col_index, SquareValT board[SQUARE_SIZE][SQUARE_SIZE])
{
  bool new_row_next_square = col_index == SQUARE_SIZE - 1;
  int next_row_index = new_row_next_square ? row_index + 1 : row_index;
  int next_col_index = new_row_next_square ? 0 : col_index + 1;

  if (row_index == SQUARE_SIZE)
  {
    return true;
  }
  else if (board[row_index][col_index] == EMPTY) 
  {
    for (SquareValT val = 1; val <= SQUARE_SIZE; val++)
    {
      board[row_index][col_index] = val;
      if (valid(row_index, col_index, board))
      {
        bool solved = solve(next_row_index, next_col_index, board);
        if (solved)
        {
          return true;
        }
      }
    }
    board[row_index][col_index] = EMPTY;
    return false;
  }
  else
  {
    bool validated = valid(row_index, col_index, board);
    return validated && solve(next_row_index, next_col_index, board);
  }
}

bool valid(int row_index, int col_index, SquareValT board[SQUARE_SIZE][SQUARE_SIZE])
{
  SquareValT current_value = board[row_index][col_index];

  // check row
  for (int i = 0; i < SQUARE_SIZE; i++)
  {
    if (i != col_index && current_value == board[row_index][i])
    {
      return false;
    }
  }

  // check column
  for (int i = 0; i < SQUARE_SIZE; i++)
  {
    if (i != row_index && current_value == board[i][col_index])
    {
      return false;
    }
  }

  // check square 
  int min_square_row_index = (row_index / 3) * 3;
  int max_square_row_index = min_square_row_index + 3;
  int min_square_col_index = (col_index / 3) * 3;
  int max_square_col_index = min_square_col_index + 3;
  for (int i = min_square_row_index; i < max_square_row_index; i++)
  {
    for (int j = min_square_col_index; j < max_square_col_index; j++)
    {
      if (i != row_index && j != col_index && current_value == board[i][j])
      {
        return false;
      }
    }
  }

  return true;
}

void print_board(SquareValT board[SQUARE_SIZE][SQUARE_SIZE])
{
  for (int row = 0; row < SQUARE_SIZE; row++)
  {
    if (row % 3 == 0) 
    {
      printf("#####################################\n");
    }
    else 
    {
      printf("-------------------------------------\n");
    }

    for (int col = 0; col < SQUARE_SIZE; col++)
    {
      if (col % 3 == 0)
      {
        printf("# %d ", board[row][col]);
      }
      else
      {
        printf("| %d ", board[row][col]);
      }
    }
    printf("#\n");
  }
  printf("#####################################\n");
}



