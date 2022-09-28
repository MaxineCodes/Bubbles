#pragma once

#include <QtWidgets/QWidget>
#include "ui_bubbles.h"

class Bubbles : public QWidget
{
    Q_OBJECT

public:
    Bubbles(QWidget *parent = nullptr);
    ~Bubbles();

private:
    Ui::BubblesClass ui;
};
