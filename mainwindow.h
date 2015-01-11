#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDropEvent>
#include <QDrag>
#include <QMimeData>
#include <QFileInfo>
#include <QDebug>
#include <QThread>
#include <QtConcurrent>
#include <QFileDialog>
#include <QInputDialog>

#include "binarydocument.h"

#define DRAG_TYPE_FILE "bin"
#define UI_OPEN_TYPE_FILE "Fichier binaire (*.bin)"
#define UI_OPEN_DIALOG_TITLE "Ouvrir un fichier..."

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void onCancelRead();

private slots:
    //ui
    void onBtnCancelClick();
    void onActionOpen();

    //binarydocument
    void onVersion(int version);
    void onNewEntry(qint64 id, int pos, int size, qint8 seed);
    void onNewIndex(BinaryDocumentIndex *index);
    void onReadLine();
    void onReadComplete();
    void onProgressChanged(int percent);

private:
    Ui::MainWindow *ui;
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent* event);
    void readFile(QString filePath);

    void UpdateUI(bool readComplete);

    BinaryDocument *m_binaryDocument;
    QFutureWatcher<void> *m_watcher;
};

#endif // MAINWINDOW_H
