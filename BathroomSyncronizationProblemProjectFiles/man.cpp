#include "man.h"

QMutex Man::initiatorMutex;
QMutex Man::leaverMutex;
int Man::entered=0;
int Man::insideBathroom=0;

Man::Man()
{
    connect(timeInBathroom,SIGNAL(timeout()),this,SLOT(leaveBathroom()));
}
void Man::attemptEnter()
{
    initiatorMutex.lock();
    if(entered==0)
    {
        manOrWomanMutex.lock();
        ++entered;
        ++insideBathroom;
        emit setInsideMan(insideBathroom);
        emit manWaitDecrease();
        timeInBathroom->start();
        initiatorMutex.unlock();
    }
    else if(entered<4)
    {
        ++entered;
        ++insideBathroom;
        emit setInsideMan(insideBathroom);
        emit manWaitDecrease();
        timeInBathroom->start();
        initiatorMutex.unlock();
    }
    else
    {
        ++entered;
        ++insideBathroom;
        emit setInsideMan(insideBathroom);
        emit manWaitDecrease();
        timeInBathroom->start();
    }
}

void Man::leaveBathroom()
{
    leaverMutex.lock();
    --insideBathroom;
    emit setInsideMan(insideBathroom);
    if(insideBathroom==0)
    {
        entered=0;
        manOrWomanMutex.unlock();
        initiatorMutex.unlock();
    }
    emit manLeft();
    leaverMutex.unlock();
    emit done();
}
