#ifndef TABLEGUI_H
#define TABLEGUI_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColor>
#include <set>

class BallGUI;
class Ball;

class TableGUI : public QGraphicsScene
{
private:
    QGraphicsRectItem * table;
    QColor tableColor;
    std::set<BallGUI *> balls;
    BallGUI * selectedBall;

public:
    TableGUI(double width,
             double height,
             QColor tableColor);

    double getTableWidth() const;
    void setTableWidth(double value);
    double getTableHeight() const;
    void setTableHeight(double value);
    QColor getTableColor() const;
    void setTableColor(const QColor & value);

    void setAllItemsMovable(bool movable);
    void addBall(BallGUI * ball);
    BallGUI * getSelectedBall() const;
    void setSelectedBall(BallGUI * ball);

    void updateBall(Ball * ball);
};

#endif // TABLEGUI_H
