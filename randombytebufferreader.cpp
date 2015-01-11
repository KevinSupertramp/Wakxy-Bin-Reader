#include "randombytebufferreader.h"

RandomByteBufferReader::RandomByteBufferReader(QByteArray byte, qint64 pos, int mult, int add)
{
    //================
    //randomizer =====
    m_mult = mult;
    m_add = add;
    m_seed = m_mult ^ m_add;

    m_byteArray = byte;
    m_buffer = new QDataStream(m_byteArray);
    m_buffer->setByteOrder(QDataStream::LittleEndian);
    m_buffer->device()->seek(pos);
}

RandomByteBufferReader::~RandomByteBufferReader()
{
    delete m_buffer;
}

//=====================
//read ================

qint8 RandomByteBufferReader::readByte()
{
    inc();
    qint8 value;
    *m_buffer >> value;  
    return (value - m_seed);
}

int RandomByteBufferReader::readInt()
{
    inc();

    int value;
    *m_buffer >> value;
    return (value - m_seed);
}


bool RandomByteBufferReader::readBool()
{
    inc();
    qint8 value;
    *m_buffer >> value;
    return (value - m_seed != 0);
}

short RandomByteBufferReader::readShort()
{
    inc();
    short value;
    *m_buffer >> value;
    return value - m_seed;
}

float RandomByteBufferReader::readFloat()
{
    inc();
    float value;
    *m_buffer >> value;
    return value;
}

double RandomByteBufferReader::readDouble()
{
    inc();
    double value;
    *m_buffer >> value;
    return value;
}

qint64 RandomByteBufferReader::readLong()
{
    inc();
    qint64 value;
    *m_buffer >> value;
    return value - m_seed;
}

QList<int> RandomByteBufferReader::readIntArray()
{
    int size = readInt();
    QList<int> data = QList<int>();

    for (int i = 0; i < size; ++i) {
        data[i] = this->readInt();
    }

    return data;
}

QString RandomByteBufferReader::readString()
{
    int size = readInt();
    QByteArray data;

    for (int i = 0; i < size; ++i) {
        qint8 value;
        *m_buffer >> value;
        data[i] = value;
    };

    return QString::fromUtf8(data);
}

//===========================

void RandomByteBufferReader::setPosition(qint64 position, qint8 seed)
{
    m_buffer->device()->seek(position);
    m_seed = seed;
}

void RandomByteBufferReader::inc()
{
    m_seed += (qint8)(m_mult * position() + m_add);
}
