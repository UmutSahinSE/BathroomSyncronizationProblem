#ifndef MAN_H
#define MAN_H

#include <QObject>
#include <person.h>

class Man : public Person
{
    Q_OBJECT
public:
    static QMutex initiatorMutex;
    static QMutex leaverMutex;
    static int entered;
    static int insideBathroom;
    Man();
public slots:
    void attemptEnter();
    void leaveBathroom();
signals:
    void setInsideMan(int newInside);
    void manLeft();
    void manWaitDecrease();
};

#endif // MAN_H
