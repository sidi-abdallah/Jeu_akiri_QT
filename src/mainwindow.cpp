#include "include/mainwindow.h"
#include "include/AkariModel.h"
#include "ui_mainwindow.h"
//#include "include/Grid.h"
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

    init(); // initialize the grid

    //chnage the level, size and game time according to the user's choices
    connect(ui->level_box, QOverload<int>::of(&QComboBox::currentIndexChanged), _model, &AkariModel::set_level);
    connect(ui->size_box, QOverload<int>::of(&QComboBox::currentIndexChanged), _model, &AkariModel::set_size);
    connect(ui->timer_box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::set_round_duration);

    //notifying AkariView with new changes
    connect(ui->changeGridButton, &QPushButton::clicked, this, &MainWindow::updateView);
    connect(this, SIGNAL(notify()), ui->Gridwidget,SLOT(update()));

    //Initializing timer
    _roundDuration = (RoundDuration)0;
    _duration = QTime(0, 0, 0);
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    _timer->start(1000);

    //sending signal to model when a cell is clicked and responding on this signal
    connect(ui->Gridwidget, &AkariView::cellClicked, _model, &AkariModel::onCellClicked);
    connect(_model, &AkariModel::responseOnMouseClick, ui->Gridwidget, &AkariView::setCellsState);

    //Verifying if the player won and stop the timer when the doneButton is clicked
    connect(ui->doneButton, &QPushButton::clicked, _model, &AkariModel::ONDoneClicked);
    connect(_model, &AkariModel::isDone, this, &MainWindow::onDoneClicked);
    connect(ui->doneButton, &QPushButton::clicked, this, &MainWindow::stopTimer);

    //Clearing the grid and restart timer when restartButton is clicked
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::onRestartClicked);
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::restartTimer);

    //Back down when undoButton is clicked
    connect(ui->undoButton, &QPushButton::clicked, _model, &AkariModel::unDo);


    connect(ui->changeGridButton, &QPushButton::clicked, this, &MainWindow::restartTimer);

    //AutoClick the button done when time is up
    connect(this, &MainWindow::timer_done, ui->doneButton, &QPushButton::click);

    //AutoClick the button restart when the user change the game time
    connect(ui->timer_box, QOverload<int>::of(&QComboBox::currentIndexChanged), ui->restartButton, &QPushButton::click);

    //Timer style
    QFont digitalFont(digitalFontFamily);
    digitalFont.setPointSize(20);
    ui->timer->setFont(digitalFont);

    // Shortcuts
    QMenuBar * menubar = this->menuBar();
    QMenu * filemenu = menubar->addMenu(QObject::tr("&File"));



    // CTRL+P --> print window
    QAction * printAction = filemenu->addAction(QObject::tr("&Print..."));
    printAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    printAction->setIcon(QIcon(":/icons/printer.png"));
    connect(printAction, &QAction::triggered, this, &MainWindow::printWindow);


    // CTRL+Q --> close window
    QAction * closeAction = filemenu->addAction(QObject::tr("&Close"));
    closeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    closeAction->setIcon(QIcon(":/icons/close.png"));
    connect(closeAction, &QAction::triggered, this, &QMainWindow::close);

    QMenu * gamemenu = menubar->addMenu(QObject::tr("&Game"));

    // Press "SPACE" --> restart
    QAction * restartAction = gamemenu->addAction(QObject::tr("&Restart"));
    restartAction->setShortcut(QKeySequence(Qt::Key_Space));
    restartAction->setIcon(QIcon(":/icons/restart.png"));
    connect(restartAction, &QAction::triggered, ui->restartButton, &QPushButton::click);

    // Press "ENTER" --> --> Done
    QAction *doneAction = gamemenu->addAction(QObject::tr("&Done"));
    doneAction->setShortcut(QKeySequence(Qt::Key_Return));
    connect(doneAction, &QAction::triggered, ui->doneButton, &QPushButton::click);

    // CTRL+Z --> Undo
    QAction * undoAction = gamemenu->addAction(QObject::tr("&Undo"));
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
     ui->Gridwidget->setSize(_model->get_sizeInteger());
     ui->Gridwidget->setCellsState(_model->get_cellsStateMatrix());
}



