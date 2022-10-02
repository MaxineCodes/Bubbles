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
	qDebug() << "- Render Pressed";
	std::cout << "- Render Pressed";
	ui.viewLabel->resize(scene::image_width, scene::image_height);

	writeQImage32();

	ui.viewLabel->setPixmap(QPixmap::fromImage(QImage32bit));

	//ui.graphic->addPixmap(QPixmap::fromImage(image));

	//QGraphicsScene* scene = new QGraphicsScene;
	//scene->addPixmap(QPixmap::fromImage(QImage32bit));
	//QGraphicsView(scene);

	//QGraphicsScene scene;
	//QGraphicsView view(scene);
	//QGraphicsPixmapItem item(QPixmap::fromImage(QImage32bit));
	//scene.addItem(&item);
	//view.show();
	//raytrace();
}
