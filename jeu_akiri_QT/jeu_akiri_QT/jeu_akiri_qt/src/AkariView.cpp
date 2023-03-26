#include "include/AkariView.h"
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QGridLayout>
#include "include/Cell.h"
#include "include/common.h"


AkariView::AkariView(QWidget *parent) : QWidget(parent), _cellsState(*new Matrix<cellState>(7))
{
    connect(this, SIGNAL(notify()), this,SLOT(update()));
}

void AkariView::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor customColor(37, 150, 190);
    drawGrid(&painter, height());

}

void AkariView::mousePressEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();
    const int pos_x_at_grid = pos.x() -  (height() / 10);
    const int pos_y_at_grid = pos.y() -  (height() / 10);

    if(pos_x_at_grid < 0 || pos_x_at_grid > (_size * _cellSize) || pos_y_at_grid < 0 || pos_y_at_grid > (_size * _cellSize)) {
        return;
    }
    const int row = pos_y_at_grid / _cellSize;
    const int col = pos_x_at_grid / _cellSize;
    emit cellClicked(row, col);
}


int AkariView::getSize(){
    return _size;
}

void AkariView::setSize(int size){
    _size = size;
}

int AkariView::getCellWidth() {
    return _cellSize;
}

Matrix<cellState> & AkariView::getCellsState() {
    return _cellsState;
}

void AkariView::setCellsState(Matrix<cellState> & cellsState) {
    _cellsState = cellsState;
    emit notify();
}

void AkariView::drawGrid(QPainter * _painter, int height){
    int x_start_point = height / 10;
    int y_start_point = height / 10;
    _cellSize =  (8 * x_start_point) / _size;
    int pos_x, pos_y;
    int lampsAroundNB = 0;
    QFont font = _painter->font();
    font.setPixelSize(_cellSize);
    font.setFamily("Arial");
    _painter->setFont(font);

    for (int row = 0; row < _size; row++){
        for (int col = 0; col < _size; col++){
            Cell * cell = new Cell(this);
            cell->setCellState(_cellsState(row, col));
            pos_x = (_cellSize * row) + x_start_point;
            pos_y = (_cellSize * col) + y_start_point;
            lampsAroundNB = 0;
            //isgreen = false;
            if(static_cast<int>(_cellsState(row, col)) <=4 && static_cast<int>(_cellsState(row, col)) >= 1) {

                for(int i = row - 1; i <= row + 1; i += 2) {
                    if(row >= 0 && row < _size && (_cellsState(i, col) == RED_LAMP || _cellsState(i, col) == YELLOW_LAMP)) {
                        lampsAroundNB++;
                    }
                }
                for(int i = col - 1; i <= col + 1; i += 2) {
                    if(col >= 0 && col < _size && (_cellsState(row, i) == RED_LAMP || _cellsState(row, i) == YELLOW_LAMP)) {
                        lampsAroundNB++;
                    }
                }
                if(lampsAroundNB == static_cast<int>(_cellsState(row, col))) {
                    cell->drawCell(_painter, _cellSize, pos_x, pos_y, true);
                }
                else {
                    cell->drawCell(_painter, _cellSize, pos_x, pos_y, false);
                }
            } else {
                cell->drawCell(_painter, _cellSize, pos_x, pos_y);
            }

        }
    }
}

