#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <memory>
struct SnakeNode {
    int x;
    int y;
    SnakeNode *next;

    explicit SnakeNode(int x = 0, int y = 0, SnakeNode *next = nullptr);
};
struct Food {
    int x;
    int y;
    int score;
};
class Snake;
class Game {
public:
    void generateFood(int xRange, int yRange);
    bool isCollideWall(const std::unique_ptr<Snake> & snake, int xRange, int yRange);
    bool hasFood();
    Food food();
    void foodEaten();
    int score();
    void incScore(int score);
    void restart();
private:
    bool m_hasFood = false;
    Food m_food;
    int m_score = 0;
};

class Snake {
public:
    Snake();

    virtual ~Snake();

    enum Direction{
        UP = -2, DOWN = 2, LEFT = 1, RIGHT = -1
    };
    void move();
    void changeDirection(Direction newDirection);
    void grow();
    bool canEatFood(const Food & food);
    bool isEatSelf();
    void draw(const std::function<void(int,int,Direction)>& drawHead, const std::function<void(int,int)>& drawBody, const std::function<void(int,int)>& drawTail);
private:
    SnakeNode *head;
    SnakeNode *tail;
    Direction direction = UP;
    friend class Widget;
    friend class Game;
};
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    constexpr static int cellWidth = 32;
    constexpr static int totalWidth = 20;
    constexpr static int totalHeight = 15;
    constexpr static int screenWidth = totalWidth * cellWidth;
    constexpr static int screenHeight = totalHeight * cellWidth;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    std::unique_ptr<Snake> snake;
    std::unique_ptr<Game> game;
    bool isDead = false;
    bool showSnake = true;
private:
    bool isCollideWall();
    void generateFood();
    void restart();
};
#endif // WIDGET_H
