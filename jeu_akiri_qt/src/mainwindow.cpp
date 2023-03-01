#include "include/mainwindow.h"
#include "include/AkariModel.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new AkariModel();
    _model->set_level(ui->level_box->currentIndex());
    _model->set_size(ui->size_box->currentIndex());
    connect(ui->level_box, QOverload<int>::of(&QComboBox::currentIndexChanged), _model, &AkariModel::set_level);
    connect(ui->size_box, QOverload<int>::of(&QComboBox::currentIndexChanged), _model, &AkariModel::set_size);
    _model->create_grid();
    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::updateView);
    connect(this, SIGNAL(notify()), ui->GridWidget,SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::updateView() {
    //Decommeter cette sequence lorsque les fonctions setMatrix et set_size sont definis
//      ui->GridWidget->setMatrix(_model->get_matrix());
//      ui->GridWidget->set_size(_model->get_sizeInteger());
     emit notify();
}
