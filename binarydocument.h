#ifndef BINARYDOCUMENT_H
#define BINARYDOCUMENT_H

#include <QObject>
#include <QDataStream>
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
    BinaryDocument(QString filepath, int dateTypeId);

protected:
    void readHeader();

private:
    QByteArray m_bit;
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
    RandomByteBufferReader* m_dataBuffer;
    //==================
};

#endif // BINARYDOCUMENT_H
