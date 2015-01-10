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
    delete m_binReader;
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

     //connect my reader on the correct function
     m_binReader = new BinReader(filePath); //setup binary reader

     connect(m_binReader, &BinReader::onReadLine, this, &MainWindow::onReadLine);
     connect(this, &MainWindow::onCancelRead, m_binReader, &BinReader::stop);
     connect(m_binReader, &BinReader::progressChanged, this, &MainWindow::onProgressChanged);

     QFuture<void> separateThread = QtConcurrent::run(m_binReader, &BinReader::read); //run inside another thread
     m_watcher->setFuture(separateThread); //connect watcher
     connect(m_watcher, SIGNAL(finished()), this, SLOT(onReadComplete())); //done signal
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


