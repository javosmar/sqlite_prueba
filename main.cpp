#include "mainwindowsql.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowsql w;
    w.show();

    return a.exec();
}
