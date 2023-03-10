#include "include/AkariView.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
//#include "include/Matrix.h"
#include "include/Grid.h"


AkariView::AkariView(QWidget *parent) : QWidget(parent)
{

    _grid = new Grid(this);
}

void AkariView::setGrid(Grid * grid) {
    _grid = grid;
}

Grid * AkariView::getGrid() {
    return _grid;
}
void AkariView::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), Qt::lightGray);
    _grid->drawGrid(&painter, height());






//    // Basic grid drawing
//    int x_current_start_point = x_start_point;
//    int y_current_start_point = y_start_point;
//    int x_current_end_point = x_end_point;
//    int y_current_end_point = y_end_point;

//    // Draw Lines
//    for (int i = 0; i <= _size; ++i){
//        painter.drawLine(x_current_start_point, y_current_start_point, x_current_end_point, y_current_start_point);
//        y_current_start_point += cell_height;
//    }

//    // update values
//    x_current_start_point = x_start_point;
//    y_current_start_point = y_start_point;
//    x_current_end_point = x_end_point;
//    y_current_end_point = y_end_point;


//    // Draw Columns

//    for (int i = 0; i <= _size; ++i){
//        painter.drawLine(x_current_start_point, y_current_start_point, x_current_start_point, y_current_end_point);
//        x_current_start_point += cell_width;
//    }

}



void AkariView::mousePressEvent(QMouseEvent *event){
    /*int x = event->x();
    int y = event->y();


    // Calculate cell coordinates
    int x_start_point = 0;
    int y_start_point = 0;
    int cell_width = ( 8 * height()) / (10 * _size);
    int cell_height = cell_width;
    int row = y / cell_height;
    int col = x / cell_width;

    if((y - y_start_point) / cell_height > _size || (y - y_start_point) / cell_height <= 0){
        row = -1;
    }

    if((x - x_start_point) / cell_width > _size || (x - x_start_point) / cell_width <= 0){
        col = -1;
    }

    // if row == -1 or j == -1, that means that the clicked position is outside the grid, otherwise, a signal is emit
    if(row != -1 && col != -1){
        emit cellClicked(row-1, col-1);
    }

    qDebug() << "Cell clicked: (" << row << "," << col << ")";*/
}

// signal to send : connect(_AkariView, SIGNAL(AkariView::mousePressEvent(int, int)), ...)
// it is important to use SIGNAL and SLOT so that the slot could recover the values sent by the signal :) :)
