#ifndef AKARIVIEW_H
#define AKARIVIEW_H

#include <QWidget>
#include"common.h"
#include "include/Matrix.h"

class Grid;
class AkariView : public QWidget
{
    Q_OBJECT
public:
    explicit AkariView(QWidget *parent = nullptr);

private:
//    Matrix<cellState> & _cellsState;
//    int _size;
    Grid * _grid;

public:
//    void set_size(int size);
//    void set_matrix(Matrix<cellState> & matrix);
    void setGrid(Grid * grid);
    Grid * getGrid();
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

signals:
    void cellClicked(int row, int col);
};

#endif // AkariView_H
