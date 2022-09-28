#include "bubbles.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bubbles w;
    w.show();
    return a.exec();
}
