// Qt/GUI includes
#include "bubblesgui.h"
#include <QtWidgets/QApplication>
#include <qfile.h>

// Raytracing includes
#include "raytrace.h"

int main(int argc, char *argv[])
{
    // Instantiate Qt app & window
    QApplication app(argc, argv);
    BubblesUI guiWindow;

    // UI style
    QFile styleSheetFile("./style.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    // Set the style
    app.setStyleSheet(styleSheet);

    raytrace();

    // Show gui
    guiWindow.show();
    return app.exec();
}