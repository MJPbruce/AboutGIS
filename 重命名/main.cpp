#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myWidget w;
    w.setWindowTitle("图像剔除系统");
    w.show();

    return a.exec();
}
