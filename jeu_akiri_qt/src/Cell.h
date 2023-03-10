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
    Cell();
    Cell(int, int);
    virtual ~Cell();
    // Ajoutez ici les méthodes pour modifier et accéder aux propriétés de la cellule
    int getRow();
    int getCol();
    cellState getCellState();
    void setCellState(cellState);
    void setRow(int);
    void setCol(int);
    void drawCell(QPainter *, int, int, int);
    virtual Cell & operator=(const Cell & );

signals:

};

#endif // CELL_H
