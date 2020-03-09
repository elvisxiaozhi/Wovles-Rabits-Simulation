#ifndef RABIT_H
#define RABIT_H

#include <QVector>
#include <queue>
#include "animal.h"

class Rabit : public Animal
{
public:
    Rabit(int pos);
    int chooseNextMove(const QVector<int> &rabitFood, const QVector<int> &rabitHoles, const QVector<int> &wolves);
    bool isTimeToComeOut();
    void updateHideTime();

private:
    int hideTime = 3;
};

#endif // RABIT_H
