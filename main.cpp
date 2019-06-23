#include <iostream>
#include <ncurses.h>

#include "snake.h"

int main()
{

    Point p(11, 12);
    Snake s(&p);
    Board b(20, 20);

    Game game(s, b);

    game.start();
    getch();
    endwin();

    return 0;
}
