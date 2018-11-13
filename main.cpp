/* 这是一个用于测试项目可行性的易碎玩具，只有基础游戏功能，不会有任何美化  */

#include <QApplication>
#include <QDebug>

#include "gamescene.h"
#include "gameview.h"
#include "hud.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameScene gs;
    GameView gv(&gs);
    gv.show();

    HUD hud;
    hud.setGameView(&gv);
    hud.show();
    return a.exec();
}
