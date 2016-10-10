#include "model.h"
#include <QTextStream>
Model::Model()
{
    timeSignalSender = new QTimer(this);
    hundredSec = 0;
    sec = 0;
    min = 0;
    // This saves the number milliseconds on the timer if the person presses pause
    milsecsSaved = 0;
}
void Model::StartTime(){
    timeTracker.start();
    timeSignalSender->start(10);
}
void Model::PauseTime(){
    milsecsSaved = timeTracker.elapsed() + milsecsSaved;
    timeSignalSender->stop();
}

void Model::ResetTime(){
    milsecsSaved = 0;
    timeSignalSender->stop();
}

void Model::RestartTime(){
    timeTracker.restart();
    timeSignalSender->start(10);
}

void Model::update_Time() {
    // el is the elapsed time in milliseconds
    int el = timeTracker.elapsed() + milsecsSaved;
    // Get the time
    int mins = el/(60*1000);
    int secs = (el%(60*1000))/1000;
    int hunds = ((el%(60*1000))%1000)/10;

    // This converts the values to zero-padded strings
    // (i.e. if mins = 1, m_txt = "01" and if mins = 12, m_txt = "12")
    QString m_txt = QString("%1").arg(mins, 2, 'f',0, '0');
    QString s_txt = QString("%1").arg(secs, 2, 'f',0, '0');
    QString h_txt = QString("%1").arg(hunds, 2, 'f',0, '0');
    // String all the strings together with colons
    QString str_txt;
    QTextStream(&str_txt) << m_txt << ":" << s_txt << ":" << h_txt;

    emit updatedTimeString(str_txt);
}
