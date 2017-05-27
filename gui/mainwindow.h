#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PoolController;
class TableGUI;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void prevPage();
    void nextPage();
    void setTable(TableGUI * table);
    void tryAddBall(QPointF * point);

private:
    Ui::MainWindow *ui;
    TableGUI * table;
    PoolController * controller;

    void bind();
};

#endif // MAINWINDOW_H
