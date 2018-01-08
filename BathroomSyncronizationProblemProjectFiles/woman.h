#ifndef WOMAN_H
#define WOMAN_H

#include <QObject>
#include <person.h>

class Woman : public Person
{
    Q_OBJECT
public:
    static QMutex initiatorMutex;
    static QMutex leaverMutex;
    static int entered;
    static int insideBathroom;
    Woman();
public slots:
    void attemptEnter();
    void leaveBathroom();
signals:
    void setInsideWoman(int newInside);
    void womanLeft();
    void womanWaitDecrease();
    void womanTurn();
};

#endif // MAN_H
