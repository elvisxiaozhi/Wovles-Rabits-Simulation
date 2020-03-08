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

private:
    Ui::MainWindow *ui;
    enum directions { Up, Down, Left, Right } rabitDir, wolfDir;
    QVector<QLabel *> grasslandVec;
    QVector<int> rabitHoles;
    QVector<int> rabitFood;
    QVector<Rabit *> rabits;
    QVector<Wolf *> wolves;
    QTimer *rabitTimer, *wolfTimer;

    void createGrassLand();
    void generateRabitHoles(int rabitHoleNum = 3);
    void generateRabitFood(int rabitFoodNum = 10);
    void generateRabits(int rabitNum = 3);
    void generateWolves(int wolfNum = 3);
    void setUpEnviroment(int rabitHoleNum = 3, int rabitFoodNum = 10, int rabitNum = 3, int wolfNum = 3);
    void setUpTimer();
    void moveRabit(Rabit *rabit);
    void moveRabit(Rabit *rabit, const int nextMove);
    void moveWolf(Wolf *wolf, const int nextMove);
    bool isRabitHole(const int pos);
    int isRabitFood(const int pos);
    bool isObject(const QVector<int> &object, const int pos);
    template <class Object>
    const QVector<int> getObjectPos(const QVector<Object *> &object);
    int isGameOver();

protected:
    void keyPressEvent(QKeyEvent *);
    void onRabitMove();
    void onWolfMove();
};

#endif // MAINWINDOW_H
