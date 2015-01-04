#ifndef BINREADER_H
#define BINREADER_H

#include <QObject>
#include <QThread>
#include <QDebug>

class BinReader : public QObject
{
    Q_OBJECT
public:
    BinReader();
    explicit BinReader(QString filePath, QObject *parent = 0);
    void read();

private:
    bool m_stop;
    QString m_filePath;

signals:
    void onReadLine(); //read line complete
    void progressChanged(int percent); //Progress changed

public slots:
    void stop(); //stop the current reading


};

#endif // BINREADER_H
