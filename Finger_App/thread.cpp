#include "thread.h"

Thread::Thread(QObject *parent) : QThread(parent)
{

}

void Thread::run()
{
    while(this->isRunning()){

//        if ( this->isFinished() )
        {
            emit this->tick();
        }

        // TO DO: get cpu use and increase to 25% use
        this->msleep(30);

        // 40ms = 14% cpu
        // 30ms = 17%
        // 20ms = 23%
        // 15   = 23%
        // 10   = 23% // aplikacja zacina sie po kliknieciu mysza
    }
}
