#include "include/Cell.h"
#include <QMouseEvent>
//#include "include/AkariView.h"



Cell::Cell(QWidget *parent)
    : QWidget(parent)
{

}



Cell::~Cell() {

}


cellState Cell::getCellState(){
    return _cellState;
}



void Cell::setCellState(cellState cellState){
    _cellState = cellState;
}

void Cell::drawCell(QPainter * _painter, int cellWidth, int pos_x, int pos_y, bool isgreen){
    QImage yellow_light(":/lights/lights/light.png");
    QImage red_light(":/lights/lights/red_light.png");

    switch(this->getCellState()){
        case BLACK:
            _painter->fillRect(pos_y, pos_x, cellWidth, cellWidth, Qt::black);

        break;
        case BLACK_0:
            _painter->fillRect(pos_y, pos_x, cellWidth, cellWidth, Qt::black);
            _painter->setPen(Qt::white);
            _painter->drawText(QRect(pos_y, pos_x, cellWidth, cellWidth), Qt::AlignCenter, "0");
            _painter->setPen(Qt::black);
        break;
        case BLACK_1:
            _painter->fillRect(pos_y, pos_x, cellWidth, cellWidth, Qt::black);
             isgreen ? _painter->setPen(Qt::green) : _painter->setPen(Qt::white);
            _painter->drawText(QRect(pos_y, pos_x, cellWidth, cellWidth), Qt::AlignCenter, "1");
            _painter->setPen(Qt::black);
        break;
        case BLACK_2:
            _painter->fillRect(pos_y, pos_x, cellWidth, cellWidth, Qt::black);
            isgreen ? _painter->setPen(Qt::green) : _painter->setPen(Qt::white);
            _painter->drawText(QRect(pos_y, pos_x, cellWidth, cellWidth), Qt::AlignCenter, "2");
            _painter->setPen(Qt::black);
        break;
        case BLACK_3:
            _painter->fillRect(pos_y, pos_x, cellWidth, cellWidth, Qt::black);
            isgreen ? _painter->setPen(Qt::green) : _painter->setPen(Qt::white);
            _painter->drawText(QRect(pos_y, pos_x, cellWidth, cellWidth), Qt::AlignCenter, "3");
            _painter->setPen(Qt::black);
        break;
        case BLACK_4:
            _painter->fillRect(pos_y, pos_x, cellWidth, cellWidth, Qt::black);
            isgreen ? _painter->setPen(Qt::green) : _painter->setPen(Qt::white);
            _painter->drawText(QRect(pos_y, pos_x, cellWidth, cellWidth), Qt::AlignCenter, "4");
            _painter->setPen(Qt::black);
        break;
        case ENLIGHTENED:
            _painter->fillRect(pos_y, pos_x, cellWidth, cellWidth, Qt::yellow);

        break;
        case UNENLIGHTENED:
            _painter->fillRect(pos_y, pos_x, cellWidth, cellWidth, Qt::white);

        break;
        case RED_LAMP:
            _painter->drawImage(QRect(pos_y, pos_x, cellWidth, cellWidth), red_light);
        break;
        case YELLOW_LAMP:
            _painter->drawImage(QRect(pos_y, pos_x, cellWidth, cellWidth), yellow_light);
        break;

    }
        _painter->drawRect(pos_y, pos_x, cellWidth, cellWidth);
}



