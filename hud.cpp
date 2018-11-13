#include "hud.h"
#include "ui_hud.h"

HUD::HUD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HUD)
{
    ui->setupUi(this);
}

HUD::~HUD()
{
    delete ui;
}

void HUD::updateText()
{
    ui->plainTextEdit->setPlainText(gv->getAllData().text());
}

void HUD::setGameView(GameView *gv)
{
    this->gv = gv;
    QTimer * t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(updateText()));
    t->start(200);
}
