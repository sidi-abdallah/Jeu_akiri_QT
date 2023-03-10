#ifndef GRID_H
#define GRID_H
#include <QWidget>
#include "include/common.h"
#include "include/Matrix.h"

class Cell;
class Grid : public QWidget
{
    Q_OBJECT
public:
    explicit Grid(QWidget *parent = nullptr);

private:
    int _size;
    //Matrix<Cell> & _cellsMatrix;
    Matrix<cellState> & _cellsState;
    int _cellWidth;
    //int _height;

public:
    Grid();
   // Grid(int size, int height);
    int getSize();
    void setSize(int size);
    //Matrix<Cell> & getCellsMatrix();
   // void setCellsMatrix(Matrix<Cell> & cellsMatrix);
    Matrix<cellState> & getCellsState();
    void setCellsState( Matrix<cellState> & cellsState);

    void drawGrid(QPainter * painter, int height);
//    Grid & operator=(const Grid & grid);
//    Cell & operator()(int row, int col);


};

#endif // GRID_H
