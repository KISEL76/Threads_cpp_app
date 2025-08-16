#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mythread.h"


#include <QMainWindow>
#include <QList>
#include <QProgressBar>
#include <QLabel>
#include <QWaitCondition>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_add_threadButton_clicked();

    void on_delete_threadButton_clicked();

    void on_start_threadpushButton_clicked();

    void on_stop_threadpushButton_clicked();

    void ticked();

private:
    Ui::MainWindow *ui;
    MyThread *thread_1;
    int row_count = 0;//количество строк
    int row = 0;//значение строки
    int i = -1;//элемент списка threads
    int running_threads = 0;//счётчик количества работающих потоков



    QList<MyThread*> threads;
    QList<QProgressBar*> bars;


private slots:

    void setpot();

    void on_tableWidget_currentCellChanged(int currentRow);
};
#endif // MAINWINDOW_H
