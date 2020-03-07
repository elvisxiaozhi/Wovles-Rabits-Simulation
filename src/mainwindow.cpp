#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(nullptr));
    createGrassLand();
    generateRabitHoles();
    generateRabitFood(); //注意此函数在generateRabitHoles()之后调用
    generateRabits(1); //注意此函数在generateRabitHoles()之后调用

    timer = new QTimer(this);
    timer->start(200);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeOut);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGrassLand()
{
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            QLabel *lbl = new QLabel(this);
            lbl->setFixedSize(30, 30);
            lbl->setAlignment(Qt::AlignCenter);

            lbl->setText(QString::number(i * 20 + j));

            lbl->setStyleSheet("QLabel { background-color: #00ff00; border: 1px solid gray; }");

            ui->gridLayout->addWidget(lbl, i, j);

            grasslandVec.push_back(lbl);
        }
    }
}

void MainWindow::generateRabitHoles(int rabitHolesNum)
{
    // 当输入小于等于0或者大于10的时候，判定为非法输入，使用默认值3
    if (rabitHolesNum <= 0 || rabitHolesNum > 10) {
        //TO DO 提示非法输入
        rabitHolesNum = 3;
    }

    rabitHoles.clear();
    while (rabitHoles.size() < rabitHolesNum) {
        int random = rand() % (ROWS * COLS);
        if (std::find(rabitHoles.begin(), rabitHoles.end(), random) == rabitHoles.end()) {
            rabitHoles.push_back(random);

            grasslandVec[random]->setStyleSheet("QLabel { background-color: black; border: 1px solid gray; }");
        }
    }
}

void MainWindow::generateRabitFood(int rabitFoodNum)
{
    // 当输入小于等于0或者大于30的时候，判定为非法输入，使用默认值3
    if (rabitFoodNum <= 0 || rabitFoodNum >= 30) {
        //TO DO 提示非法输入
        rabitFoodNum = 10;
    }

    rabitFood.clear();
    while (rabitFood.size() < rabitFoodNum) {
        int random = rand() % (ROWS * COLS);
        if (std::find(rabitHoles.begin(), rabitHoles.end(), random) == rabitHoles.end() &&
                std::find(rabitFood.begin(), rabitFood.end(), random) == rabitFood.end()) {
            rabitFood.push_back(random);

            grasslandVec[random]->setStyleSheet("QLabel { background-color: yellow; border: 1px solid gray; }");
        }
    }
}

void MainWindow::generateRabits(int rabitNum)
{
    if (rabitNum <= 0) {
        rabitNum = 3;
    }

    for (int i = 0; i < rabits.size(); ++i) {
        delete rabits[i];
    }
    rabits.clear();

    for (int i = 0; i < rabitNum; ++i) {
        int rabitHole = rand() % rabitHoles.size();
        Rabit *rabit = new Rabit(rabitHoles[rabitHole]);
        rabits.push_back(rabit);
    }
}

void MainWindow::moveRabit(Rabit *rabit)
{
    int rabitPos = rabit->getAnimalPos();
    int row = rabitPos / COLS;
    int col = rabitPos % COLS;

    switch (rabitDir) {
    case Up:
        --row;
        break;
    case Down:
        ++row;
        break;
    case Left:
        --col;
        break;
    case Right:
        ++col;
        break;
    default:
        break;
    }

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        /* 判断兔子移动前的为止是不是兔子洞
         * 是兔子洞的话，则把这个为止设置成黑色
         * 否则设置成草地的颜色绿色 */
        if (isRabitHole(rabitPos)) {
            grasslandVec[rabitPos]->setStyleSheet("QLabel { background-color: black; border: 1px solid gray; }");
        }
        else {
            grasslandVec[rabitPos]->setStyleSheet("QLabel { background-color: #00ff00; border: 1px solid gray; }");
        }

        rabitPos = row * COLS + col;

        int index = isRabitFood(rabitPos); //判断兔子的下一个移动点有没有食物
        if (index != -1) {
            rabitFood.erase(rabitFood.begin() + index); //如果有食物，则这个食物被兔子吃掉，并把它从数组中移除
        }

        grasslandVec[rabitPos]->setStyleSheet("QLabel { background-color: pink; border: 1px solid gray; }"); //pink暂时代表兔子

        rabit->changeAnimalPos(rabitPos);
    }

//    int index = rabit->findNeareastObject(rabitFood);
    //    grasslandVec[index]->setStyleSheet("QLabel { background-color: purple; border: 1px solid gray; }");
}

void MainWindow::moveRabit(Rabit *rabit, const int nextMove)
{
    /* 判断兔子移动前的为止是不是兔子洞
     * 是兔子洞的话，则把这个为止设置成黑色
     * 否则设置成草地的颜色绿色 */
    int rabitPos = rabit->getAnimalPos();
    if (isRabitHole(rabitPos)) {
        grasslandVec[rabitPos]->setStyleSheet("QLabel { background-color: black; border: 1px solid gray; }");
    }
    else {
        grasslandVec[rabitPos]->setStyleSheet("QLabel { background-color: #00ff00; border: 1px solid gray; }");
    }

    int index = isRabitFood(nextMove); //判断兔子的下一个移动点有没有食物
    if (index != -1) {
        rabitFood.erase(rabitFood.begin() + index); //如果有食物，则这个食物被兔子吃掉，并把它从数组中移除
    }

    grasslandVec[nextMove]->setStyleSheet("QLabel { background-color: pink; border: 1px solid gray; }"); //pink暂时代表兔子

    rabit->changeAnimalPos(nextMove);
}

bool MainWindow::isRabitHole(const int pos)
{
    if (std::find(rabitHoles.begin(), rabitHoles.end(), pos) != rabitHoles.end()) {
        return true;
    }

    return false;
}

/* 判断兔子下一个移动点有没有食物
 * 有的话则返回这个食物在rabitFood数组中的index, 便于后续移除该元素使用
 * 没有的话则返回0 */
int MainWindow::isRabitFood(const int pos)
{
    auto it = std::find(rabitFood.begin(), rabitFood.end(), pos);
    if (it != rabitFood.end()) {
        return std::distance(rabitFood.begin(), it);
    }

    return -1;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        rabitDir = Up;
        moveRabit(rabits[0]);
        break;
    case Qt::Key_S:
        rabitDir = Down;
        moveRabit(rabits[0]);
        break;
    case Qt::Key_A:
        rabitDir = Left;
        moveRabit(rabits[0]);
        break;
    case Qt::Key_D:
        rabitDir = Right;
        moveRabit(rabits[0]);
        break;
    case Qt::Key_1:

        break;
    case Qt::Key_Up:

        break;
    case Qt::Key_Down:

        break;
    case Qt::Key_Left:

        break;
    case Qt::Key_Right:

        break;
    case Qt::Key_L:

        break;
    default:
        break;
    }
}

void MainWindow::onTimerTimeOut()
{
    QVector<int> wolves = {0};
    int nextMove = rabits[0]->chooseNextMove(rabitFood/*, rabitHoles, wolves*/);

    moveRabit(rabits[0], nextMove);
}





