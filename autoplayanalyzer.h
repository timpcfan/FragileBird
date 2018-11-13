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
    bool canJump(GameData data); // 是否可以

public slots:
//    void feedback(GameData data, bool result);

private:

};

#endif // AUTOPLAYANALYZER_H
