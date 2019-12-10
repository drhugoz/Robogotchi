#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction("cutAct");
    menu.exec(event->globalPos());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setScene(Scene* input_scene) {
    ui->graphicsView->setScene(input_scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
