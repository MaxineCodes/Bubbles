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
// Scene instance
static scene Scene;

// __________________________________________________________________________________________________________________________
// Qt GUI structs

// Material struct to store data to pass to renderer
struct QMaterial
{
	// Enum for possible material types
	static const enum type { diffuse, metallic, dielectric };

public:
	// Public variables
	static const colour Colour;
	
	// Metal variables
	static const bool isMetallic;
	static const double roughness;

	// Dielectric variables
	static const bool isDielectric;

};

// Bubble struct to store data to pass to renderer
struct QBubble
{
public:
	// Public variables
	static const double size;
	static const vector3 position;

};

// __________________________________________________________________________________________________________________________
// Qt GUI functions

// Sets/updates the image in the viewport
void bubblesGui::setViewportImage(QImage image) 
{
	// Scale image to viewport size with padding
	int padding = 24;
	QWidget* _viewport = ui.viewport;
	int width = _viewport->width() - padding;
	int height = _viewport->height() - padding;
	image = image.scaled(width, height, Qt::KeepAspectRatio);

	// Set image to viewport
	ui.viewLabel->setPixmap(QPixmap::fromImage(image));
}

void bubblesGui::setProgressbarValue(int progress) 
{
	// Set progressbar to the range of horizontal scanlines in the raytrace render
	ui.progressBar->setRange(progress, scene::image_height);
}

// Render function
void bubblesGui::render()
{
	// Reset
	bubblesGui::reset();

	std::cout << "- Render Pressed" << "\n";

	// Raytrace and add image to the view
	raytrace(Scene, 100);
	bubblesGui::setViewportImage(QImage32bit);
}

void bubblesGui::previewRender() 
{
	int iterations = 10;
	int previewSamples = 1;

	for (int i = 0; i < iterations; i++) 
	{
		std::cout << "Rendering preview..." << "\n";
		raytrace(Scene, i);
		bubblesGui::setViewportImage(QImage32bit);
		std::cout << "Done!" << "\n";
	}
}


// __________________________________________________________________________________________________________________________
// Qt slot functions

// When the render button is pressed
void bubblesGui::on_renderButton_clicked()
{
	std::cout << "- Render Pressed" << "\n";
	bubblesGui::render();
}

// Reset the UI
void bubblesGui::reset()
{
	// Reset progressbar to 0
	ui.progressBar->reset();

	// Size view to the same size as the raytrace render output & fill with black
	ui.viewLabel->resize(scene::image_width, scene::image_height);
	QImage32bit.fill(qRgb(0, 0, 0));
	bubblesGui::setViewportImage(QImage32bit);
}
