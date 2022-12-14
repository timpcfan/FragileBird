#ifndef GAMEVIEW_H
#define GAMEVIEW_H
//u
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QIcon>

#include "gamescene.h"
#include "bird.h"
#include "pipe.h"
#include "game.h"
#include "autoplayanalyzer.h"

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(GameScene *scene);
    ~GameView();
    GameData getAllData();

    void restart();

protected:
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    bool spawnPipePair();
    void gameAdvance();
    void startGame();
    void stopGame();
    void addScore();

private:
    qreal spawnInterval = 1500; // 管子生成间隔(ms)
    qreal pipeWidth = 80;       // 管子的宽度(px)
    qreal gapSpawnRange = 300;  // 间隙生成的区间(px)
    qreal pipeGapWidth = 120;   // 上下管子间开口宽度(px)
    qreal pipeSpeed = 180;      // 管子移动速度(px/s)

    bool isStart = false; // 游戏是否开始
    bool isMainScreen = false; // 是否在开始界面
    bool isAutoPlay = false;  // 是否开启自动跳跃
    bool isLearning = false;  // 是否为学习模式

    GameScene* gscene;
    QTimer* animateTimer;
    QTimer* pipeGenerateTimer;
    const int fps = 60;
    int score = 0;
    int deadCount = 0;

    AutoPlayAnalyzer *analyzer;
};

#endif // GAMEVIEW_H
