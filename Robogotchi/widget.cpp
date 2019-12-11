#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

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

void Widget::on_infoButton_clicked()
{
    QMessageBox::information(
        this,
        tr("Robogotchi"),
        tr("\tУправление.\n"
           "Стрелки клавиатуры - поворот модели\n"
           "Q, W - поднять/опустить руки\n"
           "A, S - поднять/опустить ноги\n"
           "H - крутить голову\n"
           "цифры 0-9 - поменять цвет света\n"
           "'+','-' - увеличить/уменьшить интенсивность света\n"
           "L -  поменять расположение света\n"
           "T - включить/отключить отрисовку теней"));
}
