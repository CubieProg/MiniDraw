#include "Widgets/MainWindow.h"


// find_package(Qt6Designer CONFIG REQUIRED)
// target_link_libraries(main PRIVATE Qt6::Designer)

int main(int argc, char *argv[])
{
    QApplication app_(argc, argv);
    MainWindow window_;
    window_.showMaximized();

    return app_.exec();
}