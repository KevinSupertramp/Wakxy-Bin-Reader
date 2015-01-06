#include "binarydocument.h"

BinaryDocument::BinaryDocument(QString filepath, int dateTypeId)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    m_bit = file.readAll();
    m_dataTypeId = dateTypeId;
    m_filepath = filepath;

    readHeader();
}

void BinaryDocument::readHeader()
{
    QDataStream stream(m_bit);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream >> m_version;
    m_version += BINARYDOCUMENT_VERSION_OFFSET;

    qDebug() << QString::number(m_version);

    m_dataBuffer = new RandomByteBufferReader(stream.device()->readAll(), m_dataTypeId, m_version);

    m_entryCount = m_dataBuffer->readInt();
    qDebug() << QString::number(m_entryCount);
}
