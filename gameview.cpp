#include "gameview.h"

GameView::GameView(GameScene *gs) : QGraphicsView(gs)
{
    gscene = gs;

    setRenderHint(QPainter::Antialiasing);
//    setBackgroundBrush(...);
//    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setWindowTitle(QString("易碎小鸟"));
    resize(355, 605);

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
}

GameView::~GameView()
{
    delete animateTimer;
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
        gscene->bird()->jump();
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

    gscene->createRandomPipePair(pipeSpeed, pipeGapWidth);
    return true;
}

void GameView::gameAdvance()
{
    if(!isStart)
        return;
    gscene->advance();
}

void GameView::startGame()
{
    gscene->createBird();
    isStart = true;
    isMainScreen = false;
    gscene->startHint();
    gscene->updateScoreDisplay(score);
}

void GameView::stopGame()
{
    gscene->gameoverScreen(score);
    isStart = false;
}

void GameView::addScore()
{
    score++;
    gscene->updateScoreDisplay(score);
}
