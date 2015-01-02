#ifndef BINREADER_H
#define BINREADER_H

#include <QObject>
#include <QThread>

class BinReader : public QObject
{
    Q_OBJECT

signals:
    void progress(int progressValue);
    void startWork(int maxValue);

public slots:
    void doWork();

public:
    BinReader(); 
};

#endif // BINREADER_H
