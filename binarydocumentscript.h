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
    void setRow(int row) { m_row = row; }
    void newRow() { m_row++;}

public slots:
    void readByte(QString columnName);
    void readInt(QString columnName);
    void readBool(QString columnName);
    void readShort(QString columnName);
    void readFloat(QString columnName);
    void readDouble(QString columnName);
    void readLong(QString columnName);

signals:
    void newDataRead(int row, QString columnName, QString previousColumn, QString value);

private:
    bool loadScript(int version, int dataTypeId);

    RandomByteBufferReader* m_buffer;
    QString m_script;
    QString m_previousColumn;
    int m_row;

};



#endif // BINARYDOCUMENTSCRIPT_H
