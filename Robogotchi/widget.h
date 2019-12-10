#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <scene.h>
#include <QMenu>
#include <QMenuBar>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void setScene(Scene* input_scene);
    void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
