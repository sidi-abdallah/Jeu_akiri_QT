#include "include/AkariView.h"
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
//#include "include/Matrix.h"
#include "include/Grid.h"
#include <QGridLayout>


AkariView::AkariView(QWidget *parent) : QWidget(parent)
{

    _grid = new Grid(this);
     connect(_grid, SIGNAL(notify()), this,SLOT(update()));

}

void AkariView::setGrid(Grid * grid) {
    _grid = grid;
}

Grid * AkariView::getGrid() {
    return _grid;
}
void AkariView::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), Qt::lightGray);

    _grid->drawGrid(&painter, height());

}

void AkariView::OncellClicked(int row, int col) {
    emit cellClicked(row, col);
}


void AkariView::mousePressEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();
    const int pos_x_at_grid = pos.x() -  (height() / 10);
    const int pos_y_at_grid = pos.y() -  (height() / 10);

    if(pos_x_at_grid < 0 || pos_x_at_grid > (_grid->getSize() * _grid->getCellWidth()) || pos_y_at_grid < 0 || pos_y_at_grid > (_grid->getSize() * _grid->getCellWidth())) {
        return;
    }
    const int row = pos_y_at_grid / _grid->getCellWidth();
    const int col = pos_x_at_grid / _grid->getCellWidth();
    emit cellClicked(row, col);
}



