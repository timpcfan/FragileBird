#include "bird.h"
#include <QPainter>
#include <QDebug>

Bird::Bird() : Bird(0, 0)
{

}

Bird::Bird(qreal x, qreal y)
{
    setPos(x, y);
    birdPixmap = new QPixmap(":/new/images/images/bird1_0.png");
}

QRectF Bird::boundingRect() const
{
    const qreal adjust = 5;
    return QRectF(-BirdWidth / 2 - adjust, -BirdHeight / 2 - adjust,
                  BirdWidth + 2 * adjust, BirdHeight + 2 * adjust);
}


QPainterPath Bird::shape() const
{
    QPainterPath path;
    path.addEllipse(QRectF(-BirdWidth / 2, -BirdHeight / 2,
                           BirdWidth, BirdHeight));
    return path;
}

void Bird::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-BirdWidth / 2, -BirdHeight / 2, BirdWidth, BirdHeight, *birdPixmap);
//    painter->setBrush(Qt::blue);
//    painter->drawEllipse(-BirdWidth / 2, -BirdHeight / 2, BirdWidth, BirdHeight);
}

void Bird::advance(int phase)
{
    if(phase == 0)
        return;

    if(last_time == 0){
        last_time = QDateTime::currentDateTime().toMSecsSinceEpoch();
        return;
    }

    // 碰撞检测
    for(auto i : this->collidingItems())
        if(typeid(*i) == typeid(Pipe))
            emit clashed();
    if(y() > FLOOR - BirdHeight/2 || y() < ROOF + BirdHeight/2)
        emit clashed();

    // 计算经过的时间
    uint cur_time = QDateTime::currentDateTime().toMSecsSinceEpoch();
    qreal pass_time = (cur_time - last_time) / 1000.;
    last_time = cur_time;
//    qDebug() << "pass_time:" << pass_time << "; cur_pos:" << pos() << "; yspeed:" << yspeed;

    // 计算位移
    qreal dx = xspeed * pass_time;
    qreal dy = yspeed * pass_time;

    // 计算新速度
    yspeed += dynamicGravity() * pass_time;

    // 移动
    moveBy(dx, dy);

    // 改变方向
    setRotation(direction());
}

void Bird::jump()
{
    yspeed = -jumpspeed;
}
