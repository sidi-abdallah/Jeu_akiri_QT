#include "include/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    //srand(time(NULL));
    //qsrand(NULL);


    w.show();
    return a.exec();
}
