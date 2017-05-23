#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>

namespace Ui {
class ViewWidget;
}

class ViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = 0);
    ~ViewWidget();

signals:
    prevPressed();

private:
    Ui::ViewWidget *ui;

    void bind();
};

#endif // VIEWWIDGET_H
