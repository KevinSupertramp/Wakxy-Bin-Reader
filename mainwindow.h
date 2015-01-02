#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDropEvent>
#include <QDrag>
#include <QMimeData>
#include <QFileInfo>
#include <QDebug>
#include <QThread>

#include "binreader.h"

#define DRAG_TYPE_FILE "bin"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setMaxProgressBar(int max);
    void setValueProgressBar(int value);


private:
    Ui::MainWindow *ui;
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent* event);
};

#endif // MAINWINDOW_H
