#include "rabit.h"
#include "mainwindow.h"

Rabit::Rabit(int pos) : Animal(pos)
{

}

int Rabit::chooseNextMove(const QVector<int> &rabitFood, const QVector<int> &rabitHoles, const QVector<int> &wolves)
{
    int rabitPos = getAnimalPos();
    int layers = 3; // 为了削弱兔子的能力, 故意给了它一个检测范围, 意味着兔子只能看到周围layers层是否安全

    if (isHidden == true)
        layers = 6;

    int wolfPos = checkObjInSurroundings(rabitPos, layers, wolves); // 检测兔子周围5圈有没有狼, layers这个数视实际情况可改大或改小
    if (wolfPos == -1) { // 要是没有狼的话
        // 检测兔子周围最近的萝卜, 并去吃萝卜
        int nearestRabitFoodPos = findNeareastObject(rabitFood, wolves);
        pair<int, int> toRabitFood = findNextMoveToObject(rabitPos, nearestRabitFoodPos, wolves);

        updateHideStatus(false);

        return toRabitFood.first;
    }
    else { // 如果兔子周围有狼的话
        if (isHidden) // 如果周围5圈内还是有狼, 继续躲在兔子洞里面
            return getAnimalPos();

        // 到兔子被检测到那只狼吃掉前, 大约需要多少步, 这里没有调用calculateCostToObject()精确计算, 也是为了削弱兔子的能力
        int beforeRabitDies = layers * 10 / ((MainWindow::wolfSpeed - MainWindow::rabitSpeed) * 10);
        int nearestRabitHole = findNeareastObject(rabitHoles, wolves); // 那么此时赶紧检测最近的兔子洞
        QVector<int> obstacles = { wolfPos }; // 传参只传递现在这只狼的位置, 而不是所有狼的位置, 也是为了削弱兔子的能力
        int costToNearestRabitHole = calculateCostToObject(rabitPos, nearestRabitHole, obstacles);
        if (costToNearestRabitHole < beforeRabitDies) { // 如果在被检测到这只狼吃掉之前能跑回兔子洞
            pair<int, int> toRabitHole = findNextMoveToObject(rabitPos, nearestRabitHole, wolves); // 就赶紧跑回兔子洞

            return toRabitHole.first;
        }
        else { // 否者就往离狼远的方向跑
            QVector<int> aroundPlaces = getAroundPlaces(rabitPos, obstacles);
            int minCost = INT_MIN;
            int nextMove = aroundPlaces[0];
            for (int i = 0; i < aroundPlaces.size(); ++i) {
                int cost = calculateCostToObject(wolfPos, aroundPlaces[i], obstacles);
                if (minCost < cost) {
                    minCost = cost;
                    nextMove = aroundPlaces[i];
                }
            }

            return nextMove;
        }
    }
}

void Rabit::updateHideStatus(const bool status)
{
    isHidden = status;
}
