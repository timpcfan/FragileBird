#include "pipe.h"


Pipe::Pipe(qreal x, qreal y, qreal w, qreal h)
{
    setPos(x, y);
    width = w;
    height = h;
    setTransformOriginPoint(w/2, h/2);

    pipePixmap = new QPixmap(":/new/images/images/pipe_up.png");
}

Pipe::~Pipe()
{
    delete pipePixmap;
}

QRectF Pipe::boundingRect() const
{
    const qreal adjust = capw + 5;
    return QRectF(0 - adjust, 0 - adjust, width + 2 * adjust, height + 2 * adjust);
}

QPainterPath Pipe::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, width, height);
    return path;
}

void Pipe::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    const qreal adjust = 5;
    painter->drawPixmap(0, 0, width, height + adjust, *pipePixmap, 0, 0, pipePixmap->width(), height + adjust);

//    auto its = this->collidingItems();
//    bool collided = false;
//    for(auto i : its)
//    {
//        if(typeid(*i) == typeid(Bird))
//            collided = true;
//    }
//    painter->setBrush(collided ? Qt::red : Qt::black);
//    painter->drawRect(0, caph, width, height - caph);
//    painter->drawRect(-capw, 0, width + 2 * capw, caph); // 画突出的盖子

}

void Pipe::setSpeed(qreal speed)
{
    xspeed = -qAbs(speed);
}

QPair<Pipe*, Pipe*> Pipe::makePairPipe(qreal gapx, qreal gapy, qreal gapw, qreal pipew)
{
    Pipe* pu = new Pipe(gapx, ROOF, pipew, gapy - ROOF);
    pu->setRotation(180);
    Pipe* pd = new Pipe(gapx, gapy + gapw , pipew, FLOOR - gapy - gapw);
    QPair<Pipe*, Pipe*> p;
    p.first = pu;
    p.second = pd;
    return p;
}

void Pipe::advance(int phase)
{
    if(phase == 0)
        return;

    if(last_time == 0){
        last_time = QDateTime::currentDateTime().toMSecsSinceEpoch();
        return;
    }

    // 移出屏幕检测
    if(x() + width + capw < 0){
        emit leavingScreen(this);
        return;
    }

    // 小鸟飞过柱子检测
    if(!isPassed && x() + width + capw < BIRD_INIT_X){
        emit birdPassed();
        isPassed = true;
    }


    // 计算经过的时间
    uint cur_time = QDateTime::currentDateTime().toMSecsSinceEpoch();
    qreal pass_time = (cur_time - last_time) / 1000.;
    last_time = cur_time;
//    qDebug() << "pass_time:" << pass_time << "; cur_pos:" << pos();

    // 计算位移
    qreal dx = xspeed * pass_time;

    // 移动
    moveBy(dx, 0);
}
