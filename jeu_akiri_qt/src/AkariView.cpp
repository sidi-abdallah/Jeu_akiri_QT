#include "include/AkariView.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "include/Matrix.h"


AkariView::AkariView(QWidget *parent) : QWidget(parent),  _matrix(*(new Matrix<char>(7)))
{
   // _matrix = Matrix<char>(7);

}

void AkariView::set_size(int size) {
    _size = size;
}

void AkariView::set_matrix(Matrix<char> & matrix) {

    _matrix = matrix;
}

void AkariView::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), Qt::lightGray);



    // main points' Coordonates
    int x_start_point = height() / 10;
    int y_start_point = height() / 10;
    int cell_width = ( 8 * x_start_point) / (_size);
    int cell_height = cell_width;
    int x_end_point = x_start_point + _size * cell_width;
    int y_end_point = y_start_point + _size * cell_height;

    // Grid Filling
    int pos_x, pos_y;
    QFont font = painter.font();
    font.setPixelSize(cell_width);
    font.setFamily("Arial");
    painter.setFont(font);
    for (int i = 0; i < _size; ++i){
        for (int j = 0; j < _size; ++j){
        pos_x = (cell_width * i) + x_start_point;
        pos_y = (cell_height * j) + y_start_point;
        switch(_matrix(i, j)){
            case '.':
                painter.fillRect(pos_y, pos_x, cell_width, cell_height, Qt::white);
            break;
            case 'X':
                painter.fillRect(pos_y, pos_x, cell_width, cell_height, Qt::black);
            break;
            case '0':
                painter.fillRect(pos_y, pos_x, cell_width, cell_height, Qt::black);
                painter.setPen(Qt::white);
                painter.drawText(QRect(pos_y, pos_x, cell_width, cell_height), Qt::AlignCenter, "0");
                painter.setPen(Qt::black);
            break;
            case '1':
                painter.fillRect(pos_y, pos_x, cell_width, cell_height, Qt::black);
                painter.setPen(Qt::white);
                painter.drawText(QRect(pos_y, pos_x, cell_width, cell_height), Qt::AlignCenter, "1");
                painter.setPen(Qt::black);
            break;
            case '2':
                painter.fillRect(pos_y, pos_x, cell_width, cell_height, Qt::black);
                painter.setPen(Qt::white);
                painter.drawText(QRect(pos_y, pos_x, cell_width, cell_height), Qt::AlignCenter, "2");
                painter.setPen(Qt::black);
            break;
            case '3':
                painter.fillRect(pos_y, pos_x, cell_width, cell_height, Qt::black);
                painter.setPen(Qt::white);
                painter.drawText(QRect(pos_y, pos_x, cell_width, cell_height), Qt::AlignCenter, "3");
                painter.setPen(Qt::black);
            break;
            case '4':
                painter.fillRect(pos_y, pos_x, cell_width, cell_height, Qt::black);
                painter.setPen(Qt::white);
                painter.drawText(QRect(pos_y, pos_x, cell_width, cell_height), Qt::AlignCenter, "4");
                painter.setPen(Qt::black);
            break;
            default:
            break;
            }
        }
    }




    // Basic grid drawing
    int x_current_start_point = x_start_point;
    int y_current_start_point = y_start_point;
    int x_current_end_point = x_end_point;
    int y_current_end_point = y_end_point;

    // Draw Lines
    for (int i = 0; i <= _size; ++i){
        painter.drawLine(x_current_start_point, y_current_start_point, x_current_end_point, y_current_start_point);
        y_current_start_point += cell_height;
    }

    // update values
    x_current_start_point = x_start_point;
    y_current_start_point = y_start_point;
    x_current_end_point = x_end_point;
    y_current_end_point = y_end_point;


    // Draw Columns

    for (int i = 0; i <= _size; ++i){
        painter.drawLine(x_current_start_point, y_current_start_point, x_current_start_point, y_current_end_point);
        x_current_start_point += cell_width;
    }

}



void AkariView::mousePressEvent(QMouseEvent *event){
    int x = event->x();
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

    qDebug() << "Cell clicked: (" << row << "," << col << ")";
}

// signal to send : connect(_AkariView, SIGNAL(AkariView::mousePressEvent(int, int)), ...)
// it is important to use SIGNAL and SLOT so that the slot could recover the values sent by the signal :) :)
