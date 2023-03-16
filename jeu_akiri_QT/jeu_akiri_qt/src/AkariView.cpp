#include "include/AkariView.h"
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
//#include "include/Matrix.h"
#include "include/Grid.h"
#include <QGridLayout>
#include <QTimer>
#include <QLabel>
#include <QTime>


AkariView::AkariView(QWidget *parent) : QWidget(parent)
{

    _grid = new Grid(this);

    _duration = QTime(0, 0, 0);
    _timer = new QTimer(this);
    _timer->start(1000);
     connect(_grid, SIGNAL(notify()), this,SLOT(update()));
     connect(_timer, &QTimer::timeout, this, &AkariView::updateTimer);


}

void AkariView::setGrid(Grid * grid) {
    _grid = grid;
}

Grid * AkariView::getGrid() {
    return _grid;
}

void AkariView::set_timerLabel(QLabel * timerLabel) {
    _timerLabel = timerLabel;
}

void AkariView::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), Qt::lightGray);

    _grid->drawGrid(&painter, height());

}

void AkariView::OncellClicked(int row, int col) {
    emit cellClicked(row, col);
}


void AkariView::mousePressEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();
    const int pos_x_at_grid = pos.x() -  (height() / 10);
    const int pos_y_at_grid = pos.y() -  (height() / 10);

    if(pos_x_at_grid < 0 || pos_x_at_grid > (_grid->getSize() * _grid->getCellWidth()) || pos_y_at_grid < 0 || pos_y_at_grid > (_grid->getSize() * _grid->getCellWidth())) {
        return;
    }
    const int row = pos_y_at_grid / _grid->getCellWidth();
    const int col = pos_x_at_grid / _grid->getCellWidth();
    emit cellClicked(row, col);
}

void AkariView::set_round_duration(int roundDuration){
    _roundDuration = static_cast<RoundDuration>(roundDuration);
}

void AkariView::updateTimer(){
    QString alert_timer_stylesheet = "QLabel { color : white; background-color : red; border : 2px solid black; border-radius : 10px;}";
    QString normal_timer_stylesheet = "QLabel { color : black; background-color : yellow; border : 2px solid white; border-radius : 10px;}";
    QFont alert_timer_font = *new QFont("Arial", 18);
    QFont normal_timer_font = *new QFont("Arial", 15);


    _timerLabel->setStyleSheet(normal_timer_stylesheet);
   static bool is_alert_font = false;
   QFont current_font = is_alert_font ? alert_timer_font : normal_timer_font;
   _timerLabel->setFont(normal_timer_font);

   _duration = _duration.addSecs(1);
   _timerLabel->setText(_duration.toString("HH:mm:ss"));
   switch(_roundDuration){
       case 1: // 10 Minutes
           if(_duration.hour() == 0 && _duration.minute() == 9 && _duration.second() >= 0){
               is_alert_font = !is_alert_font; // basculer l'état actuel de la police
               QFont new_font = is_alert_font ? alert_timer_font : normal_timer_font;
               _timerLabel->setFont(new_font);
               _timerLabel->setStyleSheet(alert_timer_stylesheet);
           }
           if(_duration.hour() == 0 && _duration.minute() == 10 && _duration.second() == 0){
              _timer->stop();
               // il faut desactiver la grille
           }
       break;

       case 2: // 5 Minutes
          if(_duration.hour() == 0 && _duration.minute() == 4 && _duration.second() >= 20){
              is_alert_font = !is_alert_font; // basculer l'état actuel de la police
              QFont new_font = is_alert_font ? alert_timer_font : normal_timer_font;
              _timerLabel->setFont(new_font);
              _timerLabel->setStyleSheet(alert_timer_stylesheet);
          }
          if(_duration.hour() == 0 && _duration.minute() == 5 && _duration.second() == 0){
             _timer->stop();
              // il faut desactiver la grille
          }
          break;
       case 3: // 3 Minutes
          if(_duration.hour() == 0 && _duration.minute() == 2 && _duration.second() >= 40){
              is_alert_font = !is_alert_font; // basculer l'état actuel de la police
              QFont new_font = is_alert_font ? alert_timer_font : normal_timer_font;
              _timerLabel->setFont(new_font);
              _timerLabel->setStyleSheet(alert_timer_stylesheet);
          }
          if(_duration.hour() == 0 && _duration.minute() == 3 && _duration.second() == 0){
             _timer->stop();
              // il faut desactiver la grille
          }
          break;

       case 4: // 1 Minute
           if(_duration.hour() == 0 && _duration.minute() == 0 && _duration.second() >= 4){
               _timerLabel->setStyleSheet(alert_timer_stylesheet);
               is_alert_font = !is_alert_font; // basculer l'état actuel de la police
               QFont new_font = is_alert_font ? alert_timer_font : normal_timer_font;
               _timerLabel->setFont(new_font);

           }
           if(_duration.hour() == 0 && _duration.minute() == 1 && _duration.second() == 0){
              _timer->stop();
               // il faut desactiver la grille
           }
         break;
    default: // Unlimited time mode
        break;

}

}

void AkariView::restartTimer(){
    _duration = QTime(0, 0, 0);
    _timerLabel->setText(_duration.toString("HH:mm:ss"));
   _timer->start(1000);
}

void AkariView::stopTimer(){
   _timer->stop();
}



