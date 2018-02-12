#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include "man.h"
#include "woman.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette *background_color=new QPalette;
    background_color->setColor(QPalette::Window, Qt::blue);
    ui->ManWaitingLabel->setPalette(*background_color);
    ui->manInsideLabel->setPalette(*background_color);
    ui->manLeftLabel->setPalette(*background_color);
    background_color->setColor(QPalette::Window, Qt::magenta);
    ui->WomanWaitingLabel->setPalette(*background_color);
    ui->womanInsideLabel->setPalette(*background_color);
    ui->womanLeftLabel->setPalette(*background_color);
    background_color->setColor(QPalette::Window, Qt::black);
    ui->bathroomDivider->setPalette(*background_color);
    delete background_color;

    manWaiting=0;
    womanWaiting=0;
    womanSpawnRate=0;
    manSpawnRate=0;
    manLeftcount=0;
    womanLeftCount=0;

    SpawnTimer.setInterval(1000);
    SpawnTimer.setSingleShot(false);
    SpawnTimer.start();

    connect(&SpawnTimer,SIGNAL(timeout()),this,SLOT(spawnWaitingMan()));
    connect(&SpawnTimer,SIGNAL(timeout()),this,SLOT(spawnWaitingWoman()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::spawnWaitingWoman()
{
    if(womanWaiting+womanSpawnRate>30)
    {
        for(int counter=0;counter<30-womanWaiting;counter++)
        {
            QThread* newThread=new QThread;
            Woman* newWoman=new Woman;
            newWoman->moveToThread(newThread);
            newWoman->moveTimerToThread();
            connect(newThread,SIGNAL(started()),newWoman,SLOT(attemptEnter()));
            connect(newThread,SIGNAL(finished()),newWoman,SLOT(deleteLater()));
            connect(newWoman,SIGNAL(done()),newThread,SLOT(quit()));
            connect(newWoman,SIGNAL(setInsideWoman(int)),this,SLOT(setWomanInside(int)));
            connect(newWoman,SIGNAL(womanLeft()),this,SLOT(womanLeft()));
            connect(newWoman,SIGNAL(womanWaitDecrease()),this,SLOT(womanWaitDecrease()));
            connect(newWoman,SIGNAL(empty()),this,SLOT(emptyTurn()));
            connect(newWoman,SIGNAL(womanTurn()),this,SLOT(womanTurn()));
            newThread->start();
        }
        womanWaiting=30;
        ui->WomanWaitingLabel->setText(QString::number(womanWaiting));
    }
    else if(womanSpawnRate>0)
    {
        for(int counter=0;counter<womanSpawnRate;counter++)
        {
            QThread* newThread=new QThread;
            Woman* newWoman=new Woman;
            newWoman->moveToThread(newThread);
            newWoman->moveTimerToThread();
            connect(newThread,SIGNAL(started()),newWoman,SLOT(attemptEnter()));
            connect(newThread,SIGNAL(finished()),newWoman,SLOT(deleteLater()));
            connect(newWoman,SIGNAL(done()),newThread,SLOT(quit()));
            connect(newWoman,SIGNAL(setInsideWoman(int)),this,SLOT(setWomanInside(int)));
            connect(newWoman,SIGNAL(womanLeft()),this,SLOT(womanLeft()));
            connect(newWoman,SIGNAL(womanWaitDecrease()),this,SLOT(womanWaitDecrease()));
            connect(newWoman,SIGNAL(empty()),this,SLOT(emptyTurn()));
            connect(newWoman,SIGNAL(womanTurn()),this,SLOT(womanTurn()));
            newThread->start();
        }
        womanWaiting+=womanSpawnRate;
        ui->WomanWaitingLabel->setText(QString::number(womanWaiting));
    }
}

void MainWindow::spawnWaitingMan()
{
    if(manWaiting+manSpawnRate>30)
    {
        for(int counter=0;counter<30-manWaiting;counter++)
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
            connect(newMan,SIGNAL(empty()),this,SLOT(emptyTurn()));
            connect(newMan,SIGNAL(manTurn()),this,SLOT(manTurn()));
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
            connect(newMan,SIGNAL(empty()),this,SLOT(emptyTurn()));
            connect(newMan,SIGNAL(manTurn()),this,SLOT(manTurn()));
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
void MainWindow::setWomanInside(int newWomanInside)
{
    ui->womanInsideLabel->setText(QString::number(newWomanInside));
}

void MainWindow::womanLeft()
{
    ui->womanLeftLabel->setText(QString::number(++womanLeftCount));
}

void MainWindow::womanWaitDecrease()
{
    if(womanWaiting>0)
    --womanWaiting;
    ui->WomanWaitingLabel->setText(QString::number(womanWaiting));
}

void MainWindow::manTurn()
{
    QPalette *background_color=new QPalette;
    background_color->setColor(QPalette::Window, Qt::blue);
    ui->TurnLabel->setPalette(*background_color);
    delete background_color;
}

void MainWindow::womanTurn()
{
    QPalette *background_color=new QPalette;
    background_color->setColor(QPalette::Window, Qt::magenta);
    ui->TurnLabel->setPalette(*background_color);
    delete background_color;
}

void MainWindow::emptyTurn()
{
    QPalette *background_color=new QPalette;
    background_color->setColor(QPalette::Window, Qt::gray);
    ui->TurnLabel->setPalette(*background_color);
    delete background_color;
}
