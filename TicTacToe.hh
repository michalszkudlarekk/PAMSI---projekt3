#ifndef TICTACTOE_HH
#define TICTACTOE_HH

#include <vector>
#include <iostream>
#include <cmath>
#include <cctype>

struct data /* Struktura wykorzystywana przez algorytm Minimax do zwracania najlepszego ruchu*/
{
    int X, Y, result;
};

class game
{
private:
    std::vector<std::vector<char>> board;
    int win;   /*Warunki wygrania (ile symboli w rzedzie)*/
    int size;  /*Rozmiar planszy (np. 2x2, 3x3, 4x4 itd.) */
    int empty; /*Ile pustych miejsc zostało na planszy */

public:
    game(int a, int b);                                               /*a-rozmiar, b-ilosc w rzedzie do wygranej*/
    bool move(bool who, int X, int Y);                                /*Wybor albo kolka albo krzyzyka, x,y - koordynaty*/
    void display();                                                   /*Wyswietlenie aktualnej sytuacji na planszy w terminalu */
    int result();                                                     /*Wynik rozgrywki (1 dla wygranej x, -1 dla y, a 0 w przypadku remisu*/
    bool ifEnd();                                                     /*Sprawdzenie czy rozgrywka dobiegla konca, jeżeli tak zwraca 1 */
    int ifEmpty();                                                    /*Sprawdzenie ile zostalo pustych pol na planszy*/
    int throwSize();                                                  /*Zwraca rozmiar planszy*/
    bool CheckIfSpaceEmpty(int i, int j);                             /*Sprawdzenie czy dane pole jest puste, jezeli tak zwraca 1  */
    void clearBoard(int i, int j);                                    /* Resetuje pole do wartosci domyslnej*/
    data MiniMax(data coordinates, int alpha, int beta, bool player); /* Algorytm MiniMax z alfa,beta cieciami zawierajacy informacji na temat najlepszego dostepnego ruchu*/
};

#endif