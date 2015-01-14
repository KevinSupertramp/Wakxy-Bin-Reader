#include "binarydocument.h"

BinaryDocument::BinaryDocument(QString filepath, int dateTypeId)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    m_stop = false;

    m_fileByteArray = file.readAll();
    m_dataTypeId = dateTypeId;
    m_filepath = filepath;

    m_entries = QMap<int, strBinaryDocumentEntry>();
    m_indexes = QMap<QString, BinaryDocumentIndex*>();

    file.close();
}

BinaryDocument::~BinaryDocument()
{
    for(QMap<QString, BinaryDocumentIndex*>::iterator itr = m_indexes.begin(); itr != m_indexes.end(); ++itr)
        itr.value()->deleteLater();

    if(m_dataBuffer != NULL)
        delete m_dataBuffer;
}

void BinaryDocument::readDocument()
{
    readHeader();
    readData();
}

void BinaryDocument::readHeader()
{
    //===========
    //header ====

    QDataStream buffer(m_fileByteArray);
    buffer.setByteOrder(QDataStream::LittleEndian);

    qint64 max = buffer.device()->size(); //max

    buffer >> m_version;
    m_version += BINARYDOCUMENT_VERSION_OFFSET;
    emit version(m_version);

    RandomByteBufferReader* randomBuffer = new RandomByteBufferReader(m_fileByteArray, buffer.device()->pos(), m_dataTypeId, m_version);
    m_entryCount = randomBuffer->readInt();

    for (int i = 0; i < m_entryCount; ++i)
    {
       strBinaryDocumentEntry entry;
       entry.id = randomBuffer->readLong();
       entry.pos = randomBuffer->readInt();
       entry.size = randomBuffer->readInt();
       entry.seed = randomBuffer->readByte();

       m_entries[i] = entry;

       //=========
       //thread ==
       if(m_stop) return;
       emit progressChanged(randomBuffer->position()*100/max);
       emit newEntry(entry.id, entry.pos, entry.size, entry.seed);
       QThread::currentThread()->msleep(1); //1 ms sleep for signal
       //=========
   }

    m_indexCount = randomBuffer->readByte();
    for (int i= 0; i < m_indexCount; ++i)
    {
        //=========
        BinaryDocumentIndex* index = new BinaryDocumentIndex(randomBuffer);
        m_indexes.insert(index->getName(), index);

        //thread ==
        if(m_stop) return; //thread stop
        emit progressChanged(randomBuffer->position()*100/max);
        emit newIndex(index);
        QThread::currentThread()->msleep(1); //1 ms sleep for signal
        //=========
    }

    //=================
    //data ============
    qint64 finalPosition = randomBuffer->position();
    emit progressChanged(finalPosition*100/max); //progress update

    m_dataByteArray = m_fileByteArray.right(finalPosition);
    randomBuffer->deleteLater(); //delete not needed anymore
    m_dataBuffer = new RandomByteBufferReader(m_dataByteArray, 0, m_dataTypeId, m_version);
}

void BinaryDocument::readData()
{
    if(!m_dataBuffer)
        return;

    BinaryDocumentScript* binDocumentScript = new BinaryDocumentScript(m_dataBuffer);
    QString script = binDocumentScript->getScript(m_version, m_dataTypeId);
    if(script.isEmpty())
        return;

    qint64 max = m_dataBuffer->size(); //max

    //script loaded now
    QScriptEngine engine;
    engine.globalObject().setProperty("buffer", engine.newQObject(binDocumentScript));

    //read line
    for(int i = 0; i < m_entries.count(); i++)
    {
        QScriptValue scriptValue = engine.evaluate(script);

        if(scriptValue.isError())//@TODO error message , one error quit
            return;

        //==============================
        //thread =======================
        if(m_stop) return; //thread stop
        emit progressChanged(m_dataBuffer->position()*100/max); //update progress
        QThread::currentThread()->msleep(1); //1 ms sleep for signal
        //===============================
    }

    //adding data
    //columns
    //line

    delete binDocumentScript; //not used anymore
}
