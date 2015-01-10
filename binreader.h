#ifndef BINREADER_H
#define BINREADER_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include "binarydocument.h"
#include "binarydocumentindex.h"
#include "randombytebufferreader.h"

class BinReader : public QObject
{
    Q_OBJECT

public:
    BinReader(QString filePath);
    ~BinReader();
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
