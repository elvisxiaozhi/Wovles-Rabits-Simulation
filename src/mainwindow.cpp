#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(nullptr));

    setUpEnviroment(7, 10, 1);
    setUpTimer();
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
            lbl->setStyleSheet("QLabel { background-color: #00ff00; border: 1px solid gray; }");

            ui->gridLayout->addWidget(lbl, i, j);

            grasslandVec.push_back(lbl);
        }
    }
}

void MainWindow::generateRabitHoles(int rabitHoleNum)
{
    // 当输入小于等于0或者大于10的时候，判定为非法输入，使用默认值3
    if (rabitHoleNum <= 0 || rabitHoleNum > 10) {
        //TO DO 提示非法输入
        rabitHoleNum = 3;
    }

    rabitHoles.clear();
    while (rabitHoles.size() < rabitHoleNum) {
        int random = rand() % (ROWS * COLS);
        if (std::find(rabitHoles.begin(), rabitHoles.end(), random) == rabitHoles.end()) {
            rabitHoles.push_back(random);

            grasslandVec[random]->setPixmap(QPixmap(":/icons/hole.png"));
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

            grasslandVec[random]->setPixmap(QPixmap(":/icons/carrot.png"));
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
        Rabit *rabit = new Rabit(rabitHoles[i]);
        rabits.push_back(rabit);

        grasslandVec[rabit->getAnimalPos()]->setPixmap(QPixmap(":/icons/hidden-rabbit.png"));
    }
}

void MainWindow::generateWolves(int wolfNum)
{
    if (wolfNum <= 0) {
        wolfNum = 3;
    }

    for (int i = 0; i < wolves.size(); ++i) {
        delete wolves[i];
    }
    wolves.clear();

    QVector<int> wolfPos;
    while (wolves.size() < wolfNum) {
        int random = rand() % (ROWS * COLS);
        if (std::find(rabitHoles.begin(), rabitHoles.end(), random) == rabitHoles.end() &&
                std::find(rabitFood.begin(), rabitFood.end(), random) == rabitFood.end() &&
                std::find(wolfPos.begin(), wolfPos.end(), random) == wolfPos.end()) {
            Wolf *wolf = new Wolf(random);
            wolves.push_back(wolf);
            wolfPos.push_back(random);

            grasslandVec[random]->setPixmap(QPixmap(":/icons/wolf.png"));

        }
    }
}

void MainWindow::setUpEnviroment(int rabitHoleNum, int rabitFoodNum, int wolfNum)
{
    createGrassLand();
    //注意： 后面几个函数调用的先后顺序不能错
    generateRabitHoles(rabitHoleNum);
    generateRabitFood(rabitFoodNum);
    generateRabits(rabitHoleNum);
    generateWolves(wolfNum);
}

void MainWindow::setUpTimer()
{
    rabitTimer = new QTimer(this);
    rabitTimer->start(300);
    connect(rabitTimer, &QTimer::timeout, this, &MainWindow::onRabitMove);

    wolfTimer = new QTimer(this);
    wolfTimer->start(200);
    connect(wolfTimer, &QTimer::timeout, this, &MainWindow::onWolfMove);
}

void MainWindow::moveRabit(Rabit *rabit, const int nextMove)
{
    int rabitPos = rabit->getAnimalPos();
    int index = isObject(rabitFood, nextMove); //判断兔子的下一个移动点有没有食物
    if (index != -1) {
        rabitFood.erase(rabitFood.begin() + index); //如果有食物，则这个食物被兔子吃掉，并把它从数组中移除
        grasslandVec[rabitPos]->setPixmap(QPixmap());
    }
    else {
        grasslandVec[rabitPos]->setPixmap(QPixmap(":/icons/rabbit.png"));
    }

    if (isObject(rabitHoles, rabitPos) != -1) {
        grasslandVec[rabitPos]->setPixmap(QPixmap(":/icons/hole.png"));
    }
    else {
        grasslandVec[rabitPos]->setPixmap(QPixmap());
    }

    if (isObject(rabitHoles, nextMove) != -1) {
        rabit->updateHideStatus(true);

        grasslandVec[nextMove]->setPixmap(QPixmap(":/icons/hidden-rabbit.png"));
    }
    else {
        grasslandVec[nextMove]->setPixmap(QPixmap(":/icons/rabbit.png"));
    }

    rabit->changeAnimalPos(nextMove);

    if (isGameOver() == 1) {
        rabitTimer->stop();
        wolfTimer->stop();
        qDebug() << "Rabit Won";
    }
}

void MainWindow::moveWolf(Wolf *wolf, const int nextMove)
{
    int wolfPos = wolf->getAnimalPos();
    wolf->savePrevMoveDir(wolfPos, wolfPos);

    if (isObject(rabitFood, wolfPos) != -1) {
        grasslandVec[wolfPos]->setPixmap(QPixmap());
    }
    else {
        grasslandVec[wolfPos]->setPixmap(QPixmap(":/icons/rabit.png"));
    }

    wolf->changeAnimalPos(nextMove);
    grasslandVec[nextMove]->setPixmap(QPixmap(":/icons/wolf.png"));

    wolf->hasRabitEaten(rabits);

    if (isGameOver() == 2) {
        rabitTimer->stop();
        wolfTimer->stop();
        qDebug() << "Wolf Won";
    }
}

int MainWindow::isObject(const QVector<int> &object, const int pos)
{
    auto it = std::find(object.begin(), object.end(), pos);
    if (it != object.end()) {
        return std::distance(object.begin(), it);
    }

    return -1;
}

int MainWindow::isGameOver()
{
    if (rabitFood.empty())
        return 1;
    if (rabits.empty())
        return 2;

    return 0;
}

template <class Object>
const QVector<int> MainWindow::getObjectPos(const QVector<Object *> &object)
{
    QVector<int> pos;
    for (int i = 0; i < object.size(); ++i) {
        pos.push_back(object[i]->getAnimalPos());
    }

    return pos;
}

void MainWindow::onRabitMove()
{
    QVector<int> wolfPos = getObjectPos(wolves);
    for (int i = 0; i < rabits.size(); ++i) {
        int nextMove = rabits[i]->chooseNextMove(rabitFood, rabitHoles, wolfPos);

        for (int j = 0; j < rabits.size(); ++j) {
            if (j != i && nextMove == rabits[j]->getAnimalPos()) {
                QVector<int> obstacles = getObjectPos(rabits);
                QVector<int> aroundPlaces = rabits[i]->getAroundPlaces(rabits[i]->getAnimalPos(), obstacles);
                nextMove = aroundPlaces[rand() % aroundPlaces.size()];

                break;
            }
        }

        moveRabit(rabits[i], nextMove);
    }
}

void MainWindow::onWolfMove()
{
    QVector<int> rabitPos = getObjectPos(rabits);
    QVector<int> wolfPos = getObjectPos(wolves);
    QVector<int> obstacles = rabitHoles;
    for (int i = 0; i < wolfPos.size(); ++i) {
        obstacles.push_back(wolfPos[i]);
    }

    for (int i = 0; i < wolves.size(); ++i) {
        int nextMove = wolves[i]->chooseNextMove(rabitPos, obstacles);
        obstacles.push_back(nextMove);

        if (nextMove == -1)
            moveWolf(wolves[i], wolves[i]->getAnimalPos());
        else
            moveWolf(wolves[i], nextMove);
    }
}
