#ifndef BINARYDOCUMENTSCRIPT_H
#define BINARYDOCUMENTSCRIPT_H

#include <QObject>
#include "randombytebufferreader.h"

class BinaryDocumentScript : public QObject
{
    Q_OBJECT

public:
    BinaryDocumentScript(RandomByteBufferReader* bufferReader);

public slots:


private:
    RandomByteBufferReader* m_buffer;
};

#endif // BINARYDOCUMENTSCRIPT_H
