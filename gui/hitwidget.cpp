#include "hitwidget.h"
#include "ui_hitwidget.h"
#include "objects/tablegui.h"

HitWidget::HitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HitWidget),
    table(nullptr)
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

void HitWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    fitToView();
}

void HitWidget::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    if (table != nullptr) {
        table->setAllItemsMovable(false);
    }
    fitToView();
}
