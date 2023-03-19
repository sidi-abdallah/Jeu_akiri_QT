#include "include/mainwindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Akari Game");
    w.setWindowIcon(QIcon(":/icons/akarigame.png"));
    w.setStyleSheet("background-color: rgb(37, 150, 190);");
    QPoint position = QSettings().value("Config/WindowPosition", QPoint(0, 0)).toPoint();
    w.move(position);
//    QVariant savedSize = QSettings().value("Config/AkariSize", 0);
//    AkariModel * model = w.get_model();

    w.show();
    return a.exec();
}
