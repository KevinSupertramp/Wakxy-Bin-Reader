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
    RandomByteBufferReader(QByteArray bit, int mult, int add);
    qint64 position() { return m_buffer->device()->pos(); }

    bool readBool();
    short readShort();
    float readFloat();
    int readInt();
    double readDouble();

    QList<int> readIntArray();
    QList<short> readShortArray();
    QList<float> readFloatArray();
    QList<long> readLongArray();

    QString readString();
    QByteArray readByteArray();
    QList<QString> readStringArray();

protected:
    void setPosition(qint64 position, QByteArray seed);
    void inc();

private:
    //==============
    //randomizer ===
    QByteArray m_seed;
    int m_add;
    int m_mult;
    //==============

    QByteArray m_bit;
    QDataStream* m_buffer;


};

#endif // RANDOMBYTEBUFFERREADER_H
