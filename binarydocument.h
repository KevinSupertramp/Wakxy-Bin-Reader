#ifndef BINARYDOCUMENT_H
#define BINARYDOCUMENT_H

#include <QObject>
#include <QDataStream>
#include <QBitArray>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QScriptEngine>
#include <QMap>

#include "binarydocumentindex.h"
#include "randombytebufferreader.h"
#include "binarydocumentscript.h"

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
    void readDocument(); //read the current document

signals:
    void progressChanged(int percent); //progress changed
    //=============
    //data signal =
    void version(int version);
    void newEntry(qint64 id, int pos, int size, qint8 seed);
    void newIndex(BinaryDocumentIndex* index);
    //=============

public slots:
    void stopRead() { m_stop = true; }
    void onNewDataRead(int row, QString columnName, QString previousColumn, QString value);

protected:
    void readHeader();

private:
    bool m_stop;

    QByteArray m_fileByteArray;
    QString m_filepath;
    int m_dataTypeId;

    //================
    //header =========
    int m_version;

    int m_entryCount;
    QMap<int, strBinaryDocumentEntry> m_entries;

    int m_indexCount;
    QMap<QString, BinaryDocumentIndex*> m_indexes;

    //===================
    //data ==============
    QByteArray m_dataByteArray;
    RandomByteBufferReader* m_dataBuffer;
    QList<QString> m_dataColumns; //data columns
    QMap<int, QMap<QString, QString> > m_dataRows; //data rows

    void readData();
    //==================
};

#endif // BINARYDOCUMENT_H
