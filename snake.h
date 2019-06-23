#ifndef SNAKE_H
#define SNAKE_H

class Board
{
public:
    const int width;
    const int height;

    Board(int x = 20, int y = 20, int z = 2);
    ~Board(){};
    void printBoard();
    void repr();
    void draw();
};

class Point
{
public:
    int x;
    int y;
    Point *pNext;

    Point(int _x, int _y);
    ~Point();
    void draw();
};

class Food : public Point
{
public:
    Food(int _x, int _y) : Point(_x, _y){};
};

class Snake
{
public:
    Point *head;
    Point *tail;

    Snake(Point *p);
    ~Snake(){};

    void move(int key);
    void grow(Point *p);
    void draw();
    void drop();
};

class Game
{
public:
    Game(Snake s, Board b);

    void start();
    void draw(Food *f);
    bool isOver();
    void Over();

private:
    Snake snake;
    Board board;
    double score;
    int nGame;
};

#endif // SNAKE_H
