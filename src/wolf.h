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
    void savePrevMoveDir(const int prevMove, const int nextMove);

private:
    enum directions { up, down, left, right } prevMoveDir;
    int randomMoveTime = 3;
    void setRandomMoveTime();
    int chooseNextRandomMove(const int pos, const QVector<int> &obstacles);
    bool contineRandomMove();
    int isNextMoveAvailable(const int curPos, const int nextMoveDir, const QVector<int> &obstacles);
};

#endif // WOLF_H
