#include <iostream>
#include <cstdlib>
#include <ncurses.h>

#include "snake.h"

Board::Board(int x, int y, int z) : width(x * z), height(y)
{
    std::cout << "Initialized with width " << this->width;
    std::cout << " and height " << this->height << std::endl;
}

void Board::repr()
{
    std::cout << "A board with width " << this->width;
    std::cout << " and height " << this->height << std::endl;
}

void Board::draw()
{
    // draw the game board from left to right and up to down
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1)
            {
                // draw first or last row
                mvprintw(i, j, "#");
            }
            else
            {
                // draw rows in between
                if (j == width - 1 || j == 0)
                    mvprintw(i, j, "#");
            }
        }
    }
}

Point::Point(int _x, int _y) : x(_x), y(_y)
{
    pNext = NULL;
}

Point::~Point()
{
    delete pNext;
}

void Point::draw()
{
    mvprintw(y, x, "x");
}

Snake::Snake(Point *p)
{
    // initialize with a starting point
    head = p;
    tail = p;
}

void Snake::grow(Point *p)
{
    // stack the next point to head's next pointer
    head->pNext = p;
    head = p;
}

void Snake::drop()
{
    tail = tail->pNext;
}

void Snake::draw()
{
    Point *p = tail;
    while (p != NULL)
    {
        // std::cout << "(x, y) -> " << p->x << ", " << p->y << std::endl;
        mvprintw(p->y, p->x, "o");
        p = p->pNext;
    }
}

void Snake::move(int key)
{
    int _x;
    int _y;

    switch (key)
    {
    case KEY_RIGHT:
        _x = this->head->x + 1;
        _y = this->head->y;
        break;
    case KEY_LEFT:
        _x = this->head->x - 1;
        _y = this->head->y;
        break;
    case KEY_UP:
        _x = this->head->x;
        _y = this->head->y - 1;
        break;
    case KEY_DOWN:
        _x = this->head->x;
        _y = this->head->y + 1;
        break;
    default:
        _x = this->head->x;
        _y = this->head->y;
    }

    // have to allocate from heap, or value in stack will be overwritten
    Point *p = new Point(_x, _y);
    grow(p);
    drop();
    // head->x++;
}

Game::Game(Snake s, Board b) : snake(s), board(b)
{
    score = 0;
    nGame = 1;

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
}

void Game::start()
{
    // start playing the game
    int key;
    int key_pre = -1;

    Food *f = new Food(rand() % board.height, rand() % board.height);

    while (!isOver())
    {
        keypad(stdscr, TRUE);
        halfdelay(1);

        key = getch();

        if (key == -1)
            snake.move(key_pre);
        else
        {
            snake.move(key);
            key_pre = key;
        }

        draw(f);
    }
    Over();
}

void Game::draw(Food *f)
{
    clear();
    board.draw();
    snake.draw();
    f->draw();
    refresh();
}

bool Game::isOver()
{
    if (snake.head->x >= board.width || snake.head->x <= 1)
        return TRUE;

    if (snake.head->y >= board.height || snake.head->y <= 1)
        return TRUE;

    return FALSE;
}

void Game::Over()
{
    int mid = board.height / 2;
    mvprintw(mid, mid, "Game Over!");
    halfdelay(10);
}
