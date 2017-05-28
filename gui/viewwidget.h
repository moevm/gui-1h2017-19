#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include <QTimer>

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
    void prevPressed();

protected:
    void resizeEvent(QResizeEvent * event);
    void showEvent(QShowEvent * event);

private slots:
    void on_eventList_doubleClicked(const QModelIndex &index);
    void timeout();

    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::ViewWidget *ui;
    TableGUI * table;
    Table * currentTable;
    std::vector<Snapshot *> history;
    QTimer * timer;
    double currentTime;
    int currentHistoryIndex;

    void bind();
    void configuration();
    void fitToView();
    void setSnapshot(int index);
    void updateTable();
};

#endif // VIEWWIDGET_H
