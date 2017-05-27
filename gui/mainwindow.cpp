#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "objects/tablegui.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
}
