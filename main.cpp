#include <QApplication>

#include "match_three/match_three.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MatchThree mt;
    mt.show();
    return QApplication::exec();
}
