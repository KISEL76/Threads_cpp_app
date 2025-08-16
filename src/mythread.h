#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    int Count; //cчет до

    bool running = true; //состояние потока

    int potoks = 0; //количество потоков

    int percents = 0; //проценты, на которых мы остановились

    int schet = 0; //счётчик процентов


signals:
    void progress(int value);

    void potoki();


protected:
    void run() override; // перегрузка метода по наследованию
};

#endif // MYTHREAD_H
