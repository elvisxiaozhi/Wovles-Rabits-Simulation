#include "rabit.h"
#include "mainwindow.h"

Rabit::Rabit(int pos) : Animal(pos), hideTime(0)
{

}

int Rabit::chooseNextMove(const QVector<int> &rabitFood, const QVector<int> &rabitHoles, const QVector<int> &wolves)
{
    int rabitPos = getAnimalPos();
    int wolfPos = checkObjInSurroundings(rabitPos, 5, wolves);
    if (wolfPos == -1) {
        int nearestRabitFoodPos = findNeareastObject(rabitFood, wolves);
        pair<int, int> toRabitFood = findNextMoveToObject(rabitPos, nearestRabitFoodPos, wolves);

        return toRabitFood.first;
    }
    else {
        int beforeRabitDies = 10;
        int nearestRabitHole = findNeareastObject(rabitHoles, wolves);
        int costToNearestRabitHole = calculateCostToObject(rabitPos, nearestRabitHole, wolves);
        if (costToNearestRabitHole < beforeRabitDies) {
            pair<int, int> toRabitHole = findNextMoveToObject(rabitPos, nearestRabitHole, wolves);

            return toRabitHole.first;
        }

        int nearestRabitFoodPos = findNeareastObject(rabitFood, wolves);
        int costToNearestRabitFood = calculateCostToObject(rabitPos, nearestRabitFoodPos, wolves);
        if (costToNearestRabitFood < beforeRabitDies) {
            pair<int, int> toRabitFood = findNextMoveToObject(rabitPos, nearestRabitFoodPos, wolves);

            return toRabitFood.first;
        }
    }

    QVector<int> aroundPlaces = getAroundPlaces(rabitPos);
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

bool Rabit::isTimeToComeOut()
{
    if (hideTime > 0) {
        --hideTime;

        return false;
    }

    return true;
}

void Rabit::updateHideTime()
{
    hideTime = 3;
}
