#include "viewwidget.h"
#include "ui_viewwidget.h"
#include "objects/tablegui.h"

ViewWidget::ViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewWidget),
    table(nullptr)
{
    ui->setupUi(this);

    bind();
    configuration();
}

ViewWidget::~ViewWidget()
{
    delete ui;
}

void ViewWidget::setTable(TableGUI * table)
{
    this->table = table;
    ui->tableView->setScene(table);
    fitToView();
}

void ViewWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    fitToView();
}

void ViewWidget::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    fitToView();
}

void ViewWidget::bind()
{
    connect(ui->prevButton, SIGNAL(clicked()),
            this, SIGNAL(prevPressed()));
}

void ViewWidget::configuration()
{
    ui->tableView->setBackgroundBrush(QBrush(QColor(Qt::lightGray)));
}

void ViewWidget::fitToView()
{
    if (table != nullptr) {
        ui->tableView->fitInView(table->sceneRect(), Qt::KeepAspectRatio);
    }
}
