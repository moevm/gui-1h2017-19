#ifndef TABLEGUI_H
#define TABLEGUI_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColor>
#include <QRect>

class TableGUI : public QGraphicsScene
{
private:
    QGraphicsRectItem * table;
    QColor tableColor;

    QRect viewport;

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
};

#endif // TABLEGUI_H
