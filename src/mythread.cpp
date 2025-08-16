#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}


void MyThread::run()
{
    //имитация долгой работы
    for (int i = schet; i <= Count; i++)
    {
        emit progress(i);
        QThread::msleep(100);
        if (running==false)
        {
            percents = i;
            break;
        }
    }
    emit potoki();
}
