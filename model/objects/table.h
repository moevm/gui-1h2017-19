#ifndef TABLE_H
#define TABLE_H

#include <set>

class Ball;

class Table
{
private:
    double const width;
    double const height;

    std::set<Ball *> balls;

public:
    Table(double width,
          double height);

    Table(Table const & table);

    /**
     * @brief getWidth
     * @return ширину стола (ширина стола располагается вдоль оси ox)
     */
    double getWidth() const;
    /**
     * @brief getHeight
     * @return высоту стола (высота стола располагается вдоль оси oy)
     */
    double getHeight() const;

    bool addBall(Ball * ball);

    bool hasMoving() const;

    double shortestTimeToStop() const;
    double shortestTimeToWall() const;

    ~Table();
};

#endif // TABLE_H
