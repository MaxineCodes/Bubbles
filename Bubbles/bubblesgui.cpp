#include "bubblesgui.h"
#include "raytrace.h"
#include "scene.h"

#include <QtGui>

#include <iostream>

// Class Constructor
bubblesGui::bubblesGui(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
}

// Class Destructor
bubblesGui::~bubblesGui()
{

}


// __________________________________________________________________________________________________________________________
// Qt slot functions

// When the render button is pressed
void bubblesGui::on_renderButton_clicked()
{
	std::cout << "- Render Pressed" << "\n";
	// Size view to the same size as the raytrace render output & fill with black
	ui.viewLabel->resize(scene::image_width, scene::image_height);
	QImage32bit.fill(qRgb(0, 0, 0));
	// Raytrace and add image to the view
	raytrace();
	ui.viewLabel->setPixmap(QPixmap::fromImage(QImage32bit));
}
