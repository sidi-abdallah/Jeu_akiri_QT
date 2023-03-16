#ifndef GRID_H
#define GRID_H
#include <QWidget>
#include "include/common.h"
#include "include/Matrix.h"

class Cell;
class QGridLayout;
class Grid : public QWidget
{
    Q_OBJECT
public:
    explicit Grid(QWidget *parent = nullptr);
    int getSize();
    void setSize(int size);
    Matrix<cellState> & getCellsState();
    int getCellWidth();

    void drawGrid(QPainter * painter, int height);

private:
    int _size;
    int _cellWidth;
    Matrix<cellState> & _cellsState;
public slots:
        void setCellsState(Matrix<cellState> & cellsState);

signals:
    void notify();

};

#endif // GRID_H
