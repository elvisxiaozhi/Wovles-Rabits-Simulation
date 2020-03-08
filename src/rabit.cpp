#include "rabit.h"
#include "mainwindow.h"

Rabit::Rabit(int pos) : Animal(pos)
{

}

int Rabit::chooseNextMove(const QVector<int> &rabitFood, const QVector<int> &rabitHoles, const QVector<int> &wolves)
{
    int rabitPos = getAnimalPos();
    int nearestWolfPos = findNeareastObject(wolves, rabitHoles);
    // 如果5步之内没有狼，那么这个时候选择去吃萝卜
    if (nearestWolfPos > 5) {
        int nearestRabitFoodPos = findNeareastObject(rabitFood, wolves);
        pair<int, int> toRabitFood = findNextMoveToObject(rabitPos, nearestRabitFoodPos, wolves);
        return toRabitFood.first;
    }
    else { // 如果5步之内有狼，则检测最近的兔子洞在哪
        int nearestRabitHole = findNeareastObject(rabitHoles, wolves);
        if (nearestRabitHole < nearestWolfPos) { //如果能在狼追上自己前跑回兔子洞，那么就炮会兔子洞
            pair<int, int> toRabitHole = findNextMoveToObject(rabitPos, nearestRabitHole, wolves);
            return toRabitHole.first;
        }
        else { // 不然就只有死了，这个时候要么选择继续往兔子洞跑，或者去吃萝卜
            int choice = rand() % 1;
            if (choice == 0) {
                int nearestRabitFoodPos = findNeareastObject(rabitFood, wolves);
                pair<int, int> toRabitFood = findNextMoveToObject(rabitPos, nearestRabitFoodPos, wolves);

                return toRabitFood.first;
            }
            else {
                pair<int, int> toRabitHole = findNextMoveToObject(rabitPos, nearestRabitHole, wolves);

                return toRabitHole.first;
            }
        }
    }

    return rabitPos;
}
