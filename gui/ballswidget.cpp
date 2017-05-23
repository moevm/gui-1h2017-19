#include "ballswidget.h"
#include "ui_ballswidget.h"

#include <QPalette>
#include <QColorDialog>

BallsWidget::BallsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BallsWidget)
{
    ui->setupUi(this);

    configure();
    bind();
}

BallsWidget::~BallsWidget()
{
    delete ui;
}

void BallsWidget::configure()
{
    ui->ballColor->setAutoFillBackground(true);
    setBallColor(QColor(Qt::gray));
}

void BallsWidget::bind()
{
    connect(ui->prevButton, SIGNAL(clicked()),
            this, SIGNAL(prevPressed()));
    connect(ui->nextButton, SIGNAL(clicked()),
            this, SIGNAL(nextPressed()));
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
