#include "binreader.h"

BinReader::BinReader()
{
}


void BinReader::doWork()
{
    int max = 100;
    emit startWork(max);

    for(int i = 0; i <= max; i++)
    {
        emit progress(i);
        QThread::msleep(1000);
    }
}
