#ifndef CELL_H
#define CELL_H
#include "include/common.h"
#include <QPainter>
#include <QWidget>

class Cell : public QWidget
{
    Q_OBJECT

private:
    /**
     * @brief _cellState state of the cell (BALCK, BLACK_0 ...)
     */
    cellState _cellState;
public:

    explicit Cell(QWidget *parent = nullptr);
    virtual ~Cell();
    /**
     * @brief getCellState Returns the state of the cell
     * @return
     */
    cellState getCellState();

    /**
     * @brief setCellState Setter of the cell state
     */
    void setCellState(cellState);

    /**
     * @brief drawCell draws a cell based on its state using QPainter
     * @param size
     * @param pos_x
     * @param pos_y
     */
    void drawCell(QPainter *, int size, int pos_x, int pos_y);


};

#endif // CELL_H

