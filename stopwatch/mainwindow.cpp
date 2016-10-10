#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLCDNumber>
#include <QTextEdit>
#include "model.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hundredSec = 0;
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->display("00:00:00");
    // This makes it so we update the slot as time goes by
    QObject::connect(m.timeSignalSender, SIGNAL(timeout()), this, SLOT(prep_updateLCD()));
    QObject::connect(this, SIGNAL(update_lcd_time), ui->lcdNumber, SLOT(updatedLCD));
    QObject::connect(&m, SIGNAL(updatedTimeString(QString)), this, SLOT(updatedLCD(QString)));
    QObject::connect(this, SIGNAL(updateStart()), &m, SLOT(StartTime()));
    QObject::connect(this, SIGNAL(updatePause()), &m, SLOT(PauseTime()));
    QObject::connect(this, SIGNAL(updateReset()), &m, SLOT(ResetTime()));
    QObject::connect(this, SIGNAL(updateRestart()), &m, SLOT(RestartTime()));

}


MainWindow::~MainWindow()
{
    delete ui;
}

// This manages the Start/Restart/Pause button
// so that the button changes when we press it
// and it emits signals to update the timer
void MainWindow::on_startRestartPause_clicked()
{
    if(ui->startRestartPause->text() == "Start") {
        ui->startRestartPause->setText("Pause");
        emit updateStart();
        //m.StartTime();
    }
    else if(ui->startRestartPause->text()  == "Pause") {
        ui->startRestartPause->setText("Restart");
        emit updatePause();
        //m.PauseTime();
    }
    else if(ui->startRestartPause->text()  == "Restart"){
        ui->startRestartPause->setText("Pause");
        emit updateRestart();
        //m.RestartTime();
    }
}

// This resets the timer
void MainWindow::on_Reset_clicked()
{
    ui->startRestartPause->setText("Start");
    ui->lcdNumber->display("00:00:00");
    emit updateReset();
    //m.ResetTime();
}


// This displays the lcd number
void MainWindow::updatedLCD(QString Val)
{   
  ui->lcdNumber->display(Val);
}
// This updates the timer's time
void MainWindow::prep_updateLCD() {
    m.update_Time();
}
