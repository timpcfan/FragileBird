#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsItem>
#include <QDateTime>

#include <typeinfo>

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
    const qreal jumpspeed = 500;            // 跳跃瞬间的速度
    const qreal baseGravity = 1500;         // 重力加速度(px/s2)
    qreal xspeed = 0;                       // x方向速度(px/s)
    qreal yspeed = 0;                       // y方向速度(px/s)
    uint last_time = 0;                     // 上次更新的时间（用于速度计算）
    qreal direction(){return 1/(1+exp(-yspeed/150. + 1)) * 90 - 45;}     // 小鸟的朝向(-45~45)
    qreal dynamicGravity(){return (1 + qAbs(yspeed)/1000) * baseGravity;} // 小鸟向下的加速度
};

#endif // BIRD_H
