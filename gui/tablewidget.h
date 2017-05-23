#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QColor>

namespace Ui {
class TableWidget;
}

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = 0);
    ~TableWidget();

signals:
    void nextPressed();

private slots:
    void on_tableColor_clicked();

private:
    Ui::TableWidget *ui;

    void configure();
    void bind();

    QColor getTableColor() const;
    void setTableColor(QColor color);
};

#endif // TABLEWIDGET_H
