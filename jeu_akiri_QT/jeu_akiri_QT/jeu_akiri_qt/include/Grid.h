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
    /**
     * @brief getSize Getter of the grid's size
     * @return size of the grid
     */
    int getSize();
    /**
     * @brief setSize Setter of grid's size
     * @param size
     */
    void setSize(int size);

    /**
     * @brief getCellsState Getter of cellsStates' matrix
     * @return
     */
    Matrix<cellState> & getCellsState();

    /**
     * @brief getCellWidth grid's cell width getter
     * @return
     */
    int getCellWidth();

    /**
     * @brief drawGrid Draws the grid by iterating through cells and calling the drawCell function of each cell.
     * @param painter
     * @param height
     */
    void drawGrid(QPainter * painter, int height);

private:
    /**
     * @brief _size Size of grid
     */
    int _size;

    /**
     * @brief _cellWidth Grid's cell width
     */
    int _cellWidth;

    /**
     * @brief _cellsState Grid's cells states matrix
     */
    Matrix<cellState> & _cellsState;
public slots:
        /**
         * @brief setCellsState Modify _cellsState matrix and emit a signal notify()
         * @param cellsState
         */
        void setCellsState(Matrix<cellState> & cellsState);

signals:
     /**
     * @brief notify That cellsState matrix has been changed
     */
    void notify();

};

#endif // GRID_H
