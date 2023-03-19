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
    /**
     * @brief AkariView Constructor for the AkariView class, which sets up a grid for the Akari puzzle and connects it to the update slot of the widget
     * @param parent
     */
    explicit AkariView(QWidget *parent = nullptr);

    /**
     * @brief setGrid Setter function for the Grid object in the AkariView class
     * @param grid
     */
    void setGrid(Grid * grid);

    /**
     * @brief getGrid Getter function for the Grid object in the AkariView class
     * @return
     */
    Grid * getGrid();

    /**
     * @brief paintEvent Paints the Akari grid and fills the widget background with a light gray color
     * @param event
     */
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Grid * _grid;

public slots :
    /**
      * @brief OncellClicked Slot function that emits a signal indicating a cell in the grid has been clicked
      * @param row
      * @param col
      */
     void OncellClicked(int row, int col);

     /**
      * @brief mousePressEvent detects the cell clicked on the grid in AkariView
      * @param event
      */
     void mousePressEvent(QMouseEvent *event) override;

signals:
    void cellClicked(int row, int col);
};

#endif // AkariView_H
