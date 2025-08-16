#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>
#include <QProgressBar>
#include <QWaitCondition>
#include <QString>
#include "QTimer"
#include "QTime"
#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer;
    timer = new QTimer(this);
    timer->setInterval(10);

    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(timer, SIGNAL(timeout()),this,SLOT(ticked()));
    connect(ui->tableWidget, &QTableWidget::currentCellChanged, this, &MainWindow::on_tableWidget_currentCellChanged);
    timer->start(10);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_threadButton_clicked()
{
    row_count++;
    ui->tableWidget->setRowCount(row_count);

    int count = ui->spinBox->value();

    //создаём объект потока
    MyThread *thread = new MyThread;
    threads.append(thread);
    thread->Count = ui->spinBox->value();
    i++;


    //добавляем строку в таблицу
    QTableWidgetItem *item = new QTableWidgetItem("Поток");
    ui->tableWidget->setItem(row,0, item);

    QProgressBar *bar = new QProgressBar(this);
    bar->setMaximum(count);

    ui->tableWidget->setCellWidget(row,1,bar);
    row++;

    //коннект потока
    connect(threads.back(), SIGNAL(progress(int)), bar, SLOT(setValue(int))); // полоска загрузки
    connect(threads.back(), SIGNAL(potoki()), this, SLOT(setpot()));

}

void MainWindow::on_delete_threadButton_clicked()
{
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow >= 0 && selectedRow < threads.size())
    {
        row_count--;
        row--;
        ui->tableWidget->removeRow(selectedRow);

        threads[selectedRow]->running = false;
        if (!threads[selectedRow]->wait(500))
        {
            threads[selectedRow]->terminate();
        }

        delete threads[selectedRow];
        threads.removeAt(selectedRow);

        // обновим переменную i
        if (threads.size() > 0)
            i = qMin(selectedRow, threads.size() - 1);
        else
            i = -1;
    }
    else
    {
        QMessageBox::information(this, "Внимание!", "Поток не найден!");
    }
}


void MainWindow::on_start_threadpushButton_clicked()
{
    if (i >= 0)
    {
        if(!threads[i]->isRunning()) //поток нельзя запустить еще раз, пока он не закончится
        {
            running_threads++;
            threads[i]->running = true;
            threads[i]->start();
        }
        if(threads[i]->percents != 0)
        {
            threads[i]->schet = threads[i]->percents;
        }
    }
    else
    {
        QMessageBox::information(this, "Внимание!", "Поток не найден!");
        return;
    }
}


void MainWindow::on_stop_threadpushButton_clicked()
{
    if (i>=0)
    {
        threads[i]->running=false;
        threads[i]->wait(500);
    }
    else
    {
        QMessageBox::information(this, "Внимание!", "Поток не найден!");
    }
}

void MainWindow::setpot()
{
    running_threads--;
}

void MainWindow::ticked() //Событие на каждый тик
{
    QString str = QString::number(running_threads);
    ui->pot->setText(str);
}


void MainWindow::on_tableWidget_currentCellChanged(int currentRow)
{
    if (currentRow >= 0 && currentRow < threads.size()) {
        i = currentRow;
    } else {
        i = 0;
    }
}

