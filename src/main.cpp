#include "vdesc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vDesc w;
    w.setWindowTitle("\t vDesc");
    w.show();

    return a.exec();
}
