#include "randombytebufferreader.h"


RandomByteBufferReader::RandomByteBufferReader(QByteArray bytes, int mult, int add)
{
    //================
    //randomizer =====
    m_mult = mult;
    m_add = add;
    m_seed = QByteArray::number(m_mult * m_add);
    //================

    m_bytes = bytes;
    m_buffer = new QBuffer(m_bytes);
}

T RandomByteBufferReader::read<T>()
{
    T value;
    return value;
}

QList<T> RandomByteBufferReader::readList<T>()
{
    QList<T> list = new QList<T>;
    return list;
}

void RandomByteBufferReader::setPosition(qint64 position, QByteArray seed)
{
    m_buffer->seek(position);
    m_seed = seed;
}

void RandomByteBufferReader::inc()
{
    m_seed += QByteArray::number(m_mult * position() + m_add);
}

//========================
//SLOTS ==================
//========================
