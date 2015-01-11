#ifndef BINARYDOCUMENTINDEX_H
#define BINARYDOCUMENTINDEX_H

#include <QObject>
#include "randombytebufferreader.h"

class BinaryDocumentIndex : public QObject
{
    Q_OBJECT

public:
    BinaryDocumentIndex(RandomByteBufferReader* reader);
    QString getName() { return m_name; }
    QMap<qint64, QList<int> > getIndexes() { return m_indexes; }

private:
    QString m_name;
    QMap<qint64, QList<int> > m_indexes;
};

#endif // BINARYDOCUMENTINDEX_H
