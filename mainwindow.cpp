#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_watcher = new QFutureWatcher<void>();


    //==================
    //connect ==========
    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClick()));
    connect(ui->actionOuvrir, SIGNAL(triggered()), this, SLOT(onActionOpen()));
    //==================
}

MainWindow::~MainWindow()
{
    emit onCancelRead(); //cancel the read
    delete m_watcher;
    delete m_binaryDocument;
    delete ui;
}

 void MainWindow::dragEnterEvent(QDragEnterEvent *event)
 {
    if(m_watcher && m_watcher->isRunning()) //reading in progress, can't drag
    {
        event->ignore();
    }
    else if(event->mimeData()->hasUrls()) //only one file and bin file
    {
        QList<QUrl> urlList = event->mimeData()->urls();

        if(urlList.size() == 1)
        {
            QFileInfo dragFile(urlList[0].toLocalFile());

            if(dragFile.exists() && dragFile.suffix() == DRAG_TYPE_FILE)
                event->acceptProposedAction();
            else
                event->ignore();
        }
    }
 }

 void MainWindow::dropEvent(QDropEvent *event)
 {
    Q_UNUSED(event);

    if(event->mimeData() && event->mimeData()->urls().count() == 1)
    {
        QString filePath = event->mimeData()->urls()[0].toLocalFile();
        readFile(filePath);
    }
 }

 void MainWindow::readFile(QString filePath)
 {
     emit onCancelRead(); //cancel current read
     ui->progressBarFileReader->setValue(0); //reset progress bar value
     UpdateUI(false);

     //get the dataTypeId
     QFileInfo fileInfo(filePath);
     int dataTypeId;
     bool conversionOk;
     dataTypeId = fileInfo.baseName().toInt(&conversionOk);

     if(!conversionOk)
     {
         ui->pushButtonCancel->setEnabled(false);
         return;
     }

     //======
     //ui ===
     ui->lineEditDataTypeId->setText(QString::number(dataTypeId));
     ui->tableWidgetDocumentEntry->setRowCount(0);
     ui->tableWidgetFile->setRowCount(0);
     ui->treeWidgetIndexes->clear();
     //=======

     m_binaryDocument = new BinaryDocument(filePath, dataTypeId); //setup binary reader

     //ui signal
     connect(m_binaryDocument, &BinaryDocument::version, this, &MainWindow::onVersion);
     connect(m_binaryDocument, &BinaryDocument::newEntry, this, &MainWindow::onNewEntry);
     connect(m_binaryDocument, &BinaryDocument::newIndex, this, &MainWindow::onNewIndex);

     //thread signal
     connect(this, &MainWindow::onCancelRead, m_binaryDocument, &BinaryDocument::stopRead);
     connect(m_binaryDocument, &BinaryDocument::progressChanged, this, &MainWindow::onProgressChanged);

     QFuture<void> separateThread = QtConcurrent::run(m_binaryDocument, &BinaryDocument::readDocument); //run inside another thread
     connect(m_watcher, SIGNAL(finished()), this, SLOT(onReadComplete())); //done signal
     m_watcher->setFuture(separateThread); //connect watcher
 }

 void MainWindow::UpdateUI(bool readComplete)
 {
     ui->pushButtonCancel->setEnabled(!readComplete); //disable the button
     ui->actionOuvrir->setEnabled(readComplete);
     ui->actionSauvegarderCSV->setEnabled(readComplete);
 }

 //==============================
 //SLOTS ========================
 //==============================

 void MainWindow::onBtnCancelClick()
 {
     emit onCancelRead(); //cancel the reading
     UpdateUI(false);
 }

 void MainWindow::onReadLine()
 {
     //qDebug() << "add the line read on table...";
 }

 void MainWindow::onVersion(int version)
 {
     ui->lineEditVersion->setText(QString::number(version));
 }

 void MainWindow::onNewEntry(qint64 id, int pos, int size, qint8 seed)
 {
     int index = ui->tableWidgetDocumentEntry->rowCount();
     ui->tableWidgetDocumentEntry->insertRow(index);

     ui->tableWidgetDocumentEntry->setItem(index, 0, new QTableWidgetItem(QString::number(id)));
     ui->tableWidgetDocumentEntry->setItem(index, 1, new QTableWidgetItem(QString::number(pos)));
     ui->tableWidgetDocumentEntry->setItem(index, 2, new QTableWidgetItem(QString::number(size)));
     ui->tableWidgetDocumentEntry->setItem(index, 3, new QTableWidgetItem(QString::number(seed)));
 }

 void MainWindow::onNewIndex(BinaryDocumentIndex* index)
 {
    QTreeWidgetItem* itemRoot = new QTreeWidgetItem(); //root item
    itemRoot->setText(0, index->getName()); //name

    //data
    QMap<qint64, QList<int> > indexes = index->getIndexes();
    for(QMap<qint64, QList<int> >::iterator itr = indexes.begin(); itr != indexes.end(); ++itr)
    {
         QTreeWidgetItem* itemChild = new QTreeWidgetItem(itemRoot);
         itemChild->setText(0, QString::number(itr.key()));

         QList<int> values = itr.value();
         foreach(int i, values)
         {
            QTreeWidgetItem* itemChildSecond = new QTreeWidgetItem(itemChild);
            itemChildSecond->setText(0, QString::number(i));
         }
    }

    //add
    ui->treeWidgetIndexes->addTopLevelItem(itemRoot);
 }

 void MainWindow::onProgressChanged(int percent)
 {
     ui->progressBarFileReader->setValue(percent);
 }

 void MainWindow::onReadComplete()
 {
     UpdateUI(true);
 }

 void MainWindow::onActionOpen()
 {
     QString filename = QFileDialog::getOpenFileName(this, UI_OPEN_DIALOG_TITLE, "", UI_OPEN_TYPE_FILE);

     if(filename.isNull())
        return;

     readFile(filename);
 }


