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
    int findNeareastObject(const QVector<int> &object, const QVector<int> &obstacles);
    const pair<int, int> findNextMoveToObject(const int start, const int end, const QVector<int> &obstacles);
    const QVector<int> getAroundPlaces(const int pos);
//    virtual const int chooseNextMove(const QVector<int> &obj1, const QVector<int> &obj2, const QVector<int> &obstacles);

private:
    int animalPos;
    void addToQueue(std::priority_queue<paired, QVector<paired>, std::greater<paired> > &queue, const int pos, const int cost);
    int isObject(const QVector<int> &object, const int pos);
    int calculateCostToObject(const int start, const int end, const QVector<int> &obstacles);
};

#endif // ANIMAL_H
