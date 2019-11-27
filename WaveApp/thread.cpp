#include "thread.h"

Thread::Thread(QObject *parent) : QThread(parent)
{

}

void Thread::run()
{
    while(this->isRunning()){

        emit this->tick();
        this->msleep(1);
    }
}
