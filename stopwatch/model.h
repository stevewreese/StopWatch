#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QString>

class Model : public QObject
{
    Q_OBJECT
    // QTimer sends signals every x milliseconds
    // QTime tracks elapsed time. Use start() and elapsed() methods
    QTime timeTracker;
    double hundredSec;
    int sec;
    int min;
    //saves time when paused
    int milsecsSaved;

public:
    QTimer *timeSignalSender;
    Model();
    void update_Time();

public slots:
    void StartTime();
    void PauseTime();
    void ResetTime();
    void RestartTime();

signals:
    void updatedData(int);
    void updatedTimeString(QString);
};

#endif // MODEL_H
