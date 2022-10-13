#pragma once

#include <QtWidgets/QWidget>
#include "ui_bubbles.h"

// Qt gui class
class bubblesGui : public QWidget
{
	Q_OBJECT

public:
	// Constructor and destructor
	bubblesGui(QWidget* parent = nullptr);
	~bubblesGui();

private:
	// Define ui class
	Ui::BubblesClass ui;

public: 
	// GUI functions
	void updateScene();
	void updateCamera();
	void setViewportImage(QImage image);
	void setProgressbarValue(int progress);
	void render();
	void previewRender();
	void reset();

private slots:
	// Defining functions to be called by the GUI events (such as button clicked)
	void on_renderButton_clicked();

};