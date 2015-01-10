#ifndef BINARYDOCUMENTINDEX_H
#define BINARYDOCUMENTINDEX_H

#include <QObject>
#include "randombytebufferreader.h"

class BinaryDocumentIndex : public QObject
{
    Q_OBJECT

public:
    BinaryDocumentIndex(RandomByteBufferReader* reader);

signals:

public slots:

};

#endif // BINARYDOCUMENTINDEX_H
