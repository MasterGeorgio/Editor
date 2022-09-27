#include "txteditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TxtEditor w;
    w.show();
    return a.exec();
}
