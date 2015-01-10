#include "binreader.h"

BinReader::BinReader(QString filePath)
{
    m_stop = false;
    m_filePath = filePath;
}

BinReader::~BinReader()
{
}

void BinReader::read()
{
    m_stop = false;
    int max = 100;

    BinaryDocument* doc = new BinaryDocument(m_filePath, 69);

    for(int i = 0; i <= max; i++)
    {
        if(m_stop) return;

        emit onReadLine(); //read line done
        emit progressChanged(i*100/max);

        QThread::currentThread()->msleep(100); //100 ms sleep
    }

    doc->deleteLater();
}

//=====================
// SLOT ===============
//=====================

void BinReader::stop()
{
    m_stop = true;
}