void MainWindow::updateView() {
   _model->create_grid();
   ui->Gridwidget->setSize(_model->get_sizeInteger());
   ui->Gridwidget->setCellsState(_model->get_cellsStateMatrix());
   _model->clear_vector();
   emit notify();
}

void MainWindow::onDoneClicked(bool isDone) {
    if(isDone) {
        ui->messageLabel->setText(QObject::tr("Bingoooo, You won"));
        ui->messageLabel->setStyleSheet("color: green");
    }
    else {
        ui->messageLabel->setText(QObject::tr("Oooops, Try again"));
        ui->messageLabel->setStyleSheet("color: red");
    }
}


void MainWindow::onRestartClicked() {
    ui->messageLabel->clear();
    _model->clearGrid();
    ui->Gridwidget->setSize(_model->get_sizeInteger());
    ui->Gridwidget->setCellsState(_model->get_cellsStateMatrix());
    _model->clear_vector();

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

    QString normal_timer_stylesheet = "QLabel { color : black; background-color : yellow; border : 2px solid white; border-radius : 10px;}";
    QFont alert_timer_font(digitalFontFamily);
    alert_timer_font.setPointSize(25);
    QFont normal_timer_font(digitalFontFamily);
    normal_timer_font.setPointSize(20);

    ui->timer->setStyleSheet(normal_timer_stylesheet);
    static bool is_alert_font = false;
    QFont current_font = is_alert_font ? alert_timer_font : normal_timer_font;
    ui->timer->setFont(normal_timer_font);
    ui->timer->setText(_duration.toString("HH:mm:ss"));

    switch(ui->timer_box->currentIndex()){
        case 1: // 10 Minutes
            _duration = _duration.addSecs(-1);
            if(_duration.hour() == 0 &&_duration.minute() == 0 &&_duration.second() >= 0){
                 timer_alert();
            }
            if(_duration.hour() == 23 &&_duration.minute() == 59 &&_duration.second() == 59){
                _timer->stop();
                emit(timer_done());
            }
        break;
        case 2: // 5 Minutes
            _duration = (_duration.addSecs(-1));
            if(_duration.hour() == 0 &&_duration.minute() == 0 &&_duration.second() <= 39){
                timer_alert();
            }
            if(_duration.hour() == 23 &&_duration.minute() == 59 &&_duration.second() == 59){
                _timer->stop();
                emit(timer_done());
            }
        break;
        case 3: // 3 Minutes
            _duration = (_duration.addSecs(-1));

            if(_duration.hour() == 0 &&_duration.minute() == 0 &&_duration.second() <= 19){
                timer_alert();
            }
            if(_duration.hour() == 23 &&_duration.minute() == 59 &&_duration.second() == 59){
                _timer->stop();
                emit(timer_done());
            }
        break;
        case 4: // 1 Minute
            _duration = (_duration.addSecs(-1));

            if(_duration.hour() == 0 &&_duration.minute() == 0 &&_duration.second() <= 9){
              timer_alert();

            }
            if(_duration.hour() == 23 &&_duration.minute() == 59 &&_duration.second() == 59){
                _timer->stop();
                emit(timer_done());            
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
}

void MainWindow::set_round_duration(int roundDuration){
    _roundDuration = static_cast<MainWindow::RoundDuration>(roundDuration);
}

void MainWindow::timer_alert() {
    QString alert_timer_stylesheet = "QLabel { color : white; background-color : red; border : 2px solid black; border-radius : 10px;}";
    QFont alert_timer_font(digitalFontFamily);
    alert_timer_font.setPointSize(25);
    QFont normal_timer_font(digitalFontFamily);
    normal_timer_font.setPointSize(20);
    static bool is_alert_font = false;
    ui->timer->setStyleSheet(alert_timer_stylesheet);
    is_alert_font = !is_alert_font; //Change the current state of the police
    QFont new_font = is_alert_font ? alert_timer_font : normal_timer_font;
    ui->timer->setFont(new_font);
}


