#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    void bind();
};

#endif // MAINWINDOW_H
