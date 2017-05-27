#ifndef BALLSWIDGET_H
#define BALLSWIDGET_H

#include <QWidget>
#include <QColor>

namespace Ui {
class BallsWidget;
}

class TableGUI;
class BallGUI;

class BallsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BallsWidget(QWidget *parent = 0);
    void addBall(QPointF *point);
    ~BallsWidget();

public slots:
    void setTable(TableGUI * table);

signals:
    void prevPressed();
    void nextPressed();
    void tryAddBall(QPointF * point);

protected:
    void showEvent(QShowEvent * event);
    void resizeEvent(QResizeEvent * event);

private slots:
    void on_ballColor_clicked();

private:
    Ui::BallsWidget *ui;
    TableGUI * table;
    BallGUI * currentBall;

    void configure();
    void bind();
    void fitToView();
    void enableSettings(bool enable);

    QColor getBallColor() const;
    void setBallColor(QColor color);
};

#endif // BALLSWIDGET_H
