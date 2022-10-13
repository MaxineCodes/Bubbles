#include "bubblesgui.h"
#include <QtGui>
#include <iostream>

#include "raytrace.h"
#include "scene.h"
#include "camera.h"

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
// GUI globals

// Scene
scene Scene;
// Image
static int image_width;
static int image_height;
static int raytraceSamples;

// Camera variables
static point3 position(0, 1, 8);
static point3 viewDirection(0, 0.25, -1);
static vector3 viewUp(0, 1, 0);
static double FOV = 20;
static double aperture = 0.0;
static double dist_to_focus = (position - viewDirection).length();
// Camera
camera Camera(position, viewDirection, viewUp, FOV, Scene.aspect_ratio, aperture, dist_to_focus);

// __________________________________________________________________________________________________________________________
// GUI functions

// Update the variables in Scene instance to match UI
void bubblesGui::updateScene()
{
	// Render variables
	Scene.antialiasingEnabled = true;
	Scene.normalDebugMode = false;
	Scene.rayBouncesEnabled = true;
	Scene.maxRayDepth = 10;

	// Image variables
	Scene.image_width = 400;
	Scene.image_height = 200;
	Scene.raytraceSamples = 25;
}
void bubblesGui::updateCamera()
{
	// Render variables
	//Camera.
}

// Sets/updates the image in the viewport
void bubblesGui::setViewportImage(QImage image) 
{
	// Scale image to viewport size with padding
	int padding = 64; // in pixels
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
	ui.progressBar->setRange(progress, Scene.image_height);
}

// Render function
void bubblesGui::render()
{
	// Reset
	bubblesGui::reset();

	std::cout << "- Render Pressed" << "\n";

	// Raytrace and add image to the view
	raytrace(Scene, Camera, Scene.raytraceSamples);
	bubblesGui::setViewportImage(QImage32bit);
}

// Render in iterations
void bubblesGui::previewRender() 
{
	int iterations = 10;
	int previewSamples = 1;

	for (int i = 0; i < iterations; i++) 
	{
		std::cout << "Rendering preview..." << "\n";
		raytrace(Scene, Camera, i);
		bubblesGui::setViewportImage(QImage32bit);
		std::cout << "Done!" << "\n";
	}
}

// Reset the UI
void bubblesGui::reset()
{
	updateScene();
	// Reset progressbar to 0
	ui.progressBar->reset();

	// Size view to the same size as the raytrace render output & fill with black
	ui.viewLabel->resize(Scene.image_width, Scene.image_height);
	QImage32bit.fill(qRgb(0, 0, 0));
	bubblesGui::setViewportImage(QImage32bit);
}


// __________________________________________________________________________________________________________________________
// Qt slot functions

// When the render button is pressed
void bubblesGui::on_renderButton_clicked()
{
	std::cout << "- Render Pressed" << "\n";
	bubblesGui::render();
}
