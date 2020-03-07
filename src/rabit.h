#ifndef RABIT_H
#define RABIT_H

#include <QVector>
#include <queue>
#include "animal.h"

typedef std::pair<int, int> paired;

class Rabit : public Animal
{
public:
    Rabit(int pos);
    int chooseNextMove(const QVector<int> &rabitFood/*, const QVector<int> &rabitHoles, const QVector<int> &wolves*/);

private:
};

#endif // RABIT_H
