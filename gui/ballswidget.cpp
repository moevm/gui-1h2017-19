#include "ballswidget.h"
#include "ui_ballswidget.h"
#include "objects/tablegui.h"

#include <QPalette>
#include <QColorDialog>

BallsWidget::BallsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BallsWidget),
    table(nullptr)
{
    ui->setupUi(this);
    ui->tableView->setParentWidget(this);

    configure();
    bind();
}

void BallsWidget::addBall(QPointF * point)
{
    emit tryAddBall(point);
}

BallsWidget::~BallsWidget()
{
    delete ui;
}

void BallsWidget::setTable(TableGUI * table)
{
    this->table = table;
    ui->tableView->setScene(table);
    fitToView();
}

void BallsWidget::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    fitToView();
}

void BallsWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    fitToView();
}

void BallsWidget::configure()
{
    ui->ballColor->setAutoFillBackground(true);
    setBallColor(QColor(Qt::gray));
    ui->tableView->setBackgroundBrush(QBrush(QColor(Qt::lightGray)));
}

void BallsWidget::bind()
{
    connect(ui->prevButton, SIGNAL(clicked()),
            this, SIGNAL(prevPressed()));
    connect(ui->nextButton, SIGNAL(clicked()),
            this, SIGNAL(nextPressed()));
}

void BallsWidget::fitToView()
{
    if (table != nullptr) {
        ui->tableView->fitInView(table->sceneRect(), Qt::KeepAspectRatio);
    }
}

QColor BallsWidget::getBallColor() const
{
    QPalette palette = ui->ballColor->palette();
    return palette.color(QPalette::Button);
}

void BallsWidget::setBallColor(QColor color)
{
    QPalette palette = ui->ballColor->palette();
    palette.setColor(QPalette::Button, color);
    ui->ballColor->setPalette(palette);
    ui->ballColor->update();
}

void BallsWidget::on_ballColor_clicked()
{
    QColor color = QColorDialog::getColor(getBallColor());
    if (color.isValid()) {
        setBallColor(color);
    }
}
