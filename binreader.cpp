#include "binreader.h"

BinReader::BinReader(QString filePath, QObject *parent) :
    QObject(parent)
{
    m_stop = false;
    m_filePath = filePath;
}

void BinReader::read()
{
    m_stop = false;
    int max = 100;

    for(int i = 0; i <= max; i++)
    {
        if(m_stop) return;

        emit onReadLine(); //read line done
        emit progressChanged(i*100/max);

        QThread::currentThread()->msleep(100); //100 ms sleep
    }
}

//=====================
// SLOT ===============
//=====================

void BinReader::stop()
{
    m_stop = true;
}
