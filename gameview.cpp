#include "gameview.h"

GameView::GameView(GameScene *gs) : QGraphicsView(gs)
{
    gscene = gs;

    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setWindowTitle(QString("易碎小鸟"));
    setFixedSize(355, 605);

    animateTimer = new QTimer(this);
    connect(animateTimer, SIGNAL(timeout()), this, SLOT(gameAdvance()));
    animateTimer->start(1000 / fps);

    pipeGenerateTimer = new QTimer(this);
    connect(pipeGenerateTimer, SIGNAL(timeout()), this, SLOT(spawnPipePair()));
    pipeGenerateTimer->start(spawnInterval);

    connect(gscene, SIGNAL(gameover()), this, SLOT(stopGame()));
    connect(gscene, SIGNAL(addScore()), this, SLOT(addScore()));

    gscene->mainScreen();
    isMainScreen = true;

    // 自动跳跃分析器
    analyzer = new AutoPlayAnalyzer();
}

GameView::~GameView()
{
    delete animateTimer;
    delete pipeGenerateTimer;
    delete analyzer;
}

GameData GameView::getAllData()
{
    GameData data = gscene->gatherInfomation();
    data.game = GameData::GameSetting{spawnInterval};
    return data;
}

void GameView::restart()
{
    gscene->clear();
    score = 0;
    startGame();
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
        if(isMainScreen){
            restart();
            break;
        }
        if(isStart)
            gscene->bird()->jump();
        break;
    case Qt::Key_A:
        if(deadCount <= 3)
            break;
        isAutoPlay = true;
        gscene->setAutoPlayTextVisable(true);
        break;
    case Qt::Key_S:
        gscene->setAutoPlayTextVisable(false);
        isAutoPlay = false;
        break;
    case Qt::Key_R:
        restart();
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

bool GameView::spawnPipePair()
{
    if(!isStart)
        return false;

    gscene->createRandomPipePair(pipeSpeed, pipeGapWidth, pipeWidth, gapSpawnRange);
    return true;
}

void GameView::gameAdvance()
{
    if(!isStart)
        return;
    gscene->advance();
    if(isAutoPlay && analyzer->canJump(getAllData()))
        gscene->bird()->jump();
}

void GameView::startGame()
{
    gscene->createBird();
    isStart = true;
    isMainScreen = false;
    gscene->startHint();
    gscene->updateScoreDisplay(score);
    pipeGenerateTimer->start(spawnInterval);
}

void GameView::stopGame()
{
    isStart = false;
    deadCount ++;
    gscene->gameoverScreen(score, deadCount > 3);
}

void GameView::addScore()
{
    score++;
    gscene->updateScoreDisplay(score);
}
