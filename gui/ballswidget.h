#ifndef BALLSWIDGET_H
#define BALLSWIDGET_H

#include <QWidget>
#include <QColor>

namespace Ui {
class BallsWidget;
}

class TableGUI;

class BallsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BallsWidget(QWidget *parent = 0);
    ~BallsWidget();

public slots:
    void setTable(TableGUI * table);

signals:
    void prevPressed();
    void nextPressed();

protected:
    void showEvent(QShowEvent * event);
    void resizeEvent(QResizeEvent * event);

private slots:
    void on_ballColor_clicked();

private:
    Ui::BallsWidget *ui;
    TableGUI * table;

    void configure();
    void bind();
    void fitToView();

    QColor getBallColor() const;
    void setBallColor(QColor color);
};

#endif // BALLSWIDGET_H
