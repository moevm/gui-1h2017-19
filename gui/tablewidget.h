#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>

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

private:
    Ui::TableWidget *ui;

    void bind();
};

#endif // TABLEWIDGET_H
