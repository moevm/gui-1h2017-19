#include "tablegui.h"
#include "ballgui.h"
#include "model/objects/ball.h"

#include <QDebug>

#define SCALE 500

BallGUI * TableGUI::getSelectedBall() const
{
    return selectedBall;
}

void TableGUI::setSelectedBall(BallGUI * ball)
{
    if (balls.count(ball)) {
        selectedBall = ball;
        emit selectionChanged();
    }
}

void TableGUI::updateBall(Ball * ball)
{
    for (BallGUI * gui : balls) {
//        qDebug() << "Сравниваем с шаром номер " << gui->getId();
        if (gui->getId() == ball->getId()) {
            gui->updateBall(ball);
            gui->update();
        }
    }
}

TableGUI::TableGUI(double width, double height, QColor tableColor)
    : tableColor(tableColor),
      selectedBall(nullptr)
{
    table = new QGraphicsRectItem(0, 0, width * SCALE, height * SCALE);
    setTableColor(tableColor);
    addItem(table);
    setSceneRect(table->rect());
}

double TableGUI::getTableWidth() const
{
    return table->rect().width() / SCALE;
}

void TableGUI::setTableWidth(double value)
{
    QRectF r = table->rect();
    r.setWidth(value * SCALE);
    table->setRect(r);
    setSceneRect(r);
}

double TableGUI::getTableHeight() const
{
    return table->rect().height() / SCALE;
}

void TableGUI::setTableHeight(double value)
{
    QRectF r = table->rect();
    r.setHeight(value * SCALE);
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
