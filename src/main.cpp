#include "../inc/TicTacToe.hh"

void playerMove(int &x, int &y, int size, char choice)
{

    std::cout << "Ruch " << choice << ":" << std::endl
              << "os x: ";
    std::cin >> x;
    std::cout << std::endl
              << "os y: ";
    std::cin >> y;

    if (x < 0 || y < 0 || x > size || y > size)
    {
        throw(std::out_of_range("Bledne wpolrzedne, sprobuj ponownie.\n"));
    }
}

int main()
{
    data move;
    move.X = -1;
    move.Y = -1;
    int size;
    int win;
    char choice = 'c';
    int x = -1, y = -1;
    std::cout << "Witaj w grze w Kolko i Krzyzyk!\n"
              << std::endl;
    std::cout << "Podaj wymiary planszy MxM do gry (Podaj M, przedzial 3-5):";
    std::cin >> size;
    if (!std::cin || size < 3 || size > 5)
    {
        std::cout << "Bledny rozmiar pola lub niepoprawny format; nie rozpoczeto gry, sprobuj ponownie.\n";
        return 0;
    }
    else
        std::cout << "Ile pol pod rzad aby wygrac (przedzial od 2 do 3):"; /* Teoretycznie wartosc ta mozna ustawic na wieksza, ale w praktyce zajmuje to zbyt duzo czasu dla algorytmu na podjecie decyzji, stad decyzja o maksymalne ilosci w postaci 3*/
    std::cin >> win;
    if (!std::cin || win < 2 || win > 3)
    {
        std::cout << "Bledna ilosc M wygrywajacych znakow w rzedzie, sprobuj ponownie.\n";
        return 0;
    }

    game gameOn(size, win);

    std::cout << "Co wybierasz? ( kolko 'O' zaczyna, 'X' jest drugi):";
    while (choice != 'O' && choice != 'X')
    {
        std::cin >> choice;
        if (choice != 'O' && choice != 'X')
        {
            std::cout << "W grze dostepne sa tylko kolko i krzyzk('O' i 'X'). Wybierz ponownie:";
        }
    }

    gameOn.display(); /* Wyświetlenie planszy */

    while (!gameOn.isOver())
    {

        if (choice == 'O') /* Jezeli gracz gra kolkie, w przeciwnym wypadku ruch wykonuje komputer */
        {
            playerMove(x, y, gameOn.throwSize(), choice);
            while (!gameOn.move(0, x, y))
            {
                playerMove(x, y, gameOn.throwSize(), choice);
            }
        }
        else
        {
            move = gameOn.MiniMax(move, -2, 2, 0);
            gameOn.move(0, move.X, move.Y);
        }

        gameOn.display(); /* Wyświetlenie planszy */

        if (gameOn.isOver() == false) /* Jezeli gra sie nie skoczyna oraz gracz gra X wykonuje on ruch, w przeciwnym razie ruch komputera */
        {
            if (choice == 'X')
            {
                playerMove(x, y, gameOn.throwSize(), choice);
                while (!gameOn.move(1, x, y))
                {
                    playerMove(x, y, gameOn.throwSize(), choice);
                }
            }
            else
            {
                move = gameOn.MiniMax(move, -2, 2, 1);
                gameOn.move(1, move.X, move.Y);
            }
        }

        gameOn.display(); /* Wyświetlenie planszy */
    }

    /* Podsumowanie wynikiw rozgrywki */
    if (gameOn.result() == 1)
        std::cout << "wygrywa X" << std::endl;
    else if (gameOn.result() == -1)
        std::cout << "wygrywa O" << std::endl;
    else
        std::cout << "remis" << std::endl;
    return 0;
}