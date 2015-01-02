#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


 void MainWindow::dragEnterEvent(QDragEnterEvent * event)
 {
     // only one file and bin file
    if(event->mimeData()->hasUrls())
    {
        QList<QUrl> urlList = event->mimeData()->urls();

        if(urlList.size() == 1)
        {
            QFileInfo* dragFile = new QFileInfo(urlList[0].toLocalFile());

            if(dragFile->exists() && dragFile->suffix() == DRAG_TYPE_FILE)
            {
                event->acceptProposedAction();
            }
            else
                event->ignore();
        }
    }
 }

 void MainWindow::dropEvent(QDropEvent *event)
 {
    Q_UNUSED(event);

    QThread* mybThread = new QThread;
    BinReader* myReader = new BinReader;

    myReader->moveToThread(mybThread);
    connect(myReader, SIGNAL(startWork(int)), this, SLOT(setMaxProgressBar(int)));
    connect(myReader, SIGNAL(progress(int)), this, SLOT(setValueProgressBar(int)));
    connect(mybThread, SIGNAL(started()), myReader, SLOT(doWork()));

    mybThread->start();

    qDebug() << "drop complete";
 }

 void MainWindow::setMaxProgressBar(int max)
 {
    ui->progressBarFileReader->setMaximum(max);
 }

 void MainWindow::setValueProgressBar(int value)
 {
     ui->progressBarFileReader->setValue(value);
 }
