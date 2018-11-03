#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsItem>

#include <typeinfo>
#include <time.h>

#include "game.h"
#include "math.h"
#include "pipe.h"

class Bird : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Bird();
    Bird(qreal x, qreal y);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void advance(int phase) override;

signals:
    void clashed();

public slots:
    void jump();

private:
    enum {BirdWidth = 36, BirdHeight = 30}; // 小鸟的宽高
    const qreal jumpspeed = 500;    // 跳跃瞬间的速度
    const qreal gravity = 1000;     // 重力加速度(px/s2)
    qreal xspeed = 0;               // x方向速度(px/s)
    qreal yspeed = 0;               // y方向速度(px/s)
    time_t last_time = 0;           // 上次更新的时间（用于速度计算）
    qreal direction(){return 1/(1+exp(-yspeed/150. + 1)) * 170 - 85;}     // 小鸟的朝向(-90~90)
};

#endif // BIRD_H
