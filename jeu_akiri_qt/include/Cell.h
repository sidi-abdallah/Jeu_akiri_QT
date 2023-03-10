#ifndef CELL_H
#define CELL_H
#include "include/common.h"
#include <QPainter>
#include <QWidget>

class Cell : public QWidget
{
    Q_OBJECT

private:
    int _row;
    int _col;
    cellState _cellState;
public:
    explicit Cell(QWidget *parent = nullptr);
    virtual ~Cell();
    cellState getCellState();
    void setCellState(cellState);
    void drawCell(QPainter *, int size, int pos_x, int pos_y);

signals:

};

#endif // CELL_H

