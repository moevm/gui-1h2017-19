#ifndef HITWIDGET_H
#define HITWIDGET_H

#include <QWidget>

namespace Ui {
class HitWidget;
}

class HitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HitWidget(QWidget *parent = 0);
    ~HitWidget();

private:
    Ui::HitWidget *ui;
};

#endif // HITWIDGET_H
