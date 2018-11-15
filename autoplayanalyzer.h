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
    const qreal alpha = 150;	//设置小鸟跳跃到管道之间的最短安全距离
    const qreal beta = 35;	//设置管道的飞行的安全高度
    const qreal delta = 10;	//设置小鸟跳出管道后安全的飞行距离
    const qreal dh = 50; //设置安全飞行高度区间 y1-y0
    const qreal lambda = 0.2; //设置均衡跳跃因子
    const qreal gamma = 50  ;//概率计算的偏移量

};

#endif // AUTOPLAYANALYZER_H
