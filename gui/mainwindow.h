#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    TableGUI * table;

    void bind();
};

#endif // MAINWINDOW_H
