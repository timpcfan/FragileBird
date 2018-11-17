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

//    HUD hud;
//    hud.setGameView(&gv);
//    hud.show();
    return a.exec();
}
