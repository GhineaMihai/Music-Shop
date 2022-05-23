#include "qtUI.h"
#include "UI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    qtUI w;
    w.show();
    return a.exec();
    /*
    char* y = argv[1];
    if (argc > 1)
    {
        if (strcmp(y, "1") == 0)
        {
            UI ui;
            ui.run();
            return 0;
        }
        if (strcmp(y, "2") == 0)
        {
            QApplication a(argc, argv);
            qtUI w;
            w.show();
            return a.exec();
        }
    }
    */
}
