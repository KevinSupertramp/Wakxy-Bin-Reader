#include "binarydocumentindex.h"

BinaryDocumentIndex::BinaryDocumentIndex(RandomByteBufferReader *reader)
{
    bool unique = reader->readByte() != 0;

    m_name = reader->readString();
    int count = reader->readInt();

    for (int i = 0; i < count; ++i)
    {
        qint64 idx = reader->readLong();
        QList<int> entryList = QList<int>();

        if(unique)
        {
            int entry = reader->readInt();
            entryList.append(entry);
        }
        else
            entryList = reader->readIntArray();

        m_indexes[idx] = entryList;
    }
}
