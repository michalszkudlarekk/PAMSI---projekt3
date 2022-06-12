#include "TicTacToe.hh"

game::game(int a, int b)
{
    std::vector<char> tmp;
    /*Ustawienie parametrow zgodnie z zadanymi na poczatku */
    win = b;
    size = a;
    empty = size * size;

    for (int i = 0; i < size; i++) /*Wypelnienie kazdego pola planszy znakiem ' ' */
    {
        for (int j = 0; j < size; j++)
        {
            tmp.push_back(' ');
        }
        board.push_back(tmp);
    }
}

bool game::move(bool kto, int X, int Y)
{
    if (X > size - 1 || X < 0 || Y > size - 1 || Y < 0)
    {
        throw(std::out_of_range("Wybrane pole znajduje się poza wybranym początkowym zakresem."));
    }
    if (board[X][Y] == ' ') /*Jezeli wybrane pole jest puste, nalezy wpisac zadany symbol oraz zmniejszyć ilosc pustych pol */
    {
        if (kto == 1)
        {
            board[X][Y] = 'X';
        }
        else
        {
            board[X][Y] = 'O';
        }
        empty--;
        return true;
    }
    else
    {
        std::cout << "Wybrane pole znajduje się poza wybranym początkowym zakresem." << std::endl;
        return false;
    }
}

void game::display()
{
    /*Wyświetlenie cyfr pomocniczych u gory*/
    std::cout << "  ";
    for (int i = 0; i < size; i++)
    {
        std::cout << "  " << i << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < size; i++) /* Dla kazdej z linii*/
    {
        std::cout << i << " "; /*Wyświetlenie cyfr pomocniczych z boku*/

        for (int j = 0; j < size; j++) /*Wyswietlenie stanu pol w linijce */
        {
            std::cout << "| " << board[i][j] << " ";
        }
        std::cout << "|" << std::endl;
        std::cout << "  ";
        for (int i = 0; i < size; i++) /*Wyswietlenie linii odzielajacej */
        {
            std::cout << "  - ";
        }
        std::cout << std::endl;
    }
}

int game::result()
{
    int k = 1;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            if (board[i][j] != ' ') /* Instrukcja dziala gdy dane pole nie jest puste */
            {
                k = 1; /*Pierwszy warunek zwyciestwa - pola po kolei */
                while ((i + k) < size && board[i + k][j] == board[i][j])
                {
                    k++;
                }
                if (k >= win) /* Jesli nastapilo zwyciestwo zwroc odpowiednia liczbe */
                {
                    if (board[i][j] == 'X')
                        return 1;
                    else if (board[i][j] == 'O')
                        return -1;
                }

                k = 1; /*Drugi warunek zwyciestwa - po skosie */

                while ((i + k) < size && (j + k) < size && board[i + k][j + k] == board[i][j])
                {
                    k++;
                }

                if (k >= win) /* Jesli nastapilo zwyciestwo zwroc odpowiednia liczbe */
                {
                    if (board[i][j] == 'X')
                        return 1;
                    else if (board[i][j] == 'O')
                        return -1;
                }

                k = 1; /*Trzeci warunek zwyciestwa - po kolei */

                while ((j + k) < size && board[i][j + k] == board[i][j])
                {
                    k++;
                }

                if (k >= win) /* Jesli nastapilo zwyciestwo zwroc odpowiednia liczbe */

                {
                    if (board[i][j] == 'X')
                        return 1;
                    else if (board[i][j] == 'O')
                        return -1;
                }

                k = 1; /*Czwarty warunek zwyciestwa - po skosie (odwrotnie) */

                while ((i - k) >= 0 && (j + k) < size && board[i - k][j + k] == board[i][j])
                {
                    k++;
                }

                if (k >= win) /* Jesli nastapilo zwyciestwo zwroc odpowiednia liczbe */
                {
                    if (board[i][j] == 'X')
                        return 1;
                    else if (board[i][j] == 'O')
                        return -1;
                }
            }
        }
    }
    return 0; /* Jezeli brak zwyciestwa zwroc 0 */
}

bool game::isOver()
{

    int winner = this->result();
    if ((empty == 0 && winner == 0) || winner != 0) /*Jezeli gra sie zakonczyla zwroc 1, w innym przypadku zwroc 0 */
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
        throw(std::out_of_range("Wybrane pole znajduje się poza wybranym początkowym zakresem."));
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
        throw(std::out_of_range("Wybrane pole znajduje się poza wybranym początkowym zakresem."));
    }
    board[i][j] = ' ';
}

data game::MiniMax(data coordinates, int alpha, int beta, bool player)
{
    if (isOver()) /* Jesli koniec, zwroc wynik */
    {
        coordinates.result = result();
        return coordinates;
    }
    if (player == 1) /* Gracz X */
    {
        data max;
        max.result = -2; /* Inicjacja wartosci, ktore nie wystepuja*/
        data eval;
        eval.result = -2; /* Inicjacja wartosci, ktore nie wystepuja*/
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] == ' ') /* Wykonaj ruch dla kazdego pustego pola*/
                {

                    move(player, i, j); /* wykonanie ruchu */

                    eval = MiniMax(eval, alpha, beta, 0); /* sprawdzenie jak dobry jest to ruch */
                    eval.X = i;
                    eval.Y = j;

                    board[i][j] = ' '; /* cofniecie ruchu */
                    empty++;

                    if (max.result < eval.result && eval.result != -2) /* Jesli danych ruch jest lepszy od dotychczasowego najlepszego, zaktualizuj informacje o wykonanych ruchach */
                    {
                        max = eval;
                    }

                    if (eval.result != -2) /* Ustawienie alfa jako wieksza liczbe z nowego wyniku i poprzedniej alfy */
                        alpha = std::max(alpha, eval.result);

                    if (beta <= alpha) /* Jesli alfa wieksza badz rowa beta przerwij petle */
                    {
                        break;
                    }
                }
            }
        }
        return max;
    }

    if (player == 0) /* Gracz O */
    {
        data min;
        min.result = 2; /* Inicjacja wartosci, ktore nie wystepuja*/
        data eval;
        eval.result = -2; /* Inicjacja wartosci, ktore nie wystepuja*/
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {

                if (board[i][j] == ' ') /* Wykonaj ruch dla kazdego pustego pola*/
                {
                    move(player, i, j); /* wykonanie ruchu */

                    eval = MiniMax(eval, alpha, beta, 1); /* sprawdzenie jak dobry jest to ruch */
                    eval.X = i;
                    eval.Y = j;

                    board[i][j] = ' '; /* cofniecie ruchu */
                    empty++;

                    if (min.result > eval.result && eval.result != -2) /* Jesli danych ruch jest lepszy od dotychczasowego najlepszego, zaktualizuj informacje o wykonanych ruchach */
                    {
                        min = eval;
                    }

                    if (eval.result != -2) /* Ustawienie beta jako mniejsza liczbe z nowego wyniku i poprzedniej bety */
                        beta = std::min(beta, eval.result);

                    if (beta <= alpha) /* Jesli alfa wieksza badz rowa beta przerwij petle */
                    {
                        break;
                    }
                }
            }
        }
        return min;
    }
}
