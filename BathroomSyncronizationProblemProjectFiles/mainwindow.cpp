#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QThreadPool>
#include "man.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette *background_color=new QPalette;
    background_color->setColor(QPalette::Window, Qt::blue);
    ui->ManWaitingLabel->setPalette(*background_color);
    //color other counters
    background_color->setColor(QPalette::Window, Qt::magenta);
    ui->WomanWaitingLabel->setPalette(*background_color);
    background_color->setColor(QPalette::Window, Qt::black);
    ui->bathroomDivider->setPalette(*background_color);
    delete background_color;

    manWaiting=0;
    womanWaiting=0;
    womanSpawnRate=0;
    manSpawnRate=0;
    manLeftcount=0;
    womanLeftCount=0;
    finishedThreadCount=0;

    manSpawnTimer.setInterval(1000);
    womanSpawnTimer.setInterval(1000);
    manSpawnTimer.setSingleShot(false);
    womanSpawnTimer.setSingleShot(false);
    manSpawnTimer.start();
    womanSpawnTimer.start();

    connect(&manSpawnTimer,SIGNAL(timeout()),this,SLOT(spawnWaitingMan()));
    connect(&womanSpawnTimer,SIGNAL(timeout()),this,SLOT(spawnWaitingWoman()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::spawnWaitingWoman()
{
    womanWaiting+=womanSpawnRate;
    ui->WomanWaitingLabel->setText(QString::number(womanWaiting));
}

void MainWindow::spawnWaitingMan()
{
    if(manWaiting+manSpawnRate>30)
    {
        for(int counter=0;counter<manWaiting+manSpawnRate-30;counter++)
        {
            QThread* newThread=new QThread;
            Man* newMan=new Man;
            newMan->moveToThread(newThread);
            newMan->moveTimerToThread();
            connect(newThread,SIGNAL(started()),newMan,SLOT(attemptEnter()));
            connect(newThread,SIGNAL(finished()),newMan,SLOT(deleteLater()));
            connect(newMan,SIGNAL(destroyed(QObject*)),newThread,SLOT(terminate()));
            connect(newMan,SIGNAL(setInsideMan(int)),this,SLOT(setManInside(int)));
            connect(newMan,SIGNAL(manLeft()),this,SLOT(manLeft()));
            connect(newMan,SIGNAL(manWaitDecrease()),this,SLOT(manWaitDecrease()));
            newThread->start();
        }
        manWaiting=30;
        ui->ManWaitingLabel->setText(QString::number(manWaiting));
    }
    else if(manSpawnRate>0)
    {
        for(int counter=0;counter<manSpawnRate;counter++)
        {
            QThread* newThread=new QThread;
            Man* newMan=new Man;
            newMan->moveToThread(newThread);
            newMan->moveTimerToThread();
            connect(newThread,SIGNAL(started()),newMan,SLOT(attemptEnter()));
            connect(newThread,SIGNAL(finished()),newMan,SLOT(deleteLater()));
            connect(newMan,SIGNAL(done()),newThread,SLOT(quit()));
            connect(newMan,SIGNAL(setInsideMan(int)),this,SLOT(setManInside(int)));
            connect(newMan,SIGNAL(manLeft()),this,SLOT(manLeft()));
            connect(newMan,SIGNAL(manWaitDecrease()),this,SLOT(manWaitDecrease()));
            newThread->start();
        }
        manWaiting+=manSpawnRate;
        ui->ManWaitingLabel->setText(QString::number(manWaiting));
    }

}

void MainWindow::on_ManSpawnSpinbox_valueChanged(int newRate)
{
    manSpawnRate=newRate;
}

void MainWindow::on_WomanSpawnSpinbox_valueChanged(int newRate)
{
    womanSpawnRate=newRate;
}

void MainWindow::setManInside(int newManInside)
{
    ui->manInsideLabel->setText(QString::number(newManInside));
}

void MainWindow::manLeft()
{
    ui->manLeftLabel->setText(QString::number(++manLeftcount));
}

void MainWindow::manWaitDecrease()
{
    if(manWaiting>0)
    --manWaiting;
    ui->ManWaitingLabel->setText(QString::number(manWaiting));
}

