#include "viewwidget.h"
#include "ui_viewwidget.h"
#include "objects/tablegui.h"
#include "model/objects/snapshot.h"
#include "model/objects/table.h"
#include "model/objects/ball.h"

#include <QDebug>

#define TIMEDIFF 10.0

ViewWidget::ViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewWidget),
    table(nullptr),
    currentTable(nullptr),
    timer(new QTimer(this))
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
    setSnapshot(0);
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
    currentTime = 0;
}

void ViewWidget::bind()
{
    connect(ui->prevButton, SIGNAL(clicked()),
            this, SIGNAL(prevPressed()));
    connect(ui->prevButton, SIGNAL(clicked()),
            timer, SLOT(stop()));
    connect(timer, SIGNAL(timeout()),
            this, SLOT(timeout()));
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

void ViewWidget::setSnapshot(size_t index)
{
    Snapshot * snapshot = history[index];
    if (currentTable != nullptr) {
        delete currentTable;
    }
    currentTable = new Table(*snapshot->getTable());
    updateTable();
    currentTime = snapshot->getTimestamp();
    currentHistoryIndex = index;
}

void ViewWidget::updateTable()
{
    for (Ball * ball : currentTable->getBalls()) {
        table->updateBall(ball);
    };
}

void ViewWidget::on_eventList_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    setSnapshot(row);
}

void ViewWidget::timeout()
{
#define MS_IN_SEC 2000.0
    if (currentTime >= history.back()->getTimestamp()) {
        setSnapshot(history.size() - 1);
        timer->stop();
        return;
    }

    currentTime += TIMEDIFF / MS_IN_SEC;
//    qDebug() << "Before: " << currentTime << " " << history[currentHistoryIndex]->getTimestamp();
    if (currentTime >= history[currentHistoryIndex + 1]->getTimestamp()) {
        double time = currentTime;
        currentHistoryIndex += 1;
//        if (currentHistoryIndex >= history.size()) {
//            setSnapshot(history.size() - 1);
//            timer->stop();
//            return;
//        }
        setSnapshot(currentHistoryIndex);
        currentTable->goToNextStep(time - currentTime);
        currentTime = time;
    } else {
        currentTable->goToNextStep(TIMEDIFF / MS_IN_SEC);
    }
    updateTable();
//    qDebug() << "After: " << currentTime << " " << history[currentHistoryIndex]->getTimestamp();
}

void ViewWidget::on_playButton_clicked()
{
    timer->start(TIMEDIFF);
}

void ViewWidget::on_pauseButton_clicked()
{
    timer->stop();
}

void ViewWidget::on_stopButton_clicked()
{
    timer->stop();
    setSnapshot(0);
}
