#include "woman.h"

QMutex Woman::initiatorMutex;
QMutex Woman::leaverMutex;
int Woman::entered=0;
int Woman::insideBathroom=0;

Woman::Woman()
{
    connect(timeInBathroom,SIGNAL(timeout()),this,SLOT(leaveBathroom()));
}
void Woman::attemptEnter()
{
    initiatorMutex.lock();
    if(entered==0)
    {
        manOrWomanMutex.lock();
        emit womanTurn();
        ++entered;
        ++insideBathroom;
        emit setInsideWoman(insideBathroom);
        emit womanWaitDecrease();
        timeInBathroom->start();
        initiatorMutex.unlock();
    }
    else if(entered<4)
    {
        ++entered;
        ++insideBathroom;
        emit setInsideWoman(insideBathroom);
        emit womanWaitDecrease();
        timeInBathroom->start();
        initiatorMutex.unlock();
    }
    else
    {
        ++entered;
        ++insideBathroom;
        emit setInsideWoman(insideBathroom);
        emit womanWaitDecrease();
        timeInBathroom->start();
    }
}

void Woman::leaveBathroom()
{
    leaverMutex.lock();
    --insideBathroom;
    emit setInsideWoman(insideBathroom);
    if(insideBathroom==0)
    {
        entered=0;
        manOrWomanMutex.unlock();
        emit empty();
        initiatorMutex.unlock();
    }
    emit womanLeft();
    leaverMutex.unlock();
    emit done();
}
