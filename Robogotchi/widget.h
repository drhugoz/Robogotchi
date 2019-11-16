#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void setScene(QGraphicsScene* input_scene);

private:
    Ui::Widget *ui;
    QGraphicsScene* my_scene;
};

#endif // WIDGET_H
