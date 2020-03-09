#include "wolf.h"
#include "mainwindow.h"

Wolf::Wolf(int pos) : Animal(pos), randomMoveTime(0)
{

}

int Wolf::chooseNextMove(const QVector<int> &rabits, const QVector<int> &rabitHoles)
{
    int wolfPos = getAnimalPos();

    if (contineRandomMove() == true) {
        int nextMove = chooseNextRandomMove(wolfPos, rabitHoles);
        if (nextMove != -1)
            return nextMove;
    }

    int nearestRabit = findNeareastObject(rabits, rabitHoles);
    if (nearestRabit != -1) {
        pair<int, int> toRabit = findNextMoveToObject(wolfPos, nearestRabit, rabitHoles);

        return toRabit.first;
    }

    randomMoveTime = 3;
    int nextMove = chooseNextRandomMove(wolfPos, rabitHoles);

    return nextMove;
}

bool Wolf::hasRabitEaten(QVector<Rabit *> &rabits)
{
    int wolfPos = getAnimalPos();
    for (int i = 0; i < rabits.size(); ++i) {
        if (wolfPos == rabits[i]->getAnimalPos()) {
            delete rabits[i];
            rabits.erase(rabits.begin() + i);

            return true;
        }
    }

    return false;
}

//void Wolf::savePrevMoveDir(const int prevMove, const int nextMove)
//{
//    if (prevMove - MainWindow::COLS == nextMove) {
//        prevMoveDir = up;
//    }
//    else if (prevMove + MainWindow::COLS == nextMove) {
//        prevMoveDir = down;
//    }
//    else if (prevMove - 1 == nextMove) {
//        prevMoveDir = left;
//    }
//    else if (prevMove + 1 == nextMove) {
//        prevMoveDir = right;
//    }
//}

void Wolf::setRandomMoveTime()
{
    randomMoveTime = 3;
}

int Wolf::chooseNextRandomMove(const int pos, const QVector<int> &obstacles)
{
    int nextMove = isNextMoveAvailable(pos, prevMoveDir, obstacles);
    if (nextMove != -1)
        return nextMove;

    do {
        int nextMoveDir = rand() % 4;
        nextMove = isNextMoveAvailable(pos, nextMoveDir, obstacles);
    } while (nextMove == -1);

    return nextMove;
}

bool Wolf::contineRandomMove()
{
    if (randomMoveTime > 0) {
        --randomMoveTime;

        return true;
    }

    return false;
}

int Wolf::isNextMoveAvailable(const int curPos, const int nextMoveDir, const QVector<int> &obstacles)
{
    int row = curPos / MainWindow::COLS;
    int col = curPos % MainWindow::COLS;

    int nextMove = -1;

    switch (nextMoveDir) {
    case up:
        if (row - 1 >= 0 && isObject(obstacles, curPos - MainWindow::COLS) == -1)
            nextMove = curPos - MainWindow::COLS;
        break;
    case down:
        if (row + 1 < MainWindow::ROWS && isObject(obstacles, curPos + MainWindow::COLS) == -1)
            nextMove = curPos + MainWindow::COLS;
        break;
    case left:
        if (col - 1 >= 0 && isObject(obstacles, curPos - 1) == -1)
            nextMove = curPos - 1;
        break;
    case right:
        if (col + 1 < MainWindow::COLS && isObject(obstacles, curPos + 1) == -1)
            nextMove = curPos + 1;
        break;
    default:
        break;
    }

    return nextMove;
}
