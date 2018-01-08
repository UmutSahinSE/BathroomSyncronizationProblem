#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    int manSpawnRate;
    int womanSpawnRate;
    int womanWaiting;
    int manWaiting;
    int manLeftcount;
    int womanLeftCount;
    int finishedThreadCount;
    QTimer manSpawnTimer;
    QTimer womanSpawnTimer;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
public slots:
    void spawnWaitingMan();
    void spawnWaitingWoman();
    void setManInside(int newManInside);
    void manLeft();
    void manWaitDecrease();
private slots:
    void on_ManSpawnSpinbox_valueChanged(int newRate);
    void on_WomanSpawnSpinbox_valueChanged(int newRate);

};

#endif // MAINWINDOW_H
