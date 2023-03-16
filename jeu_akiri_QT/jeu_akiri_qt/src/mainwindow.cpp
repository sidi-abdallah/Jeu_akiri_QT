#include "include/mainwindow.h"
#include "include/AkariModel.h"
#include "ui_mainwindow.h"
#include "include/Grid.h"
#include <QAction>
#include <QShortcut>
#include <QtPrintSupport/QtPrintSupport>
#include <QPainter>
#include <QIcon>

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
   // connect(ui->undoButton, &QPushButton::clicked, _model, &AkariModel::unDo);

    //Timer handling
    ui->Gridwidget->set_timerLabel(ui->timer);

//       connect(ui->Gridwidget->get_timer(), &QTimer::timeout, this, &MainWindow::updateTimer);
//       _model->get_timer()->start(1000);
       connect(ui->restartButton, &QPushButton::clicked, ui->Gridwidget, &AkariView::restartTimer);
       connect(ui->changeGridButton, &QPushButton::clicked, ui->Gridwidget, &AkariView::restartTimer);
       connect(ui->doneButton, &QPushButton::clicked, ui->Gridwidget, &AkariView::stopTimer);
       connect(ui->timer_box, QOverload<int>::of(&QComboBox::currentIndexChanged), ui->restartButton, &QPushButton::click);
       QFont font("Arial", 15);
       ui->timer->setFont(font);


       // Shortcuts
       QMenuBar * menubar = this->menuBar();
       QMenu * filemenu = menubar->addMenu("File");



       // CTRL+P --> print window
       QAction * printAction = filemenu->addAction("Print...");
       printAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
       printAction->setIcon(QIcon(":/icons/printer.png"));
       connect(printAction, &QAction::triggered, this, &MainWindow::printWindow);

       // CTRL+Q --> close window
          QAction * closeAction = filemenu->addAction("Close");
          closeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
          closeAction->setIcon(QIcon(":/icons/close.png"));
          connect(closeAction, &QAction::triggered, this, &QMainWindow::close);

          QMenu * gamemenu = menubar->addMenu("Game");

          // Press "Enter" --> restart
          QAction * restartAction = gamemenu->addAction("Restart");
          restartAction->setShortcut(QKeySequence(Qt::Key_Space));
          restartAction->setIcon(QIcon(":/icons/restart.png"));
          connect(restartAction, &QAction::triggered, ui->restartButton, &QPushButton::click);

          // CTRL+D --> Done
          QAction *doneAction = gamemenu->addAction("Done");
          doneAction->setShortcut(QKeySequence(Qt::Key_Return));

          connect(doneAction, &QAction::triggered, ui->doneButton, &QPushButton::click);


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
     ui->Gridwidget->set_round_duration(ui->timer_box->currentIndex());
}



void MainWindow::updateView() {
   _model->create_grid();
   ui->Gridwidget->getGrid()->setSize(_model->get_sizeInteger());
   ui->Gridwidget->getGrid()->setCellsState(_model->get_cellsStateMatrix());

   emit notify();
}

void MainWindow::onDoneClicked(bool isDone) {
    if(isDone) {
        ui->messageLabel->setText(tr("Bingoooo, You won"));
        //(tr("Some text in english")
    }
    else {
        ui->messageLabel->setText(tr("Oooops, Try again"));
    }
}


void MainWindow::onRestartClicked() {
    ui->messageLabel->clear();
    _model->clearGrid();
    ui->Gridwidget->getGrid()->setSize(_model->get_sizeInteger());
    ui->Gridwidget->getGrid()->setCellsState(_model->get_cellsStateMatrix());

}

void MainWindow::printWindow(){
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if(dialog.exec() == QDialog::Accepted){
        QPainter painter(&printer);
        painter.drawPixmap(0, 0, QWidget::grab());
    }
}



void MainWindow::closeEvent(QCloseEvent *)
{
  QSettings settings;
  settings.setValue("Config/WindowPosition", frameGeometry().topLeft());
}













