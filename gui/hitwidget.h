#ifndef HITWIDGET_H
#define HITWIDGET_H

#include <QWidget>

namespace Ui {
class HitWidget;
}

class TableGUI;
class BallGUI;

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

private slots:
    void setCurrentBall();

    void on_angle_valueChanged(int value);

    void on_speed_valueChanged(int value);

private:
    Ui::HitWidget *ui;
    TableGUI * table;
    BallGUI * selectedBall;

    void bind();
    void configuration();
    void fitToView();
    void enableWidgets(bool enable);
};

#endif // HITWIDGET_H
