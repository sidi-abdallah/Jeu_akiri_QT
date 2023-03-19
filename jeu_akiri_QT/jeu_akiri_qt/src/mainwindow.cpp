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
    connect(ui->timer_box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::set_round_duration);

    connect(ui->changeGridButton, &QPushButton::clicked, this, &MainWindow::updateView);
    connect(this, SIGNAL(notify()), ui->Gridwidget,SLOT(update()));
    connect(ui->Gridwidget, &AkariView::cellClicked, _model, &AkariModel::onCellClicked);
    connect(_model, &AkariModel::responseOnMouseClick, ui->Gridwidget->getGrid(), &Grid::setCellsState);
    connect(ui->Gridwidget->getGrid(), SIGNAL(notify()), ui->Gridwidget,SLOT(update()));
    connect(ui->doneButton, &QPushButton::clicked, _model, &AkariModel::ONDoneClicked);
    connect(_model, &AkariModel::isDone, this, &MainWindow::onDoneClicked);
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::onRestartClicked);
    connect(ui->undoButton, &QPushButton::clicked, _model, &AkariModel::unDo);


    _duration = QTime(0, 0, 0);
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    _timer->start(1000);
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::restartTimer);
    connect(ui->changeGridButton, &QPushButton::clicked, this, &MainWindow::restartTimer);
    connect(ui->doneButton, &QPushButton::clicked, this, &MainWindow::stopTimer);
    connect(this, &MainWindow::timer_done, ui->doneButton, &QPushButton::click);
    connect(ui->timer_box, QOverload<int>::of(&QComboBox::currentIndexChanged), ui->restartButton, &QPushButton::click);
    QFont digitalFont(digitalFontFamily);
    digitalFont.setPointSize(20);
    ui->timer->setFont(digitalFont);

    // Shortcuts
    QMenuBar * menubar = this->menuBar();
    QMenu * filemenu = menubar->addMenu("&File");



    // CTRL+P --> print window
    QAction * printAction = filemenu->addAction("&Print...");
    printAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    printAction->setIcon(QIcon(":/icons/printer.png"));
    connect(printAction, &QAction::triggered, this, &MainWindow::printWindow);


    // CTRL+Q --> close window
    QAction * closeAction = filemenu->addAction("&Close");
    closeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    closeAction->setIcon(QIcon(":/icons/close.png"));
    connect(closeAction, &QAction::triggered, this, &QMainWindow::close);

    QMenu * gamemenu = menubar->addMenu("&Game");

    // Press "SPACE" --> restart
    QAction * restartAction = gamemenu->addAction("&Restart");
    restartAction->setShortcut(QKeySequence(Qt::Key_Space));
    restartAction->setIcon(QIcon(":/icons/restart.png"));
    connect(restartAction, &QAction::triggered, ui->restartButton, &QPushButton::click);

    // Press "ENTER" --> --> Done
    QAction *doneAction = gamemenu->addAction("&Done");
    doneAction->setShortcut(QKeySequence(Qt::Key_Return));
    connect(doneAction, &QAction::triggered, ui->doneButton, &QPushButton::click);

    // CTRL+Z --> Undo
    QAction * undoAction = gamemenu->addAction("&Undo");
    undoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    // undoAction->setIcon(QIcon(":/icons/restart.png"));
    connect(undoAction, &QAction::triggered, ui->undoButton, &QPushButton::click);

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
        ui->messageLabel->setStyleSheet("color: green");
    }
    else {
        ui->messageLabel->setText("Oooops, Try again");
        ui->messageLabel->setStyleSheet("color: red");
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


void MainWindow::updateTimer(){
    QString alert_timer_stylesheet = "QLabel { color : white; background-color : red; border : 2px solid black; border-radius : 10px;}";
    QString normal_timer_stylesheet = "QLabel { color : black; background-color : yellow; border : 2px solid white; border-radius : 10px;}";

    QFont alert_timer_font(digitalFontFamily);
    alert_timer_font.setPointSize(25);
    QFont normal_timer_font(digitalFontFamily);
    normal_timer_font.setPointSize(20);

    ui->timer->setStyleSheet(normal_timer_stylesheet);
    static bool is_alert_font = false;
    QFont current_font = is_alert_font ? alert_timer_font : normal_timer_font;
    ui->timer->setFont(normal_timer_font);

//    _duration = (_duration.addSecs(1));
    ui->timer->setText(_duration.toString("HH:mm:ss"));
    switch(ui->timer_box->currentIndex()){
        case 1: // 10 Minutes
            _duration = _duration.addSecs(-1);
            if(_duration.hour() == 0 &&_duration.minute() == 0 &&_duration.second() >= 0){
                is_alert_font = !is_alert_font; // basculer l'état actuel de la police
                QFont new_font = is_alert_font ? alert_timer_font : normal_timer_font;
                ui->timer->setFont(new_font);
                ui->timer->setStyleSheet(alert_timer_stylesheet);
            }
            if(_duration.hour() == 23 &&_duration.minute() == 59 &&_duration.second() == 59){
                _timer->stop();
                emit(timer_done());
                // il faut desactiver la grille
            }
        break;
        case 2: // 5 Minutes
            _duration = (_duration.addSecs(-1));
            if(_duration.hour() == 0 &&_duration.minute() == 0 &&_duration.second() <= 39){
                is_alert_font = !is_alert_font; // basculer l'état actuel de la police
                QFont new_font = is_alert_font ? alert_timer_font : normal_timer_font;
                ui->timer->setFont(new_font);
                ui->timer->setStyleSheet(alert_timer_stylesheet);
            }
            if(_duration.hour() == 23 &&_duration.minute() == 59 &&_duration.second() == 59){
                _timer->stop();
                emit(timer_done());
                // il faut desactiver la grille
            }
        break;
        case 3: // 3 Minutes
            _duration = (_duration.addSecs(-1));

            if(_duration.hour() == 0 &&_duration.minute() == 0 &&_duration.second() <= 19){
                is_alert_font = !is_alert_font; // basculer l'état actuel de la police
                QFont new_font = is_alert_font ? alert_timer_font : normal_timer_font;
                ui->timer->setFont(new_font);
                ui->timer->setStyleSheet(alert_timer_stylesheet);
            }
            if(_duration.hour() == 23 &&_duration.minute() == 59 &&_duration.second() == 59){
                _timer->stop();
                emit(timer_done());
                // il faut desactiver la grille
            }
        break;
        case 4: // 1 Minute
            _duration = (_duration.addSecs(-1));

            if(_duration.hour() == 0 &&_duration.minute() == 0 &&_duration.second() <= 9){
                ui->timer->setStyleSheet(alert_timer_stylesheet);
                is_alert_font = !is_alert_font; // basculer l'état actuel de la police
                QFont new_font = is_alert_font ? alert_timer_font : normal_timer_font;
                ui->timer->setFont(new_font);

            }
            if(_duration.hour() == 23 &&_duration.minute() == 59 &&_duration.second() == 59){
                _timer->stop();
                emit(timer_done());
                // il faut desactiver la grille
            }
        break;
        default: // Unlimited time mode
            _duration = _duration.addSecs(1);
        break;

    }

}

void MainWindow::restartTimer(){
    switch(_roundDuration){
    case 0:
        _duration = (QTime(0, 0, 0));
        break;
    case 1:
        _duration = (QTime(0, 10, 0));
        break;
    case 2:
        _duration = (QTime(0, 5, 0));
        break;
    case 3:
        _duration = (QTime(0, 3, 0));
        break;
    case 4:
        _duration = (QTime(0, 1, 0));
        break;
    }
    ui->timer->setText(_duration.toString("HH:mm:ss"));
    _timer->start(1000);
}

void MainWindow::stopTimer(){
    _timer->stop();
}


void MainWindow::closeEvent(QCloseEvent *)
{
  QSettings settings;
  settings.setValue("Config/WindowPosition", frameGeometry().topLeft());
//  settings.setValue("Config/AkariSize", _model->get_size());
}

void MainWindow::set_round_duration(int roundDuration){
    _roundDuration = static_cast<MainWindow::RoundDuration>(roundDuration);
}
