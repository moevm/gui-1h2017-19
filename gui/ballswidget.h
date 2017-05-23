#ifndef BALLSWIDGET_H
#define BALLSWIDGET_H

#include <QWidget>
#include <QColor>

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

private slots:
    void on_ballColor_clicked();

private:
    Ui::BallsWidget *ui;

    void configure();
    void bind();

    QColor getBallColor() const;
    void setBallColor(QColor color);
};

#endif // BALLSWIDGET_H
