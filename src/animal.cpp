#include "animal.h"
#include "mainwindow.h"
#include <QQueue>

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

void Animal::savePrevMoveDir(const int prevMove, const int nextMove)
{
    if (prevMove - MainWindow::COLS == nextMove) {
        prevMoveDir = up;
    }
    else if (prevMove + MainWindow::COLS == nextMove) {
        prevMoveDir = down;
    }
    else if (prevMove - 1 == nextMove) {
        prevMoveDir = left;
    }
    else if (prevMove + 1 == nextMove) {
        prevMoveDir = right;
    }
}

int Animal::findNeareastObject(const QVector<int> &objects, const QVector<int> &obstacles)
{
    QVector<pair<int, bool> > grassLand = initGrassLand();
    grassLand[animalPos].second = true;

    std::priority_queue<paired, QVector<paired>, std::greater<paired> > queue;
    addToQueue(queue, animalPos, 1, obstacles);
    while (queue.empty() == false) {
        int cost = queue.top().first;
        int pos = queue.top().second;
        queue.pop();
        if (grassLand[pos].second == false) {
            grassLand[pos].second = true;

            int index = isObject(objects, pos);
            if (index != -1)
                return index;

            addToQueue(queue, pos, cost + 1, obstacles);
        }
    }

    return -1; // 没有找到的话返回-1
}

const pair<int, int> Animal::findNextMoveToObject(const int start, const int end, const QVector<int> &obstacles)
{
    QVector<int> aroundPlaces = getAroundPlaces(start, obstacles);
    int nextMove = aroundPlaces[0], minCost = INT_MAX;
    for (int i = 0; i < aroundPlaces.size(); ++i) {
        int cost = calculateCostToObject(aroundPlaces[i], end, obstacles);
        if (minCost > cost) {
            minCost = cost;
            nextMove = aroundPlaces[i];
        }
    }

    return make_pair(nextMove, minCost);
}

const QVector<int> Animal::getAroundPlaces(const int pos, const QVector<int> &obstacles)
{
    QVector<int> aroundPlaces;
    int row = pos / MainWindow::COLS;
    int col = pos % MainWindow::COLS;
    if (row - 1 >= 0) {
        int up = (row - 1) * MainWindow::COLS + col;
        if (isObject(obstacles, up) == -1)
            aroundPlaces.push_back(up);
    }
    if (row + 1 < MainWindow::ROWS) {
        int down = (row + 1) * MainWindow::COLS + col;
        if (isObject(obstacles, down) == -1)
            aroundPlaces.push_back(down);
    }
    if (col - 1 >= 0) {
        int left = row * MainWindow::COLS + col - 1;
        if (isObject(obstacles, left) == -1)
            aroundPlaces.push_back(left);
    }
    if (col + 1 < MainWindow::COLS) {
        int right = row * MainWindow::COLS + col + 1;
        if (isObject(obstacles, right) == -1)
            aroundPlaces.push_back(right);
    }

    return aroundPlaces;
}

int Animal::checkObjInSurroundings(const int pos, int layers, const QVector<int> &objects)
{
    QVector<pair<int, bool> > grassland = initGrassLand();
    grassland[pos].second = true;

    QVector<int> aroundPlaces = getAroundPlaces(pos);
    QQueue<int> queue;
    for (int i = 0; i < aroundPlaces.size(); ++i) {
        queue.push_back(aroundPlaces[i]);
    }

    while (layers > 0) {
        int n = queue.size();
        while (n > 0) {
            int curPos = queue.front();
            queue.pop_front();
            --n;

            if (grassland[curPos].second == false) {
                grassland[curPos].second = true;

                int index = isObject(objects, curPos);
                if (index != -1) {
                    return index;
                }

                QVector<int> tmp = getAroundPlaces(curPos);
                for (int i = 0; i < tmp.size(); ++i) {
                    queue.push_back(tmp[i]);
                }
            }
        }

        --layers;
    }

    return -1;
}

void Animal::addToQueue(std::priority_queue<paired, QVector<paired>, std::greater<paired> > &queue, const int pos, const int cost, const QVector<int> &obstacles)
{
    QVector<int> aroundPlaces = getAroundPlaces(pos, obstacles);
    for (int i = 0; i < aroundPlaces.size(); ++i) {
        queue.push(make_pair(cost, aroundPlaces[i]));
    }
}

int Animal::isObject(const QVector<int> &objects, const int pos)
{
    auto it = std::find(objects.begin(), objects.end(), pos);
    if (it != objects.end()) {
        int index = std::distance(objects.begin(), it);
        return objects[index];
    }

    return -1;
}

int Animal::calculateCostToObject(const int start, const int end, const QVector<int> &obstacles)
{
    QVector<pair<int, bool> > grassLand = initGrassLand();

    std::priority_queue<paired, QVector<paired>, std::greater<paired> > queue;
    queue.push(make_pair(1, start));
    addToQueue(queue, start, 2, obstacles);
    while (queue.empty() == false) {
        int cost = queue.top().first;
        int pos = queue.top().second;
        queue.pop();
        if (grassLand[pos].second == false) {
            grassLand[pos].second = true;

            if (pos == end)
                return cost;
            else
                addToQueue(queue, pos, cost + 1, obstacles);
        }
    }

    return -1;
}

const QVector<pair<int, bool> > Animal::initGrassLand()
{
    int total = MainWindow::COLS * MainWindow::COLS;
    QVector<pair<int, bool> > grassLand;
    for (int i = 0; i < total; ++i) {
        grassLand.push_back(make_pair(i, false));
    }

    return grassLand;
}
