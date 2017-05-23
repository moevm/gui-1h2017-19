#include "ballswidget.h"
#include "ui_ballswidget.h"

BallsWidget::BallsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BallsWidget)
{
    ui->setupUi(this);

    bind();
}

BallsWidget::~BallsWidget()
{
    delete ui;
}

void BallsWidget::bind()
{
    connect(ui->prevButton, SIGNAL(clicked()),
            this, SIGNAL(prevPressed()));
    connect(ui->nextButton, SIGNAL(clicked()),
            this, SIGNAL(nextPressed()));
}
