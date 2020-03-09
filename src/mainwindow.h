#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include "rabit.h"
#include "wolf.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static const int ROWS = 20;
    static const int COLS = 20;
    static float rabitSpeed;
    static float wolfSpeed;

private:
    Ui::MainWindow *ui;
    QVector<QLabel *> grasslandVec;
    QVector<int> rabitHoles;
    QVector<int> rabitFood;
    QVector<Rabit *> rabits;
    QVector<Wolf *> wolves;
    QTimer *rabitTimer, *wolfTimer, *countDownTimer;
    int countDown = 60;

    void createGrassLand();
    void generateRabitHoles(int rabitHoleNum = 3);
    void generateRabitFood(int rabitFoodNum = 10);
    void generateRabits(int rabitNum = 3);
    void generateWolves(int wolfNum = 3);
    void setUpEnviroment(int rabitHoleNum = 3, int rabitFoodNum = 10, int wolfNum = 3);
    void setUpTimer();
    void moveRabit(Rabit *rabit, const int nextMove);
    void moveWolf(Wolf *wolf, const int nextMove);
    int isObject(const QVector<int> &object, const int pos);
    template <class Object>
    const QVector<int> getObjectPos(const QVector<Object *> &object);
    int isGameOver();
    void gameOver(const QString title);

private slots:
    void onRabitMove();
    void onWolfMove();
    void onCountDown();
    void on_startBTn_clicked();
};

#endif // MAINWINDOW_H
