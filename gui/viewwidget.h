#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>

namespace Ui {
class ViewWidget;
}

class Snapshot;

class TableGUI;
class Table;

class ViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = 0);
    void setHistory(std::vector<Snapshot *> history);
    ~ViewWidget();

public slots:
    void setTable(TableGUI * table);

signals:
    prevPressed();

protected:
    void resizeEvent(QResizeEvent * event);
    void showEvent(QShowEvent * event);

private slots:
    void on_eventList_doubleClicked(const QModelIndex &index);

private:
    Ui::ViewWidget *ui;
    TableGUI * table;
    Table * currentTable;
    std::vector<Snapshot *> history;

    void bind();
    void configuration();
    void fitToView();
};

#endif // VIEWWIDGET_H
