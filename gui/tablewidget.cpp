#include "tablewidget.h"
#include "ui_tablewidget.h"

#include <QPalette>
#include <QColorDialog>

TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidget)
{
    ui->setupUi(this);

    configure();
    bind();
}

TableWidget::~TableWidget()
{
    delete ui;
}

void TableWidget::configure()
{
    ui->tableColor->setAutoFillBackground(true);
    setTableColor(QColor(Qt::darkGreen));
}

void TableWidget::bind()
{
    connect(ui->nextButton, SIGNAL(clicked()),
            this, SIGNAL(nextPressed()));
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
}

void TableWidget::on_tableColor_clicked()
{
    QColor color = QColorDialog::getColor(getTableColor());
    if (color.isValid()) {
        setTableColor(color);
    }
}
