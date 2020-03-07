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
    int findNeareastObject(const QVector<int> &object);
    const pair<int, int> findNextMoveToObject(const int start, const int end);

private:
    int animalPos;
    virtual const QVector<int> getAroundPlaces(const int pos);
    void addToQueue(std::priority_queue<paired, QVector<paired>, std::greater<paired> > &queue, const int pos, const int cost);
    int isObject(const QVector<int> &object, const int pos);
    int calculateCostToObject(const int start, const int end);
};

#endif // ANIMAL_H
