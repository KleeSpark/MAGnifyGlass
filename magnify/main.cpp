#include "magnifyglass.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    magnifyGlass w;
    w.show();
    return a.exec();

}
