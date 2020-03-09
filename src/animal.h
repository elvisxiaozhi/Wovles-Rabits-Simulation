#ifndef ANIMAL_H
#define ANIMAL_H

#include <QVector>
#include <queue>

using std::pair;

typedef std::pair<int, int> paired;

class Animal
{
public:
    Animal(int pos);
    virtual ~Animal();
    int getAnimalPos();
    void changeAnimalPos(const int pos);
//    enum directions { up, down, left, right } prevMoveDir;
//    void savePrevMoveDir(const int prevMove, const int nextMove);
    int findNeareastObject(const QVector<int> &objects, const QVector<int> &obstacles);
    const pair<int, int> findNextMoveToObject(const int start, const int end, const QVector<int> &obstacles);
    const QVector<int> getAroundPlaces(const int pos, const QVector<int> &obstacles = QVector<int>());
    int checkObjInSurroundings(const int pos, int layers, const QVector<int> &objects);
    int calculateCostToObject(const int start, const int end, const QVector<int> &obstacles = QVector<int>());
    int isObject(const QVector<int> &objects, const int pos);

private:
    int animalPos;
    void addToQueue(std::priority_queue<paired, QVector<paired>, std::greater<paired> > &queue, const int pos, const int cost, const QVector<int> &obstacles = QVector<int>());
    const QVector<pair<int, bool> > initGrassLand();
};

#endif // ANIMAL_H
