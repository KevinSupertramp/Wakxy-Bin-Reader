#include "binarydocument.h"

BinaryDocument::BinaryDocument(QString filepath, int dateTypeId)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    m_fileByteArray = file.readAll();
    m_dataTypeId = dateTypeId;
    m_filepath = filepath;

    m_entries = QMap<int, strBinaryDocumentEntry>();

    readHeader();
}

BinaryDocument::~BinaryDocument()
{
    delete m_dataBuffer;
}

void BinaryDocument::readHeader()
{
    //===========
    //header ====

    QDataStream buffer(m_fileByteArray);
    buffer.setByteOrder(QDataStream::LittleEndian);

    buffer >> m_version;
    m_version += BINARYDOCUMENT_VERSION_OFFSET;

    qDebug() << QString::number(m_version);

    RandomByteBufferReader* randomBuffer = new RandomByteBufferReader(m_fileByteArray, buffer.device()->pos(), m_dataTypeId, m_version);
    m_entryCount = randomBuffer->readInt();

    qDebug() << m_entryCount;

    for (int i = 0; i < m_entryCount; ++i) {

       strBinaryDocumentEntry entry;
       entry.id = randomBuffer->readLong();
       entry.pos = randomBuffer->readInt();
       entry.size = randomBuffer->readInt();
       entry.seed = randomBuffer->readByte();

       m_entries[i] = entry;
   }

    m_indexCount = randomBuffer->readByte();
    for (int i= 0; i < m_indexCount; ++i)
    {
        //@TODO
        //BinaryDocumentIndex* index = new BinaryDocumentIndex(randomBuffer);
    }

    //=================
    //data ============

    qint64 finalPosition = randomBuffer->position();
    m_dataByteArray = m_fileByteArray.right(finalPosition);

    randomBuffer->deleteLater(); //delete not needed anymore

    m_dataBuffer = new RandomByteBufferReader(m_dataByteArray, 0, m_dataTypeId, m_version);
}
