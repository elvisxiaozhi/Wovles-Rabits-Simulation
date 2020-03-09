#include "rabit.h"
#include "mainwindow.h"

Rabit::Rabit(int pos) : Animal(pos)
{

}

int Rabit::chooseNextMove(const QVector<int> &rabitFood, const QVector<int> &rabitHoles, const QVector<int> &wolves)
{
    int rabitPos = getAnimalPos();
    int wolfPos = checkObjInSurroundings(rabitPos, 5, wolves); // 检测兔子周围5圈有没有狼, 5这个数视实际情况可改大或改小
    if (wolfPos == -1) { // 要是没有狼的话
        // 检测兔子周围最近的萝卜, 并去吃萝卜
        int nearestRabitFoodPos = findNeareastObject(rabitFood, wolves);
        pair<int, int> toRabitFood = findNextMoveToObject(rabitPos, nearestRabitFoodPos, wolves);

        updateHideStatus(false);

        return toRabitFood.first;
    }
    else { // 如果兔子周围5圈有狼的话
        if (isHidden) // 如果周围5圈内还是有狼, 继续躲在兔子洞里面
            return getAnimalPos();

        int beforeRabitDies = 10; // 那么意味着最快10步之内(此时速度为1.5 ： 1), 兔子必被狼吃掉
        int nearestRabitHole = findNeareastObject(rabitHoles, wolves); // 那么此时赶紧检测最近的兔子洞
        int costToNearestRabitHole = calculateCostToObject(rabitPos, nearestRabitHole, wolves); // 如果在被狼吃掉之前能跑回兔子洞
        if (costToNearestRabitHole < beforeRabitDies) {
            // 就赶紧跑回兔子洞
            pair<int, int> toRabitHole = findNextMoveToObject(rabitPos, nearestRabitHole, wolves);

            return toRabitHole.first;
        }
    }

    QVector<int> aroundPlaces = getAroundPlaces(rabitPos, wolves);
    int minCost = INT_MIN;
    int nextMove = aroundPlaces[0];
    for (int i = 0; i < aroundPlaces.size(); ++i) {
        int cost = calculateCostToObject(wolfPos, aroundPlaces[i], wolves);
        if (minCost < cost) {
            minCost = cost;
            nextMove = aroundPlaces[i];
        }
    }

    return nextMove;
}

void Rabit::updateHideStatus(const bool status)
{
    isHidden = status;
}
