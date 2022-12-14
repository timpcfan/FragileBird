#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QList>
#include <QTimer>
#include <QDebug>
#include <QPair>

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
    void createRandomPipePair(qreal speed=100, qreal gapWidth=110, qreal pipeWidth=68, qreal gapSpawnRange=300); // 随机生成管子对
    void clear();   // 清空scene
    void mainScreen();
    void gameoverScreen(int score, bool showHint);
    void startHint();
    void updateScoreDisplay(int score);
    void drawBackground(QPainter *painter, const QRectF & rect) override;
    void setAutoPlayTextVisable(bool visable);
    GameData gatherInfomation();


signals:
    void gameover();
    void addScore();

public slots:
    void removeFromPipeGroup(Pipe *p);
    void birdClashed();
    void birdPassed();
    void handlePipePassed();
    void disableHint();

private:

    void initDisplay();
    QGraphicsTextItem *putTextByCenterPos(QString s, QFont& f, qreal x, qreal y, QColor color=Qt::white);

    bool isAutoPlay = false;
    QList<QPair<GameData::GapData, Pipe*>> gapsAndPies; // 保存还没消亡的所有裂缝信息
    Bird* mbird = nullptr;
    QGraphicsItemGroup* pipe_group = nullptr;
    QGraphicsTextItem* scoreDisplay;
    QGraphicsTextItem* hintText;
    QGraphicsTextItem* autoPlayText;

    QImage* bgImage;
};

#endif // GAMESCENE_H
