#include "widget.h"
#include <QtWidgets>
#include <memory>
#include <utility>
#include <map>
#include <random>
#include <iostream>
#define log std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
using std::pair;
using std::default_random_engine;
pair<int, int> mapToScreen(int x, int y) {
    return {
            x * Widget::cellWidth,
            (Widget::totalHeight - y - 1) * Widget::cellWidth
    };
}
void Game::generateFood(int xRange, int yRange)
{
    static default_random_engine e(time(nullptr));
    m_hasFood = true;
    m_food = {
            static_cast<int>(e() % xRange + 1),
            static_cast<int>(e() % yRange + 1),
            static_cast<int>(e() % 3 + 1)
    };
}

bool Game::isCollideWall(const std::unique_ptr<Snake> &snake, int xRange, int yRange)
{
    auto x = snake->head->x;
    auto y = snake->head->y;
    return x == 0 || x == xRange - 1 || y == 0 || y == yRange - 1;
}

bool Game::hasFood() {
    return m_hasFood;
}

Food Game::food() {
    return m_food;
}

int Game::score() {
    return m_score;
}

void Game::incScore(int score) {
    m_score += score;
}

void Game::foodEaten() {
    m_hasFood = false;
    incScore(m_food.score);
    log << "gain score: " << m_food.score << std::endl;
}

void Game::restart() {
    m_hasFood = false;
    m_score = 0;
}

SnakeNode::SnakeNode(int x, int y, SnakeNode *next)
        : x(x), y(y), next(next) {}
Snake::Snake() {
    head = new SnakeNode(1, 3);
    tail = new SnakeNode(1, 1);
    tail->next = new SnakeNode(1, 2, head);
}

Snake::~Snake() {
    log << std::endl;
    auto it = tail;
    while(it != nullptr) {
        auto t = it;
        it = it->next;
        delete t;
    }
}
pair<int, int> nextXY(int x, int y, Snake::Direction direction) {
    switch (direction) {
        case Snake::UP:
            y++;
            break;
        case Snake::DOWN:
            y--;
            break;
        case Snake::LEFT:
            x--;
            break;
        case Snake::RIGHT:
            x++;
            break;
    }
    return {x, y};
}
void Snake::move() {
    auto tmp = tail;
    tail = tail->next;
    auto [x, y] = nextXY(this->head->x, this->head->y, this->direction);
    tmp->x = x;
    tmp->y = y;
    head->next = tmp;
    head = tmp;
    head->next = nullptr;
}

void Snake::changeDirection(Snake::Direction newDirection) {
    if (this->direction + newDirection != 0)
    this->direction = newDirection;
}

void Snake::grow() {
    auto [x, y] = nextXY(this->head->x, this->head->y, this->direction);
    auto tmp = new SnakeNode(x, y);
    head->next = tmp;
    head = tmp;
}

bool Snake::canEatFood(const Food &food)
{
    auto [nextX, nextY] = nextXY(this->head->x, this->head->y, this->direction);
    return nextX == food.x && nextY == food.y;
}

bool Snake::isEatSelf()
{
    auto it = this->tail;
    while(it != this->head) {
        if (it->x == this->head->x && it->y == this->head->y) {
            return true;
        }
        it = it->next;
    }
    return false;
}

void Snake::draw(
        const std::function<void (int, int, Direction)>& drawHead,
        const std::function<void (int, int)>& drawBody,
        const std::function<void (int, int)>& drawTail)
{
    drawHead(this->head->x, this->head->y, this->direction);
    auto it = this->tail;
    while(it != this->head) {
        drawBody(it->x, it->y);
        it = it ->next;
    }
}


Widget::Widget(QWidget *parent)
    : QWidget(parent), snake(std::make_unique<Snake>()),
    game(std::make_unique<Game>())
{
    resize(screenWidth, screenHeight);
    auto timer = new QTimer(this);
    timer->setInterval(200);
    connect(timer, &QTimer::timeout, [this](){
        if (!isDead) {
            if (!this->game->hasFood()) {
                generateFood();
                this->snake->move();
            } else {
                if (this->snake->canEatFood(this->game->food())) {
                    qDebug() << "eat food";
                    this->snake->grow();
                    this->game->foodEaten();
                } else {
                    this->snake->move();
                }
            }
            if (this->snake->isEatSelf() || isCollideWall()) {
                qDebug() << "game over";
                isDead = true;
                auto ret = QMessageBox::question(nullptr, tr("Game Over"), tr("Restart Game?"));
                if (ret == QMessageBox::Yes) {
                    restart();
                } else {
                    qApp->exit();
                }
            }
        }
        this->update();
    });
    timer->start();
}

Widget::~Widget()
= default;

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // draw wall
    painter.drawTiledPixmap(0, 0, screenWidth, screenHeight, QPixmap(":/res/wall.png"));
    painter.save();
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawRect(cellWidth, cellWidth, screenWidth - 2 * cellWidth, screenHeight - 2 * cellWidth);
    painter.restore();

    {
        // draw food
        auto food = this->game->food();
        auto [sx, sy] = mapToScreen(food.x, food.y);
        painter.drawPixmap(sx, sy, QPixmap(":/res/apple.png"));
    }
    // draw title
    painter.drawText(0, 0, screenWidth, cellWidth, Qt::AlignCenter, "Snake Game");

    // draw score
    painter.drawText(0, screenHeight - 1 * cellWidth, screenWidth, cellWidth, Qt::AlignCenter, QString("Score: %1").arg(this->game->score()));

    // draw snake
    if (!isDead || showSnake) {
        auto drawHead = [&painter](int x, int y, Snake::Direction dir) {
            auto[sx, sy] = mapToScreen(x, y);
            QString picDir = "";
            // because of picture resource problem, have to adjust sx, sy
            switch (dir) {
                case Snake::UP:
                    picDir = "up";
                    break;
                case Snake::DOWN:
                    picDir = "down";
                    sy -= cellWidth;
                    break;
                case Snake::LEFT:
                    picDir = "left";
                    break;
                case Snake::RIGHT:
                    picDir = "right";
                    sx -= cellWidth;
                    break;
            }
            painter.drawPixmap(sx, sy, QPixmap(QString(":/res/head_%1.png").arg(picDir)));
        };
        this->snake->draw(drawHead, [&painter](int x, int y){
            auto[sx, sy] = mapToScreen(x, y);
            painter.drawPixmap(sx, sy, QPixmap(":/res/body.png"));
        }, [](int x, int y){});
    }
    if (isDead)
        showSnake = !showSnake;
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    if (isDead) return;
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W: {
        qDebug() << "go up";
        this->snake->changeDirection(Snake::UP);
        break;
    }
    case Qt::Key_Down:
    case Qt::Key_S: {
        qDebug() << "go down";
        this->snake->changeDirection(Snake::DOWN);
        break;
    }
    case Qt::Key_Left:
    case Qt::Key_A: {
        qDebug() << "go left";
        this->snake->changeDirection(Snake::LEFT);
        break;
    }
    case Qt::Key_Right:
    case Qt::Key_D: {
        qDebug() << "go right";
        this->snake->changeDirection(Snake::RIGHT);
        break;
    }
    }
}

bool Widget::isCollideWall()
{
    return this->game->isCollideWall(this->snake, totalWidth, totalHeight);
}

void Widget::generateFood()
{
    this->game->generateFood(totalWidth - 2, totalHeight - 2);
}

void Widget::restart() {
    isDead = false;
    showSnake = true;
    this->snake = std::make_unique<Snake>();
    this->game->restart();
}


