#ifndef RANDOMBYTEBUFFERREADER_H
#define RANDOMBYTEBUFFERREADER_H

#include <QtCore>
#include <QObject>
#include <QDataStream>
#include <QList>

class RandomByteBufferReader : public QObject
{
    Q_OBJECT

public:
    RandomByteBufferReader(QByteArray byte, qint64 pos, int mult, int add);
    ~RandomByteBufferReader();

    qint64 position() { return m_buffer->device()->pos(); }
    qint64 size() { return m_buffer->device()->size(); }

    qint8 readByte(); //get() in RandomByteBuffer.java
    int readInt();
    bool readBool();
    short readShort();
    float readFloat();
    double readDouble();
    qint64 readLong();

    QList<int> readIntArray();
    QList<short> readShortArray();
    QList<float> readFloatArray();
    QList<qint64> readLongArray();

    QString readString();
    QByteArray readByteArray();
    QList<QString> readStringArray();

protected:
    void setPosition(qint64 position, qint8 seed);
    void inc();

private:
    //==============
    //randomizer ===
    qint8 m_seed;
    int m_add;
    int m_mult;
    //==============

    QByteArray m_byteArray;
    QDataStream *m_buffer;
};

#endif // RANDOMBYTEBUFFERREADER_H
