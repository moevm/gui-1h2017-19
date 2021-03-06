#include "tablewidget.h"
#include "ui_tablewidget.h"
#include "gui/objects/tablegui.h"
#include "model/constants/constants.h"

#include <QPalette>
#include <QColorDialog>
#include <QDebug>

TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidget),
    table(nullptr)
{
    ui->setupUi(this);

    initTable();
    configure();
    bind();
}

TableWidget::~TableWidget()
{
    delete ui;
}

void TableWidget::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    ui->accel->setValue(-Constants::getAccel());

    if (table != nullptr) {
        delete table;
    }
    initTable();
    table->setAllItemsMovable(false);
    fitToView();
}

void TableWidget::configure()
{
    ui->tableColor->setAutoFillBackground(true);
    setTableColor(QColor(Qt::darkGreen));
}

void TableWidget::initTable()
{
    table = new TableGUI(ui->tableWidth->value(),
                         ui->tableHeight->value(),
                         getTableColor());
    ui->tableView->setBackgroundBrush(QBrush(QColor(Qt::lightGray)));
    ui->tableView->setScene(table);
}

void TableWidget::bind()
{
    connect(ui->nextButton, SIGNAL(clicked()),
            this, SLOT(emitTableGUI()));
    connect(ui->nextButton, SIGNAL(clicked()),
            this, SIGNAL(nextPressed()));
}

void TableWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    fitToView();
}

QColor TableWidget::getTableColor() const
{
    QPalette palette = ui->tableColor->palette();
    return palette.color(QPalette::Button);
}

void TableWidget::setTableColor(QColor color)
{
    QPalette palette = ui->tableColor->palette();
    palette.setColor(QPalette::Button, color);
    ui->tableColor->setPalette(palette);
    ui->tableColor->update();
    table->setTableColor(color);
}

void TableWidget::fitToView()
{
    ui->tableView->fitInView(table->sceneRect(), Qt::KeepAspectRatio);
}

void TableWidget::on_tableColor_clicked()
{
    QColor color = QColorDialog::getColor(getTableColor());
    if (color.isValid()) {
        setTableColor(color);
    }
}

void TableWidget::on_tableWidth_valueChanged(double value)
{
    table->setTableWidth(value);
    ui->tableView->fitInView(table->sceneRect(), Qt::KeepAspectRatio);
}

void TableWidget::on_tableHeight_valueChanged(double value)
{
    table->setTableHeight(value);
    ui->tableView->fitInView(table->sceneRect(), Qt::KeepAspectRatio);
}

void TableWidget::emitTableGUI()
{
    emit tableCreated(table);
}

void TableWidget::on_accel_valueChanged(double accel)
{
    Constants::setAccel(-accel);
}
