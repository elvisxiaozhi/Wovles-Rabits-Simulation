#include "wolf.h"

Wolf::Wolf(int pos) : Animal(pos)
{

}

int Wolf::chooseNextMove(const QVector<int> &rabits, const QVector<int> &rabitHoles)
{
    int wolfPos = getAnimalPos();
    int nearestRabit = findNeareastObject(rabits, rabitHoles);
    if (nearestRabit != -1) {
        pair<int, int> toRabit = findNextMoveToObject(wolfPos, nearestRabit, rabitHoles);

        return toRabit.first;
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
