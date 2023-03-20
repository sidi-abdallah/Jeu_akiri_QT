#include "include/mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QFile>
#include<QFileInfo>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QStringList languages = QLocale().uiLanguages(); // e.g. ("en-US")
    if (languages.size()) {
        QString language = languages.front().split("-").front(); // -> "en"
        QString qmFile = QString(":/jeu_akiri_qt_en_FR.qm").arg(language);
        if (QFileInfo(qmFile).exists()) {
            QTranslator * translator = new QTranslator(&app);
            if (translator->load(qmFile)) {
                app.installTranslator(translator);
            } else {
                translator->deleteLater();
            }
            // Translate Qt strings (e.g. in predefined dialogs)
            translator = new QTranslator(&app);
            if (translator->load(QString("qt_%1").arg(language),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
                app.installTranslator(translator);
            } else {
             translator->deleteLater();
            }
        }
    }
    MainWindow w;

    w.setWindowTitle(QObject::tr("Akari Game"));
    w.setWindowIcon(QIcon(":/icons/akarigame.png"));
    w.setStyleSheet("background-color: #29C8D2 ;"); // rgb(37, 150, 190)
    QPoint position = QSettings().value("Config/WindowPosition", QPoint(0, 0)).toPoint();
    w.move(position);


    w.show();
    return app.exec();
}
