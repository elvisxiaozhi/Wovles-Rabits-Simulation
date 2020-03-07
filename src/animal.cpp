#include "animal.h"
#include "mainwindow.h"

using std::make_pair;

Animal::Animal(int pos) : animalPos(pos)
{

}

Animal::~Animal()
{

}

int Animal::getAnimalPos()
{
    return animalPos;
}

void Animal::changeAnimalPos(const int pos)
{
    animalPos = pos;
}

int Animal::findNeareastObject(const QVector<int> &object)
{
    int total = MainWindow::COLS * MainWindow::COLS;
    QVector<pair<int,int> > grassLand;
    for (int i = 0; i < total; ++i) {
        grassLand.push_back(make_pair(i, -1));
    }
    grassLand[animalPos].second = 0;

    std::priority_queue<paired, QVector<paired>, std::greater<paired> > queue;
    addToQueue(queue, animalPos, 1);
    while (queue.empty() == false) {
        int cost = queue.top().first;
        int pos = queue.top().second;
        queue.pop();
        if (grassLand[pos].second == -1) {
            grassLand[pos].second = cost;

            int index = isObject(object, pos);
            if (index != -1)
                return index;
            else
                addToQueue(queue, pos, cost + 1);
        }
    }

    return -1; // 没有找到的话返回-1
}

const pair<int, int> Animal::findNextMoveToObject(const int start, const int end)
{
    QVector<int> aroundPlaces = getAroundPlaces(start);
    int nextMove = aroundPlaces[0], minCost = INT_MAX;
    for (int i = 0; i < aroundPlaces.size(); ++i) {
        int cost = calculateCostToObject(aroundPlaces[i], end);
        if (minCost > cost) {
            minCost = cost;
            nextMove = aroundPlaces[i];
        }
    }

    return make_pair(nextMove, minCost);
}

const QVector<int> Animal::getAroundPlaces(const int pos)
{
    QVector<int> aroundPlaces;
    int row = pos / MainWindow::COLS;
    int col = pos % MainWindow::COLS;
    if (row - 1 >= 0) {
        int up = (row - 1) * MainWindow::COLS + col;
        aroundPlaces.push_back(up);
    }
    if (row + 1 < MainWindow::ROWS) {
        int down = (row + 1) * MainWindow::COLS + col;
        aroundPlaces.push_back(down);
    }
    if (col - 1 >= 0) {
        int left = row * MainWindow::COLS + col - 1;
        aroundPlaces.push_back(left);
    }
    if (col + 1 < MainWindow::COLS) {
        int right = row * MainWindow::COLS + col + 1;
        aroundPlaces.push_back(right);
    }

    return aroundPlaces;
}

void Animal::addToQueue(std::priority_queue<paired, QVector<paired>, std::greater<paired> > &queue, const int pos, const int cost)
{
    QVector<int> aroundPlaces = getAroundPlaces(pos);
    for (int i = 0; i < aroundPlaces.size(); ++i) {
        queue.push(make_pair(cost, aroundPlaces[i]));
    }
}

int Animal::isObject(const QVector<int> &object, const int pos)
{
    auto it = std::find(object.begin(), object.end(), pos);
    if (it != object.end()) {
        int index = std::distance(object.begin(), it);
        return object[index];
    }

    return -1;
}

int Animal::calculateCostToObject(const int start, const int end)
{
    int total = MainWindow::COLS * MainWindow::COLS;
    QVector<pair<int,int> > grassLand;
    for (int i = 0; i < total; ++i) {
        grassLand.push_back(make_pair(i, -1));
    }

    std::priority_queue<paired, QVector<paired>, std::greater<paired> > queue;
    queue.push(make_pair(1, start));
    addToQueue(queue, start, 2);
    while (queue.empty() == false) {
        int cost = queue.top().first;
        int pos = queue.top().second;
        queue.pop();
        if (grassLand[pos].second == -1) {
            grassLand[pos].second = cost;

            if (pos == end)
                return cost;
            else
                addToQueue(queue, pos, cost + 1);
        }
    }

    return -1;
}
