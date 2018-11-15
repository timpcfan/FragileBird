#include "gamescene.h"

GameScene::GameScene() : QGraphicsScene()
{
    setSceneRect(0, -300, 350, 600);
    setItemIndexMethod(QGraphicsScene::NoIndex);

    pipe_group = new QGraphicsItemGroup;
    addItem(pipe_group);

    scoreDisplay = new QGraphicsTextItem;
    scoreDisplay->setPos(LEFT, ROOF);
    addItem(scoreDisplay);
}

GameScene::~GameScene()
{

}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawImage(0, ROOF, QImage(":/new/images/images/bg_day.png"));
}

void GameScene::createBird()
{
    mbird = new Bird(BIRD_INIT_X, BIRD_INIT_Y);
    connect(mbird, SIGNAL(clashed()), this, SLOT(birdClashed()));
    addItem(mbird);
}

void GameScene::createRandomPipePair(qreal speed, qreal gapWidth, qreal pipeWidth, qreal gapSpawnRange)
{
    const qreal adjust = 30;
    QPair<Pipe*, Pipe*> p = Pipe::makePairPipe(SCREEN_WIDTH + adjust,
                                               - gapWidth / 2 - gapSpawnRange / 2 + (qrand() % int(gapSpawnRange)),
                                               gapWidth, pipeWidth);
    p.first->setSpeed(speed);
    p.second->setSpeed(speed);
    connect(p.first, SIGNAL(leavingScreen(Pipe*)), this, SLOT(removeFromPipeGroup(Pipe*)));
    connect(p.second, SIGNAL(leavingScreen(Pipe*)), this, SLOT(removeFromPipeGroup(Pipe*)));
    connect(p.second, SIGNAL(birdPassed()), this, SIGNAL(addScore()));
    pipe_group->addToGroup(p.first);
    pipe_group->addToGroup(p.second);
}

void GameScene::clear()
{
    if(mbird){
        removeItem(mbird);
        delete mbird;
        mbird = nullptr;
    }
    removeItem(pipe_group);
    delete pipe_group;
    removeItem(scoreDisplay);
    delete scoreDisplay;
    QGraphicsScene::clear();
    pipe_group = new QGraphicsItemGroup;
    addItem(pipe_group);
    scoreDisplay = new QGraphicsTextItem;
    scoreDisplay->setPos(LEFT, ROOF);
    addItem(scoreDisplay);
}

void GameScene::mainScreen()
{
    clear();
    auto t = addText(QString("按空格键开始游戏"));
    t->setPos(100, 0);
}

void GameScene::gameoverScreen(int score)
{
    char* s = new char[100];
    sprintf(s, "游戏结束，最终得分：%d，按R键重新开始", score);
    auto t = addText(QString(s));
    t->setPos(100, 0);
}

void GameScene::startHint()
{
    QTimer* tmpTimer = new QTimer();
    tmpTimer->setSingleShot(true);
    auto t = addText(QString("按空格键跳跃，避开水管"));
    t->setPos(100, 0);
    connect(tmpTimer, SIGNAL(timeout()), t, SLOT(deleteLater()));
    connect(tmpTimer, SIGNAL(timeout()), tmpTimer, SLOT(deleteLater()));
    tmpTimer->start(2000);
}

void GameScene::updateScoreDisplay(int score)
{
    char* s = new char[100];
    sprintf(s, "分数:%d", score);
    scoreDisplay->setPlainText(QString(s));
}

void GameScene::removeFromPipeGroup(Pipe *p)
{
    pipe_group->removeFromGroup(p);
    delete p;
}

void GameScene::birdClashed()
{
    emit gameover();
}

Bird *GameScene::bird() const
{
    return mbird;
}

QGraphicsItemGroup *GameScene::pipes() const
{
    return pipe_group;
}

