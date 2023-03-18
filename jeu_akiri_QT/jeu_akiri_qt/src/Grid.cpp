#include "include/Grid.h"
#include <QPainter>
#include "include/Cell.h"
#include <QGridLayout>
Grid::Grid(QWidget *parent)
    : QWidget(parent), _cellsState(*new Matrix<cellState>(7))
{

}

int Grid::getSize(){
    return _size;
}

void Grid::setSize(int size){
    _size = size;
}

int Grid::getCellWidth() {
    return _cellWidth;
}

Matrix<cellState> & Grid::getCellsState() {
    return _cellsState;
}

void Grid::setCellsState(Matrix<cellState> & cellsState) {
    _cellsState = cellsState;
    emit notify();
}

void Grid::drawGrid(QPainter * _painter, int height){
    int x_start_point = height / 10;
    int y_start_point = height / 10;
    _cellWidth =  (8 * x_start_point) / _size;
    int pos_x, pos_y;

    QFont font = _painter->font();
    font.setPixelSize(_cellWidth);
    font.setFamily("Arial");
    _painter->setFont(font);

    for (int row = 0; row < _size; row++){
        for (int col = 0; col < _size; col++){
            Cell * cell = new Cell(this);
            cell->setCellState(_cellsState(row, col));
            pos_x = (_cellWidth * row) + x_start_point;
            pos_y = (_cellWidth * col) + y_start_point;
            cell->drawCell(_painter, _cellWidth, pos_x, pos_y);
        }
    }
}




