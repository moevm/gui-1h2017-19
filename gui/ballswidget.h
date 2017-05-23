#ifndef BALLSWIDGET_H
#define BALLSWIDGET_H

#include <QWidget>

namespace Ui {
class BallsWidget;
}

class BallsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BallsWidget(QWidget *parent = 0);
    ~BallsWidget();

signals:
    void prevPressed();
    void nextPressed();

private:
    Ui::BallsWidget *ui;

    void bind();
};

#endif // BALLSWIDGET_H
