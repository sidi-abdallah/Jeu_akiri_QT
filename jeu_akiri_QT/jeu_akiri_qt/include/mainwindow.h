#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AkariModel;
class AkariView;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow * ui;
    AkariModel * _model;

    void init();

protected slots :
    /**
     * @brief updateView update all the viewWidget values from the model one when they changed
     */
    virtual void updateView();
    virtual void onDoneClicked(bool);
    virtual void onRestartClicked();

signals :
    /**
     * @brief notify sent to update of the viewWidget to launch QPainter again
     */
    void notify();
};
#endif // MAINWINDOW_H
