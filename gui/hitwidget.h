#ifndef HITWIDGET_H
#define HITWIDGET_H

#include <QWidget>

namespace Ui {
class HitWidget;
}

class TableGUI;

class HitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HitWidget(QWidget *parent = 0);
    ~HitWidget();

public slots:
    void setTable(TableGUI * table);

signals:
    void prevPressed();
    void nextPressed();

protected:
    void resizeEvent(QResizeEvent * event);
    void showEvent(QShowEvent * event);

private:
    Ui::HitWidget *ui;
    TableGUI * table;

    void bind();
    void configuration();
    void fitToView();
};

#endif // HITWIDGET_H
