#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QTimer>
#include <QTime>

class AkariModel;
class AkariView;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow * ui;
    AkariModel * _model;
    const QString digitalFontFamily = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/digital_font/DS-DIGI.TTF")).at(0);

    enum RoundDuration{
        unlimited = 0,
        ten_minutes,
        five_minutes,
        three_minutes,
        one_minute
    };

    QTime _duration;
    QTimer * _timer;
    RoundDuration _roundDuration;

    void init();

protected:
    void closeEvent(QCloseEvent *);

protected slots :
    /**
     * @brief updateView update all the viewWidget values from the model one when they changed
     */
    virtual void updateView();
    virtual void onDoneClicked(bool);
    virtual void onRestartClicked();
    virtual void printWindow();


private slots :
    virtual void updateTimer();
    virtual void restartTimer();
    virtual void stopTimer();

    virtual void set_round_duration(int roundDuration);

signals :
    /**
     * @brief notify sent to update of the viewWidget to launch QPainter again
     */
    void notify();
    void timer_done();
};
#endif // MAINWINDOW_H
