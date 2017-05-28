#include "hitwidget.h"
#include "ui_hitwidget.h"
#include "objects/tablegui.h"
#include "objects/ballgui.h"
#include "model/objects/ball.h"

#define PI 3.14159265359

HitWidget::HitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HitWidget),
    table(nullptr),
    selectedBall(nullptr)
{
    ui->setupUi(this);

    bind();
    configuration();
}

HitWidget::~HitWidget()
{
    delete ui;
}

void HitWidget::setTable(TableGUI * table)
{
    this->table = table;
    if (this->table != nullptr) {
        connect(this->table, SIGNAL(selectionChanged()),
                this, SLOT(setCurrentBall()));
    }
    selectedBall = table->getSelectedBall();
    ui->tableView->setScene(table);
    fitToView();
}

void HitWidget::bind()
{
    connect(ui->prevButton, SIGNAL(clicked()),
            this, SIGNAL(prevPressed()));
    connect(ui->nextButton, SIGNAL(clicked()),
            this, SIGNAL(nextPressed()));
}

void HitWidget::configuration()
{
    ui->tableView->setBackgroundBrush(QBrush(QColor(Qt::lightGray)));
}

void HitWidget::fitToView()
{
    if (table != nullptr) {
        table->update();
        ui->tableView->fitInView(table->sceneRect(), Qt::KeepAspectRatio);
    }
}

void HitWidget::enableWidgets(bool enable)
{
    ui->angle->setEnabled(enable);
    ui->angleLabel->setEnabled(enable);
    ui->angleMainLabel->setEnabled(enable);
    ui->angleResultLabel->setEnabled(enable);
    ui->speed->setEnabled(enable);
    ui->speedLabel->setEnabled(enable);
    ui->speedMainLabel->setEnabled(enable);
    ui->speedResultLabel->setEnabled(enable);
}

void HitWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    fitToView();
}

void HitWidget::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    if (selectedBall == nullptr) {
        enableWidgets(false);
    }
    if (table != nullptr) {
        table->setAllItemsMovable(false);
    }
    fitToView();
}

void HitWidget::setCurrentBall()
{
    selectedBall = table->getSelectedBall();
    if (selectedBall != nullptr) {
        enableWidgets(true);
        Ball * ball = selectedBall->getBall();
        ui->speed->setValue(ball->getSpeed().getSize() * 100.0);
        ui->angle->setValue(ball->getSpeed().getAngle() / PI * 180.0);
    }
}

void HitWidget::on_angle_valueChanged(int value)
{
    if (selectedBall != nullptr) {
        double rads = value / 180.0 * PI;
        DoubleVector2D ballSpeed = selectedBall->getBall()->getSpeed();
        ballSpeed.setAngle(rads);
        selectedBall->getBall()->setSpeed(ballSpeed);
        ui->angleResultLabel->setText(QString::number(value) + "°");
        selectedBall->update();
    }
}

void HitWidget::on_speed_valueChanged(int value)
{
    if (selectedBall != nullptr) {
        double speed = value / 100.0;
        DoubleVector2D ballSpeed = selectedBall->getBall()->getSpeed();
        ballSpeed.setSize(speed);
        selectedBall->getBall()->setSpeed(ballSpeed);
        ui->speedResultLabel->setText(QString::number(speed) + " м/с");
        selectedBall->update();
    }
}
