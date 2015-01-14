#include "binarydocumentscript.h"

BinaryDocumentScript::BinaryDocumentScript(RandomByteBufferReader* bufferReader)
{
    m_buffer = bufferReader;
    m_row = 0;
}

QString BinaryDocumentScript::getScript(int version, int dataTypeId)
{
    if(loadScript(version, dataTypeId))
        return m_script;

    return "";
}

bool BinaryDocumentScript::loadScript(int version, int dataTypeId)
{
    //script path look like
    //{APPLICATIONDIR}/scripts/{VERSION}/{DATATYPEID}.js

    QDir workingDir(QDir::currentPath()+"/scripts/"+QString::number(version));
    workingDir.mkpath("."); //create path if doesn't exist

    QString scriptFilePath = workingDir.absolutePath() + "/" + QString::number(dataTypeId) + ".js";
    QFile scriptFile(scriptFilePath);

    //file doesn't exist
    if(!scriptFile.exists())
    {
        qDebug() << scriptFilePath;
        return false;
    }

    //can't open the file
    if(!scriptFile.open(QIODevice::ReadOnly))
        return false;

    QTextStream in(scriptFile.readAll());

    m_script = in.readAll();

    //script basic implements
    //function readLine()
    //{
    //}
    //readLine();

    return true;
}

//=====================
//SLOTS ===============
//=====================

void BinaryDocumentScript::readByte(QString columnName)
{
    qint8 value = m_buffer->readByte();
    emit newDataRead(m_row, columnName, m_previousColumn, QString::number(value));
    m_previousColumn = columnName;
}

void BinaryDocumentScript::readInt(QString columnName)
{
    int value = m_buffer->readInt();
    emit newDataRead(m_row, columnName, m_previousColumn, QString::number(value));
    m_previousColumn = columnName;
}

void BinaryDocumentScript::readBool(QString columnName)
{
    bool value = m_buffer->readBool();
    emit newDataRead(m_row, columnName, m_previousColumn, QString::number(value));
    m_previousColumn = columnName;
}

void BinaryDocumentScript::readShort(QString columnName)
{
    short value = m_buffer->readShort();
    emit newDataRead(m_row, columnName, m_previousColumn, QString::number(value));
    m_previousColumn = columnName;
}

void BinaryDocumentScript::readFloat(QString columnName)
{
    float value =m_buffer->readFloat();
    emit newDataRead(m_row, columnName, m_previousColumn, QString::number(value));
    m_previousColumn = columnName;
}

void BinaryDocumentScript::readDouble(QString columnName)
{
    double value = m_buffer->readDouble();
    emit newDataRead(m_row, columnName, m_previousColumn, QString::number(value));
    m_previousColumn = columnName;
}

void BinaryDocumentScript::readLong(QString columnName)
{
    qint64 value = m_buffer->readLong();
    emit newDataRead(m_row, columnName, m_previousColumn, QString::number(value));
    m_previousColumn = columnName;
}

