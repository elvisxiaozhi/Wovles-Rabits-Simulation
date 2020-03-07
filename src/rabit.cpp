#include "rabit.h"
#include "mainwindow.h"

using std::pair;
using std::make_pair;

Rabit::Rabit(int pos) : Animal(pos)
{

}

int Rabit::chooseNextMove(const QVector<int> &rabitFood/*, const QVector<int> &rabitHoles, const QVector<int> &wolves*/)
{
    int nearestRabitFoodPos = findNeareastObject(rabitFood);
//    int nearestWolfPos = findNeareastObject(wolves);
    int rabitPos = getAnimalPos();
    pair<int, int> toRabitFood = findNextMoveToObject(rabitPos, nearestRabitFoodPos);
//    pair<int, int> toWolf = findNextMoveToObject(rabitPos, nearestWolfPos);

//    if (toRabitFood.second < toWolf.second) {
//        return toRabitFood.first;
//    }
//    else {
//        int nearestRabitHole = findNeareastObject(rabitHoles);
//        pair<int, int> toRabitHole = findNextMoveToObject(rabitPos, nearestRabitHole);
//        if (toRabitHole.second < toWolf.second) {
//            return toRabitHole.first;
//        }
//        // TO Do 如果狼始终追得上的话
////        else {

////        }
//    }

    return toRabitFood.first;
}
