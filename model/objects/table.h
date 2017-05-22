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

    double getWidth() const;
    double getHeight() const;

    bool addBall(Ball * ball);

    bool hasMoving() const;

    double shortestTimeToStop() const;

    ~Table();
};

#endif // TABLE_H
