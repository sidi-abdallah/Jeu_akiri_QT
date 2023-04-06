#ifndef AKARIVIEW_H
#define AKARIVIEW_H

#include <QWidget>
#include"common.h"
#include "include/Matrix.h"

class Cell;
class AkariView : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief AkariView Constructor for the AkariView class, which sets up a grid for the Akari puzzle and connects it to the update slot of the widget
     * @param parent
     */
    explicit AkariView(QWidget *parent = nullptr);

    /**
     * @brief paintEvent Paints the Akari grid and fills the widget background with a light gray color
     * @param event
     */
    virtual void paintEvent(QPaintEvent *event) override;

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
     * @brief _cellSize Grid's cell width
     */
    int _cellSize;

    /**
     * @brief _cellsState Grid's cells states matrix
     */
    Matrix<cellState> & _cellsState;

public slots :
     /**
      * @brief mousePressEvent detects the cell clicked on the grid in AkariView and emits a cellClicked signal
      * @param event
      */
     void mousePressEvent(QMouseEvent *event) override;

     /**
      * @brief setCellsState Modify _cellsState matrix and emit a signal notify to notify the Qpainter to get updated
      * @param cellsState
      */
     void setCellsState(Matrix<cellState> & cellsState);

signals:
     /**
     * @brief cellClicked emits when a cell is clicked by the mouse
     * @param row
     * @param col
     */
    void cellClicked(int row, int col);

    /**
    * @brief notifies That cellsState matrix has been changed
    */
   void notify();
};

#endif // AkariView_H


