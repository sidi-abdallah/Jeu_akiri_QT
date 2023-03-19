#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QTimer>
#include <QTime>

class AkariModel;
class AkariView;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow Constructor function of MainWindow class with initialization and connection of various UI elements and signals.
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow * ui;

    /**
     * @brief _model Instance of AkariModel (in the presentator :: MVP archtecture)
     */
    AkariModel * _model;

    /**
     * @brief digitalFontFamily Defines a new font which served to display timer with digital digits
     */
    const QString digitalFontFamily = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/digital_font/DS-DIGI.TTF")).at(0);

    /**
     * @brief The RoundDuration enum Mode of the game
     */
    enum RoundDuration{
        unlimited = 0,
        ten_minutes,
        five_minutes,
        three_minutes,
        one_minute
    };

    /**
     * @brief _duration It represents how much time has been passed.
     */
    QTime _duration;

    /**
     * @brief _timer It handles the timer object
     */
    QTimer * _timer;

    /**
     * @brief _roundDuration Defines the mode has been chosen by user
     */
    RoundDuration _roundDuration;

    /**
     * @brief init Initializes the game grid and sets its size and cells state based on the current level and size selected in the UI.
     */
    void init();

protected:
    /**
     * @brief closeEvent Saves the position of the main window in the application settings when the user closes the window.
     */
    void closeEvent(QCloseEvent *);

protected slots :
    /**
     * @brief updateView update all the viewWidget values from the model one when they changed
     */
    virtual void updateView();

    /**
     * @brief onDoneClicked Updates the UI message label based on whether the game is won or lost.
     */
    virtual void onDoneClicked(bool);

    /**
     * @brief onRestartClicked Resets the grid and clears the message label.
     */
    virtual void onRestartClicked();

    /**
     * @brief printWindow Allow the player to save a pdf format screen shot of its grid
     */
    virtual void printWindow();


private slots :
    /**
     * @brief updateTimer Function to update a timer displayed in a GUI, with options for different time intervals and alert styles.
     */
    virtual void updateTimer();

    /**
     * @brief restartTimer Restart timer with a new duration based on the round type.
     */
    virtual void restartTimer();

    /**
     * @brief stopTimer Stops the timer
     */
    virtual void stopTimer();

    /**
     * @brief set_round_duration Setter of _roundDuration
     * @param roundDuration
     */
    virtual void set_round_duration(int roundDuration);

signals :
    /**
     * @brief notify sent to update of the viewWidget to launch QPainter again
     */
    void notify();

    /**
     * @brief timer_done emitted signal when Done button is clicked
     */
    void timer_done();
};
#endif // MAINWINDOW_H
