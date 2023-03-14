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
    void setGrid(Grid * grid);
    Grid * getGrid();
    virtual void paintEvent(QPaintEvent *event) override;
private:
    Grid * _grid;

public slots :
     void OncellClicked(int row, int col);
     void mousePressEvent(QMouseEvent *event) override;

signals:
    void cellClicked(int row, int col);
};

#endif // AkariView_H
