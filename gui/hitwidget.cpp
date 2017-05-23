#include "hitwidget.h"
#include "ui_hitwidget.h"

HitWidget::HitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HitWidget)
{
    ui->setupUi(this);
}

HitWidget::~HitWidget()
{
    delete ui;
}
