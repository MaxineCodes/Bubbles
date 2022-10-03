/////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	- B U B B L E S   R A Y T R A C I N G   R E N D E R E R -
//	 ~         Offline renderer for bubbles only;          ~
//
//	The Bubbles raytracing rendering engine is a GUI offline raytracing engine project.
//	Using only renders Bubbles (spheres) using C++.
// 
// 
//	GUI made with the Qt on the open-source license.
//	
// 
//	Description:
//	`main()` instantiates Qt GUI window.
//	`bubblesGui()` handles Qt window and slot functions.
//	`raytrace()` does the magic.
//
//	Credits:
//  - Maxine Meijboom
// 
/////////////////////////////////////////////////////////////////////////////////////////////////////


// Qt/GUI includes
#include "bubblesgui.h"
#include <QtWidgets/QApplication>
#include <qfile.h>


// Application entrypoint
int main(int argc, char* argv[])
{
	// Instantiate Qt app & window
	QApplication app(argc, argv);
	bubblesGui guiWindow;

	// Assign .qss style to gui
	QFile styleSheetFile("./style.qss");
	styleSheetFile.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(styleSheetFile.readAll());
	// Set the style
	app.setStyleSheet(styleSheet);

	// Show gui
	guiWindow.showMaximized();
	guiWindow.show();
	return app.exec();
}