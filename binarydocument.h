#ifndef BINARYDOCUMENT_H
#define BINARYDOCUMENT_H

#include <QObject>
#include <QDataStream>
#include <QBitArray>
#include "binarydocumentindex.h"
#include "randombytebufferreader.h"

#define BINARYDOCUMENT_VERSION_OFFSET 756423

struct strBinaryDocumentEntry
{
    qint64 id;
    int pos;
    int size;
    qint8 seed;
};

class BinaryDocument : public QObject
{
     Q_OBJECT

public:
    BinaryDocument(QString filepath, int dateTypeId);
    ~BinaryDocument();

protected:
    void readHeader();

private:
    QByteArray m_fileByteArray;
    QString m_filepath;
    int m_dataTypeId;

    //================
    //header =========
    int m_version;

    int m_entryCount;
    QMap<int, strBinaryDocumentEntry> m_entries;

    int m_indexCount;
    QMap<QString, BinaryDocumentIndex> m_indexes;

    //===================
    //data ==============
    QByteArray m_dataByteArray;
    RandomByteBufferReader* m_dataBuffer;
    //==================
};

#endif // BINARYDOCUMENT_H
