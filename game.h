#ifndef GAME_H
#define GAME_H

#include <QDebug>

enum COORD {FLOOR = 300, ROOF = -300, LEFT = 0, RIGHT = 350, SCREEN_HEIGHT = 600, SCREEN_WIDTH = 350};

const qreal BIRD_INIT_X = 70;
const qreal BIRD_INIT_Y = 0;
const QString fmt = QString("bird.birdWidth=%1\nbird.birdHeight=%2\nbird.jumpspeed=%3\nbird.baseGravity=%4\nbird.xspeed=%5\nbird.yspeed=%6\nbird.direction=%7\nbird.dynamicGravity=%8\nbird.x=%9\nbird.y=%10\ngap.gapx=%11\ngap.gapy=%12\ngap.gapw=%13\ngap.pipew=%14\ngap.gapSpeed=%15\ngame.pipeSpawnInterval=%16");

/**
 * @brief 游戏数据信息
 */
struct GameData
{
    struct BirdData{
        qreal birdWidth;   // 鸟身的宽度
        qreal birdHeight;  // 鸟身的高度
        qreal jumpspeed;   // 跳跃速度
        qreal baseGravity; // 基础加速度
        qreal xspeed;      // x轴速度（恒为0）
        qreal yspeed;      // y轴速度
        qreal direction;   // 朝向（角度）
        qreal dynamicGravity; // 当前真实加速度
        qreal x;  // 鸟的x坐标
        qreal y;  // 鸟的y坐标
    } bird; // 鸟的相关数据

    struct GapData{
        qreal gapx;  // 裂口左上角x坐标
        qreal gapy;  // 裂口左上角y坐标
        qreal gapw;  // 裂口宽度(大小）
        qreal pipew; // 管子宽度
        qreal gapSpeed; // 管子移动速度
    } gap; // 当前裂口的数据（鸟即将跳过的下一对柱子的裂口）

    struct GameSetting{
        qreal pipeSpawnInterval; // 管子生成间隔(ms)
    } game;

    QString text() {
        return fmt.arg(bird.birdWidth)
                    .arg(bird.birdHeight)
                    .arg(bird.jumpspeed)
                    .arg(bird.baseGravity)
                    .arg(bird.xspeed)
                    .arg(bird.yspeed)
                    .arg(bird.direction)
                    .arg(bird.dynamicGravity)
                    .arg(bird.x)
                    .arg(bird.y)
                    .arg(gap.gapx)
                    .arg(gap.gapy)
                    .arg(gap.gapw)
                    .arg(gap.pipew)
                    .arg(gap.gapSpeed)
                    .arg(game.pipeSpawnInterval);
    }

    // 显示内容;
    void display(){

        qDebug() << "************GameData************";
        qDebug() << "bird.birdWidth=" << bird.birdWidth;
        qDebug() << "bird.birdHeight=" << bird.birdHeight;
        qDebug() << "bird.jumpspeed=" << bird.jumpspeed;
        qDebug() << "bird.baseGravity=" << bird.baseGravity;
        qDebug() << "bird.xspeed=" << bird.xspeed;
        qDebug() << "bird.yspeed=" << bird.yspeed;
        qDebug() << "bird.direction=" << bird.direction;
        qDebug() << "bird.dynamicGravity=" << bird.dynamicGravity;
        qDebug() << "bird.x=" << bird.x;
        qDebug() << "bird.y=" << bird.y;
        qDebug() << "gap.gapx=" << gap.gapx;
        qDebug() << "gap.gapy=" << gap.gapy;
        qDebug() << "gap.gapw=" << gap.gapw;
        qDebug() << "gap.pipew=" << gap.pipew;
        qDebug() << "gap.gapSpeed=" << gap.gapSpeed;
        qDebug() << "game.pipeSpawnInterval=" << game.pipeSpawnInterval;
        qDebug() << "***************END**************";
    }
};

#endif // GAME_H
