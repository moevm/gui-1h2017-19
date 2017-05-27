#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>

namespace Ui {
class ViewWidget;
}

class TableGUI;

class ViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = 0);
    ~ViewWidget();

public slots:
    void setTable(TableGUI * table);

signals:
    prevPressed();

protected:
    void resizeEvent(QResizeEvent * event);
    void showEvent(QShowEvent * event);

private:
    Ui::ViewWidget *ui;
    TableGUI * table;

    void bind();
    void configuration();
    void fitToView();
};

#endif // VIEWWIDGET_H
