#include "randombytebufferreader.h"


RandomByteBufferReader::RandomByteBufferReader(QByteArray bit, int mult, int add)
{
    //================
    //randomizer =====
    m_mult = mult;
    m_add = add;

    QDataStream steam(&m_seed, QIODevice::ReadWrite);
    steam << (m_mult ^ m_add);

    /*
    Un peu de théorie, dans notre seed nous avous notre valeur comme ceci :
    0x000005A5 = 00000000 00000000 00000101 10100101  (1445)
    sauf que ce n'est pas comme quand on fait un (byte) (monmachin) en java
    enfaite je crois qu'il fait ceci :
    0xFFFFFFA5 = 11111111 11111111 11111111 10100101  (-91)

    Un bon sujet : http://stackoverflow.com/questions/842817/how-does-java-convert-int-into-byte

    Le debugger de qt me balance bien pour mon seed[5] -91/165 ;
    Comment peut-on obtenir le -91 ?
    Il faut juste garder le dernier octet et passer tout les autres a 255.
    */
    //================

    m_bit = bit;
    m_buffer = new QDataStream(m_bit);
    m_buffer->setByteOrder(QDataStream::LittleEndian);
}

int RandomByteBufferReader::readInt()
{
    inc();
    uint size = sizeof(int); //type size

    int value;
    *m_buffer >> value;

    return value;
}

void RandomByteBufferReader::setPosition(qint64 position, QByteArray seed)
{
    m_buffer->device()->seek(position);
    m_seed = seed;
}

void RandomByteBufferReader::inc()
{
    m_seed += QByteArray::number(m_mult * position() + m_add); //DNU
}
