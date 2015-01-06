#ifndef RANDOMBYTEBUFFERREADER_H
#define RANDOMBYTEBUFFERREADER_H

#include <QObject>
#include <QBuffer>

class RandomByteBufferReader : public QObject
{
    Q_OBJECT
public:
    RandomByteBufferReader(QByteArray bytes, int mult, int add);
    qint64 position() { return m_buffer->pos(); }
    T read<T>();
    QList<T> readList<T>();

public slots:
    //========
    //read<T> implements
    bool readBool();
    short readShort();
    float readFloat();
    int readInt();
    double readDouble();

    //================
    //readList<T> implements
    QList<int> readIntArray();
    QList<short> readShortArray();
    QList<float> readFloatArray();
    QList<long> readLongArray();

    //=================
    QString readString();
    QByteArray readByteArray();
    QList<QString> readStringArray();

protected:
    void setPosition(int position, QByteArray seed);
    void inc();

private:
    //==============
    //randomizer ===
    QByteArray m_seed;
    int m_add;
    int m_mult;
    //==============

    QByteArray m_bytes;
    QBuffer* m_buffer;


};

#endif // RANDOMBYTEBUFFERREADER_H
