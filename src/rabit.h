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
    void updateHideStatus(const bool status = true);

private:
    bool isHidden = false;
};

#endif // RABIT_H
