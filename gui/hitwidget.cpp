#include "hitwidget.h"
#include "ui_hitwidget.h"

HitWidget::HitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HitWidget)
{
    ui->setupUi(this);

    bind();
}

HitWidget::~HitWidget()
{
    delete ui;
}

void HitWidget::bind()
{
    connect(ui->prevButton, SIGNAL(clicked()),
            this, SIGNAL(prevPressed()));
    connect(ui->nextButton, SIGNAL(clicked()),
            this, SIGNAL(nextPressed()));
}
