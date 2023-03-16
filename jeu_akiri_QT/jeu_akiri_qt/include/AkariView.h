#ifndef AKARIVIEW_H
#define AKARIVIEW_H

#include <QWidget>
#include"common.h"
#include "include/Matrix.h"
#include <QTimer>
#include <QTime>

class QLabel;
class Grid;
class AkariView : public QWidget
{
    Q_OBJECT
public:
    explicit AkariView(QWidget *parent = nullptr);
    void setGrid(Grid * grid);
    Grid * getGrid();
    virtual void paintEvent(QPaintEvent *event) override;

    // begin timer methods
    QTime get_duration();
    QTimer * get_timer();
    void set_duration(QTime duration);
    void set_timer(QTimer * timer);
    RoundDuration get_round_duration();
    void set_round_duration(int roundDuration);

    void set_timerLabel(QLabel * timerLabel);

    // void timer_alert(bool is_alert_font);
    // end timer functions


private:
    Grid * _grid;

    QTime _duration;
    QTimer * _timer;
    RoundDuration _roundDuration;
    QLabel * _timerLabel;


public slots :
     void OncellClicked(int row, int col);
     void mousePressEvent(QMouseEvent *event) override;
     virtual void updateTimer();
     virtual void restartTimer();
     virtual void stopTimer();

signals:
    void cellClicked(int row, int col);
};

#endif // AkariView_H
