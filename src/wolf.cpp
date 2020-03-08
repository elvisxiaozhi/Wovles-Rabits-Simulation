#include "wolf.h"

Wolf::Wolf(int pos) : Animal(pos)
{

}

int Wolf::chooseNextMove(const QVector<int> &rabits, const QVector<int> &rabitFood, const QVector<int> &rabitHoles)
{
    int wolfPos = getAnimalPos();
    int nearestRabit = findNeareastObject(rabits, rabitHoles);
    // 如果10步以内能找到兔子，那么就去抓兔子
    if (nearestRabit < 20 && nearestRabit != -1) {
        pair<int, int> toRabit = findNextMoveToObject(wolfPos, nearestRabit, rabitHoles);

        return toRabit.first;
    }
    else {
        int choice = rand() % 3;
        if (choice == 0) {
            int nearestRabitFood = findNeareastObject(rabitFood, rabitHoles);
            pair<int, int> toRabitFood = findNextMoveToObject(wolfPos, nearestRabitFood, rabitHoles);

            return toRabitFood.first;
        }
        else {
            QVector<int> aroundPlaces = getAroundPlaces(wolfPos);
            choice = rand() % aroundPlaces.size();

            return aroundPlaces[choice];
        }

    }

    return wolfPos;
}

bool Wolf::hasRabitEaten(QVector<Rabit *> &rabits)
{
    int wolfPos = getAnimalPos();
    for (int i = 0; i < rabits.size(); ++i) {
        if (wolfPos == rabits[i]->getAnimalPos()) {
            delete rabits[i];
            rabits.erase(rabits.begin() + i);

            return true;
        }
    }

    return false;
}
