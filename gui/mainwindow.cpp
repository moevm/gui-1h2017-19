#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "objects/tablegui.h"
#include "objects/ballgui.h"
#include "model/poolcontroller.h"
#include "model/objects/ball.h"
#include "model/objects/doublevector2d.h"
#include "model/objects/table.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    table(nullptr),
    controller(new PoolController)
{
    ui->setupUi(this);

    bind();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::prevPage()
{
    int count = ui->stackedWidget->count();
    int index = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex((index - 1) % count);
}

void MainWindow::nextPage()
{
    int count = ui->stackedWidget->count();
    int index = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex((index + 1) % count);
}

void MainWindow::setTable(TableGUI * table)
{
    this->table = table;
    controller->setTable(new Table(table->getTableWidth(),
                                   table->getTableHeight()));
}

void MainWindow::tryAddBall(QPointF * point)
{
    double x = point->x();
    double y = point->y();

    DoubleVector2D position;
    position.setX(x);
    position.setY(y);
    Ball * ball = new Ball(position);

    if (controller->addBall(ball)) {
        BallGUI * ballGUI = new BallGUI(ball);
        if (table != nullptr) {
            table->addItem(ballGUI);
        }
    } else {
        delete ball;
    }
}

void MainWindow::bind()
{
    connect(ui->tablePage, SIGNAL(nextPressed()),
            this, SLOT(nextPage()));
    connect(ui->ballsPage, SIGNAL(prevPressed()),
            this, SLOT(prevPage()));
    connect(ui->ballsPage, SIGNAL(nextPressed()),
            this, SLOT(nextPage()));
    connect(ui->hitPage, SIGNAL(prevPressed()),
            this, SLOT(prevPage()));
    connect(ui->hitPage, SIGNAL(nextPressed()),
            this, SLOT(nextPage()));
    connect(ui->viewPage, SIGNAL(prevPressed()),
            this, SLOT(prevPage()));

    connect(ui->tablePage, SIGNAL(tableCreated(TableGUI*)),
            this, SLOT(setTable(TableGUI*)));
    connect(ui->tablePage, SIGNAL(tableCreated(TableGUI*)),
            ui->hitPage, SLOT(setTable(TableGUI*)));
    connect(ui->tablePage, SIGNAL(tableCreated(TableGUI*)),
            ui->viewPage, SLOT(setTable(TableGUI*)));
    connect(ui->tablePage, SIGNAL(tableCreated(TableGUI*)),
            ui->ballsPage, SLOT(setTable(TableGUI*)));

    connect(ui->ballsPage, SIGNAL(tryAddBall(QPointF*)),
            this, SLOT(tryAddBall(QPointF*)));
}
