#include <QApplication>
#include "InvestmentSimulator.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    InvestmentSimulator window;
    window.resize(800, 600);
    window.show();
    return app.exec();
}

