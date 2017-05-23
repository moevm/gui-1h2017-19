#include "ballswidget.h"
#include "ui_ballswidget.h"

BallsWidget::BallsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BallsWidget)
{
    ui->setupUi(this);
}

BallsWidget::~BallsWidget()
{
    delete ui;
}
