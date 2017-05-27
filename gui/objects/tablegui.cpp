#include "tablegui.h"
#include "ballgui.h"

#include <QDebug>

TableGUI::TableGUI(double width, double height, QColor tableColor)
    : tableColor(tableColor)
{
    table = new QGraphicsRectItem(0, 0, width * 100, height * 100);
    setTableColor(tableColor);
    addItem(table);
    setSceneRect(table->rect());
}

double TableGUI::getTableWidth() const
{
    return table->rect().width() / 100;
}

void TableGUI::setTableWidth(double value)
{
    QRectF r = table->rect();
    r.setWidth(value * 100);
    table->setRect(r);
    setSceneRect(r);
}

double TableGUI::getTableHeight() const
{
    return table->rect().height() / 100;
}

void TableGUI::setTableHeight(double value)
{
    QRectF r = table->rect();
    r.setHeight(value * 100);
    table->setRect(r);
    setSceneRect(r);
}

QColor TableGUI::getTableColor() const
{
    return tableColor;
}

void TableGUI::setTableColor(const QColor & value)
{
    tableColor = value;
    table->setBrush(tableColor);
}

void TableGUI::setAllItemsMovable(bool movable)
{
    std::for_each(balls.begin(),
                  balls.end(),
                  [=](BallGUI * ball) {
        ball->setFlag(QGraphicsItem::ItemIsMovable, movable);
    });
}

void TableGUI::addBall(BallGUI * ball)
{
    if (!balls.count(ball)) {
        balls.insert(ball);
    }
    addItem(ball);
}
