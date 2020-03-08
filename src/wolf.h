#ifndef WOLF_H
#define WOLF_H

#include "animal.h"
#include "rabit.h"

class Wolf : public Animal
{
public:
    Wolf(int pos);
    int chooseNextMove(const QVector<int> &rabits, const QVector<int> &rabitFood, const QVector<int> &rabitHoles);
    bool hasRabitEaten(QVector<Rabit *> &rabits);

private:
};

#endif // WOLF_H
