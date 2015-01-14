#include "binarydocumentscript.h"

BinaryDocumentScript::BinaryDocumentScript(RandomByteBufferReader* bufferReader)
{
    m_buffer = bufferReader;
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
    //==================

    return true;
}
