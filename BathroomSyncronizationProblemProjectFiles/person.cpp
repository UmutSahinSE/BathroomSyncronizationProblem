#include "person.h"

QMutex Person::manOrWomanMutex;

Person::Person(QObject *parent) : QObject(parent)
{
    timeInBathroom=new QTimer;
    timeInBathroom->setInterval(2000);
    timeInBathroom->setSingleShot(true);

}

void Person::moveTimerToThread()
{
    timeInBathroom->moveToThread(this->thread());
}




