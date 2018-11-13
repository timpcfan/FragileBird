#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QList>
#include <QTimer>
#include <QDebug>

#include "bird.h"
#include "pipe.h"
#include "game.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene();
    ~GameScene();
    Bird *bird() const;
    QGraphicsItemGroup* pipes() const;

    void createBird();           // 生成鸟
    void createRandomPipePair(qreal speed=100, qreal gapWidth=110, qreal pipeWidth=60, qreal gapSpawnRange=400); // 随机生成管子对
    void clear();   // 清空scene
    void mainScreen();
    void gameoverScreen(int score);
    void startHint();
    void updateScoreDisplay(int score);
    GameData gatherInfomation();

signals:
    void gameover();
    void addScore();

public slots:
    void removeFromPipeGroup(Pipe *p);
    void birdClashed();
    void birdPassed();

private:

    QList<GameData::GapData> gaps; // 保存还没消亡的所有裂缝信息
    Bird* mbird = nullptr;
    QGraphicsItemGroup* pipe_group = nullptr;
    QGraphicsTextItem* scoreDisplay;
};

#endif // GAMESCENE_H
