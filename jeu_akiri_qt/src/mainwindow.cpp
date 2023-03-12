#include "include/mainwindow.h"
#include "include/AkariModel.h"
#include "ui_mainwindow.h"
#include "include/Grid.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new AkariModel();

    init();
    connect(ui->level_box, QOverload<int>::of(&QComboBox::currentIndexChanged), _model, &AkariModel::set_level);
    connect(ui->size_box, QOverload<int>::of(&QComboBox::currentIndexChanged), _model, &AkariModel::set_size);

    connect(ui->changeGridButton, &QPushButton::clicked, this, &MainWindow::updateView);
    connect(this, SIGNAL(notify()), ui->Gridwidget,SLOT(update()));
    connect(ui->Gridwidget, &AkariView::cellClicked, _model, &AkariModel::onCellClicked);
    connect(_model, &AkariModel::responseOnMouseClick, ui->Gridwidget->getGrid(), &Grid::setCellsState);
   // connect(ui->Gridwidget->getGrid(), SIGNAL(notify()), ui->Gridwidget,SLOT(update()));
    connect(ui->doneButton, &QPushButton::clicked, _model, &AkariModel::ONDoneClicked);
    connect(_model, &AkariModel::isDone, this, &MainWindow::onDoneClicked);
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::onRestartClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::init(){
    _model->set_level(ui->level_box->currentIndex());
    _model->set_size(ui->size_box->currentIndex());
    _model->create_grid();
     ui->Gridwidget->getGrid()->setSize(_model->get_sizeInteger());
     ui->Gridwidget->getGrid()->setCellsState(_model->get_cellsStateMatrix());
}



void MainWindow::updateView() {
   _model->create_grid();
   ui->Gridwidget->getGrid()->setSize(_model->get_sizeInteger());
   ui->Gridwidget->getGrid()->setCellsState(_model->get_cellsStateMatrix());
   emit notify();
}

void MainWindow::onDoneClicked(bool isDone) {
    if(isDone) {
        ui->messageLabel->setText("Bingoooo, You won");
    }
    else {
        ui->messageLabel->setText("Oooops, Try again");
    }
}


void MainWindow::onRestartClicked() {
    ui->messageLabel->clear();
    _model->clearGrid();
    ui->Gridwidget->getGrid()->setSize(_model->get_sizeInteger());
    ui->Gridwidget->getGrid()->setCellsState(_model->get_cellsStateMatrix());

}







