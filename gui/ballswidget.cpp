#include "ballswidget.h"
#include "ui_ballswidget.h"
#include "objects/tablegui.h"
#include "objects/ballgui.h"

#include <QPalette>
#include <QColorDialog>

BallsWidget::BallsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BallsWidget),
    table(nullptr),
    currentBall(nullptr)
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
    connect(this->table, SIGNAL(selectionChanged()),
            SLOT(setCurrentBall()));
    ui->tableView->setScene(table);
    fitToView();
}

void BallsWidget::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    if (table != nullptr) {
        table->setAllItemsMovable(true);
    }
    enableSettings(currentBall != nullptr);
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

void BallsWidget::enableSettings(bool enable)
{
    ui->ballColor->setEnabled(enable);
    ui->ballColorLabel->setEnabled(enable);
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
    if (currentBall != nullptr) {
        currentBall->setBrush(QBrush(color));
    }
    ui->ballColor->update();
}

void BallsWidget::on_ballColor_clicked()
{
    QColor color = QColorDialog::getColor(getBallColor());
    if (color.isValid()) {
        setBallColor(color);
    }
}

void BallsWidget::setCurrentBall()
{
    currentBall = table->getSelectedBall();
    if (currentBall != nullptr) {
        enableSettings(true);
        QColor color = currentBall->brush().color();
        setBallColor(color);
    }
}
