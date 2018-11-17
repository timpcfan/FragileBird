#include "gamescene.h"

GameScene::GameScene() : QGraphicsScene()
{
    setSceneRect(0, -300, 350, 600);
    setItemIndexMethod(QGraphicsScene::NoIndex);

    pipe_group = new QGraphicsItemGroup;
    addItem(pipe_group);

    initDisplay();

    bgImage = new QImage(":/new/images/images/bg_day.png");
}

GameScene::~GameScene()
{
    delete bgImage;
}

void GameScene::drawBackground(QPainter *painter, const QRectF &)
{
    const qreal adjust = 5;
    painter->drawImage(0 - adjust, ROOF - adjust, *bgImage);
}

void GameScene::setAutoPlayTextVisable(bool visable)
{
    isAutoPlay = visable;
    autoPlayText->setVisible(isAutoPlay);
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
    qreal gapx = SCREEN_WIDTH + adjust;
    qreal gapy = - gapWidth / 2 - gapSpawnRange / 2 + (qrand() % int(gapSpawnRange));

    QPair<Pipe*, Pipe*> p = Pipe::makePairPipe(gapx, gapy, gapWidth, pipeWidth);
    p.first->setSpeed(speed);
    p.second->setSpeed(speed);
    connect(p.first, SIGNAL(leavingScreen(Pipe*)), this, SLOT(removeFromPipeGroup(Pipe*)));
    connect(p.second, SIGNAL(leavingScreen(Pipe*)), this, SLOT(removeFromPipeGroup(Pipe*)));
    connect(p.second, SIGNAL(birdPassed()), this, SLOT(birdPassed()));
    pipe_group->addToGroup(p.first);
    pipe_group->addToGroup(p.second);

    gapsAndPies.append(QPair<GameData::GapData, Pipe*>(GameData::GapData{gapx, gapy, gapWidth, pipeWidth, speed}, p.first));
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
    initDisplay();
    gapsAndPies.clear();
}

void GameScene::mainScreen()
{
    clear();
    auto p = addPixmap(QPixmap(":/new/images/images/main.png"));
    qreal adjust = 5;
    p->setPos(LEFT - adjust, ROOF - adjust);
}

void GameScene::gameoverScreen(int score, bool showHint)
{
    disableHint();
    scoreDisplay->setVisible(false);
    auto fbig = QFont(QString("Microsoft YaHei"), 32, QFont::Bold);
    auto fmiddle = QFont(QString("Microsoft YaHei"), 26, QFont::Bold);
    auto fsmall = QFont(QString("Microsoft YaHei"), 18, QFont::Bold);
    auto ftiny = QFont(QString("Microsoft YaHei"), 12, QFont::Normal);
    auto s1 = QString("游戏结束");
    auto s2 = QString("得分");
    auto s3 = QString("%1").arg(score);
    auto s4 = QString("按R键重新开始");
    putTextByCenterPos(s1, fbig, SCREEN_WIDTH / 2, -200);
    putTextByCenterPos(s2, fmiddle, SCREEN_WIDTH / 2, -120);
    putTextByCenterPos(s3, fbig, SCREEN_WIDTH / 2, -50);
    putTextByCenterPos(s4, fsmall, SCREEN_WIDTH / 2, 250);

    if(showHint){
        putTextByCenterPos(QString("游戏太难？"), ftiny, SCREEN_WIDTH / 2, 50, Qt::red);
        putTextByCenterPos(QString("按A键试试 : )"), ftiny, SCREEN_WIDTH / 2, 73, Qt::red);
    }

}

void GameScene::startHint()
{
    hintText->setVisible(true);
    QTimer* tmpTimer = new QTimer();
    tmpTimer->setSingleShot(true);
    connect(tmpTimer, SIGNAL(timeout()), this, SLOT(disableHint()));
    connect(tmpTimer, SIGNAL(timeout()), tmpTimer, SLOT(deleteLater()));
    tmpTimer->start(2000);
}

void GameScene::updateScoreDisplay(int score)
{
    auto s = QString("%1").arg(score);
    scoreDisplay->setX(-QFontMetricsF(scoreDisplay->font()).width(s)/2 + SCREEN_WIDTH/2);
    scoreDisplay->setPlainText(s);
}

GameData GameScene::gatherInfomation()
{
    GameData d;
    if(mbird)
        d.bird = mbird->getInfo();
    else
        d.bird = GameData::BirdData{};
    if(!gapsAndPies.isEmpty()){
        auto info = gapsAndPies.first();
        d.gap = info.first;
        d.gap.gapx = info.second->x();
    }else
        d.gap = GameData::GapData{};
    return d;
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

void GameScene::birdPassed()
{
    emit addScore();
    QTimer* tmpTimer = new QTimer();
    tmpTimer->setSingleShot(true);
    connect(tmpTimer, SIGNAL(timeout()), this, SLOT(handlePipePassed()));
    connect(tmpTimer, SIGNAL(timeout()), tmpTimer, SLOT(deleteLater()));
    tmpTimer->start(180);
}

void GameScene::handlePipePassed()
{
    gapsAndPies.removeFirst();
}

void GameScene::disableHint()
{
    hintText->setVisible(false);
}

void GameScene::initDisplay()
{
    scoreDisplay = new QGraphicsTextItem;
    addItem(scoreDisplay);
    scoreDisplay->setDefaultTextColor(Qt::white);
    scoreDisplay->setFont(QFont(QString("Microsoft YaHei"), 32, QFont::Bold));
    auto w = QFontMetricsF(scoreDisplay->font()).width(QString("0"));
    scoreDisplay->setPos(SCREEN_WIDTH / 2 - w / 2, ROOF);
    auto f = QFont("Microsoft YaHei", 14, QFont::Normal);
    hintText = putTextByCenterPos(QString("按空格键跳跃，躲避管道"), f, SCREEN_WIDTH / 2, 30, Qt::white);
    auto f2 = QFont("Microsoft YaHei", 12, QFont::Normal);
    autoPlayText = addText(QString("AI辅助跳跃已启动"), f2);
    autoPlayText->setPos(LEFT, ROOF);
    autoPlayText->setVisible(isAutoPlay);
    autoPlayText->setDefaultTextColor(Qt::red);
}

QGraphicsTextItem* GameScene::putTextByCenterPos(QString s, QFont &f, qreal x, qreal y, QColor color)
{
    auto m = QFontMetricsF(f);
    auto w = m.width(s);
    auto h = m.height();
    auto t = addText(s, f);
    t->setPos(x - w / 2, y - h / 2);
    t->setDefaultTextColor(color);
    return t;
}

Bird *GameScene::bird() const
{
    return mbird;
}

QGraphicsItemGroup *GameScene::pipes() const
{
    return pipe_group;
}

