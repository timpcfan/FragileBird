#ifndef PIPE_H
#define PIPE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QPainter>
#include <QDebug>
#include <QPair>

#include <typeinfo>
#include <time.h>

#include "bird.h"
#include "game.h"

class Pipe : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Pipe();
    ~Pipe();
    Pipe(qreal x, qreal y, qreal w, qreal h);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void setSpeed(qreal speed);

    static QPair<Pipe*, Pipe*> makePairPipe(qreal gapx, qreal gapy, qreal gapw, qreal pipew);

protected:
    void advance(int phase) override;

signals:
    void leavingScreen(Pipe*);
    void birdPassed();

private:
    const qreal caph = 20;  // 管道盖子的高度
    const qreal capw = 4;   // 管道盖子边沿宽度
    qreal width;            // 管子的宽度
    qreal height;           // 管子的高度
    qreal xspeed = -250;    // 管子移动速度
    time_t last_time = 0;   // 上次更新的时间（用于速度计算）
    bool isPassed = false;
};

#endif // PIPE_H
