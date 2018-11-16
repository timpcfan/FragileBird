#ifndef HUD_H
#define HUD_H

#include <QWidget>
#include "gameview.h"
#include <QTimer>

namespace Ui {
class HUD;
}

class HUD : public QWidget
{
    Q_OBJECT

public:
    explicit HUD(QWidget *parent = 0);
    ~HUD();
    void setGameView(GameView *gv);

public slots:
    void updateText();

private:
    Ui::HUD *ui;
    GameView *gv;
};

#endif // HUD_H
