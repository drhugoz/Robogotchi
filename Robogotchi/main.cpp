#include "widget.h"
#include "controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controller contr;
    contr.w->show();

    return a.exec();
}
