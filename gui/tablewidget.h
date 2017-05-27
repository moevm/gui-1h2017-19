#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QColor>

namespace Ui {
class TableWidget;
}

class TableGUI;

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = 0);
    ~TableWidget();

signals:
    void nextPressed();
    void tableCreated(TableGUI * table);

private slots:
    void on_tableColor_clicked();
    void on_tableWidth_valueChanged(double arg1);
    void on_tableHeight_valueChanged(double arg1);

    void emitTableGUI();

private:
    Ui::TableWidget * ui;
    TableGUI * table;

    void configure();
    void initTable();
    void bind();
    void resizeEvent(QResizeEvent *event);

    QColor getTableColor() const;
    void setTableColor(QColor color);
};

#endif // TABLEWIDGET_H
