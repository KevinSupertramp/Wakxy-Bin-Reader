#ifndef BINARYDOCUMENT_H
#define BINARYDOCUMENT_H

#include <QObject>
#include <QBuffer>
#include "binarydocumentindex.h"
#include "randombytebufferreader.h"

#define BINARYDOCUMENT_VERSION_OFFSET 756423

struct strBinaryDocumentEntry
{
    long id;
    int pos;
    int size;
    QBitArray seed;
};

class BinaryDocument : public QObject
{
     Q_OBJECT

public:
    BinaryDocument(QString filename, int dateTypeId);

private:

    QBitArray m_bytes;
    QString m_filename;
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
    RandomByteBufferReader* m_dataBuffer;
    //==================
};

#endif // BINARYDOCUMENT_H
