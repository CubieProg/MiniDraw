#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app_(argc, argv);
    MainWindow window_;
    window_.showMaximized();

    return app_.exec();
}