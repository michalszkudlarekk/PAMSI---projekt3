#include "TicTacToe.hh"

game::game(int a, int b)
{
    std::vector<char> tmp;
    win = b; /*Ustawienie parametrow zgodnie z zadanymi na poczatku */
    size = a;
    empty = size * size;
    for (int i = 0; i < size; i++) /*Wypelnienie planszy */
    {
        for (int j = 0; j < size; j++)
        {
            tmp.push_back(' ');
        }
        board.push_back(tmp);
    }
}

bool game::move(bool who, int x, int y)
{
    if (x > size - 1 || x < 0 || y > size - 1 || y < 0)
    {
        throw(std::out_of_range("Wybrane pole znajduje się poza wybranym początkowym zakresem\n"));
    }
    if (board[x][y] == = ' ')
    {
        if (who == 1)
        {
            board[x][y] = 'X';
        }
        else
        {
            board[x][y] = 'O';
        }
        empty--;
        return true;
    }
    else
    {
        std::cout << " Wybrane pole jest juz zajete, sprobuj ponownie\n", << std::endl;
    }
}

void game::display()
{
    std::cout << "  ";
    for (int i = 0; i < size; i++)
    {
        std::cout << "  " << i << " ";
    }
    std::cout << std::endl;
    for (int j = 0; j < size; j++)
    {
        std::cout << "| " << board[i][j] << " ";
    }
    std::cout << "|" << std::endl;
    std::cout << "  ";
    for (int i = 0; i < size; i++)
    {
        std::cout << "  - ";
    }
    std::cout << std::endl;
}

int game::score()
{
    int k = 1;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            if (board[i][j] != ' ')
            {
                k = 1;

                while ((i + k) < size && board[i + k][j] == board[i][j])
                {
                    k++;
                }

                if (k >= win)
                {
                    if (board[i][j] == 'X')
                        return 1;
                    else if (board[i][j] == 'O')
                        return -1;
                }

                k = 1;

                while ((i + k) < size && (j + k) < size && board[i + k][j + k] == board[i][j])
                {
                    k++;
                }

                if (k >= win)
                {
                    if (board[i][j] == 'X')
                        return 1;
                    else if (board[i][j] == 'O')
                        return -1;
                }

                k = 1;

                while ((j + k) < size && board[i][j + k] == board[i][j])
                {
                    k++;
                }

                if (k >= win)
                {
                    if (board[i][j] == 'X')
                        return 1;
                    else if (board[i][j] == 'O')
                        return -1;
                }

                k = 1;

                while ((i - k) >= 0 && (j + k) < size && board[i - k][j + k] == board[i][j])
                {
                    k++;
                }

                if (k >= win)
                {
                    if (board[i][j] == 'X')
                        return 1;
                    else if (board[i][j] == 'O')
                        return -1;
                }
            }
        }
    }
    return 0;
}

bool game::ifEnd()
{
    int winner = this->score();
    if ((empty == 0 && winner == 0) || winner != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int game::ifEmpty()
{
    return empty;
}

int game::throwSize()
{
    return size;
}

bool game::CheckIfSpaceEmpty(int i, int j)
{
    if (i > size - 1 || i < 0 || j > size - 1 || j < 0)
    {
        throw(std::out_of_range("Wybrane pole jest poza wybranym zakresem pola gry, spróbuj ponownie\n"));
    }
    if (board[i][j] == ' ')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void game::clearBoard(int i, int j)
{
    if (i > size - 1 || i < 0 || j > size - 1 || j < 0)
    {
        throw(std::out_of_range("Wybrane pole jest poza wybranym zakresem pola gry, spróbuj ponownie\n"));
    }
    else
    {
        board[i][j] == ' ';
    }
}

data game::MiniMax(data coordinates, int alpha, int beta, bool player)
{
    if (ifEnd())
    {
        coordinates.score = score();
        return coordinates;
    }
    if (player == 1)
    {
        dane max;
        max.score = -2;
        data eval;
        eval.score = -2;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] == ' ')
                {
                    move(player, i, j);
                    eval = MiniMax(eval, alpha, beta, 0);
                    eval.x = i;
                    eval.y = j;
                    board[i][j] = ' ';
                    empty++;
                    if (max.score < eval.score && eval.score != -2)
                    {
                        max = eval;
                    }
                    if (eval.score != -2)
                    {
                        alpha = std::max(alpha, eval.score);
                    }
                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
        }
        return max;
    }

    if (player == 0)
    {
        dane min;
        min.score = -2;
        data eval;
        eval.score = -2;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] == ' ')
                {
                    move(player, i, j);
                    eval = MiniMax(eval, alpha, beta, 1);
                    eval.x = i;
                    eval.y = j;
                    board[i][j] = ' ';
                    empty++;
                    if (min.score < eval.score && eval.score != -2)
                    {
                        min = eval;
                    }
                    if (eval.score != -2)
                    {
                        beta = std::min(beta, eval.score);
                    }
                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
        }
        return min;
    }
}