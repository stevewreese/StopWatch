#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //QString ButtonText;


public:
    explicit MainWindow(QWidget *parent = 0);
    void PushButton();
    ~MainWindow();

private slots:
    void on_startRestartPause_clicked();

    void on_Reset_clicked();

public slots:
    //void showTime();

    void updatedLCD(QString Val);
    void prep_updateLCD();

signals:
    void updatedData(double);
    void updatedTimeStr(QString);
    void updateStart();
    void updatePause();
    void updateReset();
    void updateRestart();

private:
    Ui::MainWindow *ui;
    Model m;
    double hundredSec;
};

#endif // MAINWINDOW_H
