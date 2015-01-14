#ifndef BINARYDOCUMENTSCRIPT_H
#define BINARYDOCUMENTSCRIPT_H

#include <QObject>
#include "randombytebufferreader.h"

class BinaryDocumentScript : public QObject
{
    Q_OBJECT

public:
    BinaryDocumentScript(RandomByteBufferReader* bufferReader);
    QString getScript(int version, int dataTypeId);

public slots:


private:
    bool loadScript(int version, int dataTypeId);

    RandomByteBufferReader* m_buffer;
    QString m_script;

};

#endif // BINARYDOCUMENTSCRIPT_H
