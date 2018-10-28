#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Hello, 易碎玩具";

    return a.exec();
}
