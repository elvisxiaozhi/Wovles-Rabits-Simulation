#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include "rabit.h"
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
    QTimer *timer;

    void createGrassLand();
    void generateRabitHoles(int rabitHolesNum = 3);
    void generateRabitFood(int rabitFoodNum = 10);
    void generateRabits(int rabitNum = 3);
    void moveRabit(Rabit *rabit);
    void moveRabit(Rabit *rabit, const int nextMove);
    bool isRabitHole(const int pos);
    int isRabitFood(const int pos);

protected:
    void keyPressEvent(QKeyEvent *);
    void onTimerTimeOut();
};

#endif // MAINWINDOW_H
