#ifndef AUTOPLAYANALYZER_H
#define AUTOPLAYANALYZER_H

#include <QObject>
#include <QDebug>
#include "bird.h"
#include "pipe.h"
#include "game.h"


/**
 * @brief 自动游戏分析器
 */
class AutoPlayAnalyzer : public QObject
{
    Q_OBJECT

public:
    AutoPlayAnalyzer();
    bool canJump(GameData data); // 根据游戏信息判断是否可以跳跃
    qreal calcuP(GameData data);//实现跳跃的自然计算在跳跃区跳跃的概率

private:
    const qreal alpha = 130;	//设置小鸟跳跃到管道之间的最短安全距离
    const qreal beta = 35;	//设置管道的飞行的安全高度
    const qreal delta = 20;	//设置小鸟默认跳跃高度与间隙下沿的高度差
    const qreal dh = 30; //设置安全飞行高度区间 y1-y0
    const qreal lambda = 0.3; //设置均衡跳跃因子
    const qreal gamma = 70  ;//概率计算的偏移量

};

#endif // AUTOPLAYANALYZER_H
