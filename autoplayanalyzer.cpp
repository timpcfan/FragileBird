#include "autoplayanalyzer.h"

AutoPlayAnalyzer::AutoPlayAnalyzer()
{

}

bool AutoPlayAnalyzer::canJump(GameData data)
{
    // 在游戏中按A键打开AutoPlay效果，此时canJump函数会生效，当canJump返回true时就会跳跃，按S键可以关闭AutoPlay，此时canJump无效

    qreal y0 = data.gap.gapy + data.gap.gapw + delta;
    qreal y1 = y0 + dh;

    if(data.bird.y > y1){//底部碰撞检测
        return true;
    }
    else if(data.bird.x < data.gap.gapx - alpha  && data.bird.y > y0)//状态1 在两个柱子之间维持一个安全高度
    {
        if(rand() % 10000 < calcuP(data) * 10000)
            return true;
    }
    else if(data.bird.x > data.gap.gapx - alpha && data.bird.y > data.gap.gapy + data.gap.gapw - beta)//状态二  调整到轨道的高度区域飞行 和 状态三 在管道上面维持跳跃
    {
        return true;
    }
    return false;
}

qreal AutoPlayAnalyzer::calcuP(GameData data)
{
    qreal y0 = data.gap.gapy + data.gap.gapw + gamma;
    qreal y1 = y0 + dh;
    qreal up = data.bird.y - y0 + gamma;
    qreal down = gamma + y1 - y0;
    qreal pro = (up/down) * lambda;
    return pro;
}
