#include "viewwidget.h"
#include "ui_viewwidget.h"
#include "objects/tablegui.h"
#include "model/objects/snapshot.h"
#include "model/objects/table.h"
#include "model/objects/ball.h"

#include <QDebug>

ViewWidget::ViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewWidget),
    table(nullptr),
    currentTable(nullptr)
{
    ui->setupUi(this);

    bind();
    configuration();
}

void ViewWidget::setHistory(std::vector<Snapshot *> history)
{
    ui->eventList->clear();
    std::for_each(history.begin(),
                  history.end(),
                  [&](Snapshot * snapshot) {
        ui->eventList->addItem(QString::fromStdString(snapshot->getName()) +
                               " " + QString::number(snapshot->getTimestamp()));
    });
    this->history = history;
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
    if (table != nullptr) {
        table->setAllItemsMovable(false);
    }
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

void ViewWidget::on_eventList_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    Snapshot * snapshot = history[row];
    if (currentTable != nullptr) {
        delete currentTable;
    }
    currentTable = new Table(*snapshot->getTable());
    for (Ball * ball : currentTable->getBalls()) {
        qDebug() << "Обновление шара номер " << ball->getId();
        table->updateBall(ball);
    };
}
