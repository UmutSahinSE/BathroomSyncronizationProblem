#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QMutex>
#include <QTimer>

class Person : public QObject
{
    Q_OBJECT
protected:
    static QMutex manOrWomanMutex;
    QTimer* timeInBathroom;

public:
    explicit Person(QObject *parent = nullptr);
    ~Person();
    void moveTimerToThread();
signals:
    void done();
    void empty();
public slots:
    virtual void attemptEnter()=0;
    virtual void leaveBathroom()=0;
};

#endif // MAN_H
